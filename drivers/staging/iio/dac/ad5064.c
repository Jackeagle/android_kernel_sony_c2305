/*
 * AD5024, AD5025, AD5044, AD5045, AD5064, AD5064-1, AD5065, AD5628, AD5648,
 * AD5666, AD5668 Digital to analog converters driver
 *
 * Copyright 2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2.
 */

#include <linux/device.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/regulator/consumer.h>

#include "../iio.h"
#include "../sysfs.h"
#include "dac.h"

#define AD5064_MAX_DAC_CHANNELS			8
#define AD5064_MAX_VREFS			4

#define AD5064_ADDR(x)				((x) << 20)
#define AD5064_CMD(x)				((x) << 24)

#define AD5064_ADDR_DAC(chan)			(chan)
#define AD5064_ADDR_ALL_DAC			0xF

#define AD5064_CMD_WRITE_INPUT_N		0x0
#define AD5064_CMD_UPDATE_DAC_N			0x1
#define AD5064_CMD_WRITE_INPUT_N_UPDATE_ALL	0x2
#define AD5064_CMD_WRITE_INPUT_N_UPDATE_N	0x3
#define AD5064_CMD_POWERDOWN_DAC		0x4
#define AD5064_CMD_CLEAR			0x5
#define AD5064_CMD_LDAC_MASK			0x6
#define AD5064_CMD_RESET			0x7
#define AD5064_CMD_CONFIG			0x8

#define AD5064_CONFIG_DAISY_CHAIN_ENABLE	BIT(1)
#define AD5064_CONFIG_INT_VREF_ENABLE		BIT(0)

#define AD5064_LDAC_PWRDN_NONE			0x0
#define AD5064_LDAC_PWRDN_1K			0x1
#define AD5064_LDAC_PWRDN_100K			0x2
#define AD5064_LDAC_PWRDN_3STATE		0x3

/**
 * struct ad5064_chip_info - chip specific information
 * @shared_vref:	whether the vref supply is shared between channels
 * @internal_vref:	internal reference voltage. 0 if the chip has no internal
 *			vref.
 * @channel:		channel specification
 * @num_channels:	number of channels
 */

struct ad5064_chip_info {
	bool shared_vref;
	unsigned long internal_vref;
	const struct iio_chan_spec *channels;
	unsigned int num_channels;
};

/**
 * struct ad5064_state - driver instance specific data
 * @spi:		spi_device
 * @chip_info:		chip model specific constants, available modes etc
 * @vref_reg:		vref supply regulators
 * @pwr_down:		whether channel is powered down
 * @pwr_down_mode:	channel's current power down mode
 * @dac_cache:		current DAC raw value (chip does not support readback)
 * @use_internal_vref:	set to true if the internal reference voltage should be
 *			used.
 * @data:		spi transfer buffers
 */

struct ad5064_state {
	struct spi_device		*spi;
	const struct ad5064_chip_info	*chip_info;
	struct regulator_bulk_data	vref_reg[AD5064_MAX_VREFS];
	bool				pwr_down[AD5064_MAX_DAC_CHANNELS];
	u8				pwr_down_mode[AD5064_MAX_DAC_CHANNELS];
	unsigned int			dac_cache[AD5064_MAX_DAC_CHANNELS];
	bool				use_internal_vref;

	/*
	 * DMA (thus cache coherency maintenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be32 data ____cacheline_aligned;
};

enum ad5064_type {
	ID_AD5024,
	ID_AD5025,
	ID_AD5044,
	ID_AD5045,
	ID_AD5064,
	ID_AD5064_1,
	ID_AD5065,
	ID_AD5628_1,
	ID_AD5628_2,
	ID_AD5648_1,
	ID_AD5648_2,
	ID_AD5666_1,
	ID_AD5666_2,
	ID_AD5668_1,
	ID_AD5668_2,
};

static int ad5064_spi_write(struct ad5064_state *st, unsigned int cmd,
	unsigned int addr, unsigned int val, unsigned int shift)
{
	val <<= shift;

	st->data = cpu_to_be32(AD5064_CMD(cmd) | AD5064_ADDR(addr) | val);

	return spi_write(st->spi, &st->data, sizeof(st->data));
}

static int ad5064_sync_powerdown_mode(struct ad5064_state *st,
	unsigned int channel)
{
	unsigned int val;
	int ret;

	val = (0x1 << channel);

	if (st->pwr_down[channel])
		val |= st->pwr_down_mode[channel] << 8;

	ret = ad5064_spi_write(st, AD5064_CMD_POWERDOWN_DAC, 0, val, 0);

	return ret;
}

static const char ad5064_powerdown_modes[][15] = {
	[AD5064_LDAC_PWRDN_NONE]	= "",
	[AD5064_LDAC_PWRDN_1K]		= "1kohm_to_gnd",
	[AD5064_LDAC_PWRDN_100K]	= "100kohm_to_gnd",
	[AD5064_LDAC_PWRDN_3STATE]	= "three_state",
};

static ssize_t ad5064_read_powerdown_mode_available(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, char *buf)
{
	return sprintf(buf, "%s %s %s\n", ad5064_powerdown_modes[1],
		ad5064_powerdown_modes[2], ad5064_powerdown_modes[3]);
}

static ssize_t ad5064_read_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, char *buf)
{
	struct ad5064_state *st = iio_priv(indio_dev);

	return sprintf(buf, "%s\n",
		ad5064_powerdown_modes[st->pwr_down_mode[chan->channel]]);
}

static ssize_t ad5064_write_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, const char *buf, size_t len)
{
	struct ad5064_state *st = iio_priv(indio_dev);
	unsigned int mode, i;
	int ret;

	mode = 0;

	for (i = 1; i < ARRAY_SIZE(ad5064_powerdown_modes); ++i) {
		if (sysfs_streq(buf, ad5064_powerdown_modes[i])) {
			mode = i;
			break;
		}
	}
	if (mode == 0)
		return  -EINVAL;

	mutex_lock(&indio_dev->mlock);
	st->pwr_down_mode[chan->channel] = mode;

	ret = ad5064_sync_powerdown_mode(st, chan->channel);
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}

static ssize_t ad5064_read_dac_powerdown(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, char *buf)
{
	struct ad5064_state *st = iio_priv(indio_dev);

	return sprintf(buf, "%d\n", st->pwr_down[chan->channel]);
}

static ssize_t ad5064_write_dac_powerdown(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, const char *buf, size_t len)
{
	struct ad5064_state *st = iio_priv(indio_dev);
	bool pwr_down;
	int ret;

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	mutex_lock(&indio_dev->mlock);
	st->pwr_down[chan->channel] = pwr_down;

	ret = ad5064_sync_powerdown_mode(st, chan->channel);
	mutex_unlock(&indio_dev->mlock);
	return ret ? ret : len;
}

static int ad5064_get_vref(struct ad5064_state *st,
	struct iio_chan_spec const *chan)
{
	unsigned int i;

	if (st->use_internal_vref)
		return st->chip_info->internal_vref;

	i = st->chip_info->shared_vref ? 0 : chan->channel;
	return regulator_get_voltage(st->vref_reg[i].consumer);
}

static int ad5064_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad5064_state *st = iio_priv(indio_dev);
	int scale_uv;

	switch (m) {
	case 0:
		*val = st->dac_cache[chan->channel];
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		scale_uv = ad5064_get_vref(st, chan);
		if (scale_uv < 0)
			return scale_uv;

		scale_uv = (scale_uv * 100) >> chan->scan_type.realbits;
		*val =  scale_uv / 100000;
		*val2 = (scale_uv % 100000) * 10;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		break;
	}
	return -EINVAL;
}

static int ad5064_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	struct ad5064_state *st = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case 0:
		if (val > (1 << chan->scan_type.realbits) || val < 0)
			return -EINVAL;

		mutex_lock(&indio_dev->mlock);
		ret = ad5064_spi_write(st, AD5064_CMD_WRITE_INPUT_N_UPDATE_N,
				chan->address, val, chan->scan_type.shift);
		if (ret == 0)
			st->dac_cache[chan->channel] = val;
		mutex_unlock(&indio_dev->mlock);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

static const struct iio_info ad5064_info = {
	.read_raw = ad5064_read_raw,
	.write_raw = ad5064_write_raw,
	.driver_module = THIS_MODULE,
};

static struct iio_chan_spec_ext_info ad5064_ext_info[] = {
	{
		.name = "powerdown",
		.read = ad5064_read_dac_powerdown,
		.write = ad5064_write_dac_powerdown,
	},
	{
		.name = "powerdown_mode",
		.read = ad5064_read_powerdown_mode,
		.write = ad5064_write_powerdown_mode,
	},
	{
		.name = "powerdown_mode_available",
		.shared = true,
		.read = ad5064_read_powerdown_mode_available,
	},
	{ },
};

#define AD5064_CHANNEL(chan, bits) {				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (chan),					\
	.info_mask = IIO_CHAN_INFO_SCALE_SEPARATE_BIT,	\
	.address = AD5064_ADDR_DAC(chan),			\
	.scan_type = IIO_ST('u', (bits), 16, 20 - (bits)),	\
	.ext_info = ad5064_ext_info,				\
}

#define DECLARE_AD5064_CHANNELS(name, bits) \
const struct iio_chan_spec name[] = { \
	AD5064_CHANNEL(0, bits), \
	AD5064_CHANNEL(1, bits), \
	AD5064_CHANNEL(2, bits), \
	AD5064_CHANNEL(3, bits), \
	AD5064_CHANNEL(4, bits), \
	AD5064_CHANNEL(5, bits), \
	AD5064_CHANNEL(6, bits), \
	AD5064_CHANNEL(7, bits), \
}

static DECLARE_AD5064_CHANNELS(ad5024_channels, 12);
static DECLARE_AD5064_CHANNELS(ad5044_channels, 14);
static DECLARE_AD5064_CHANNELS(ad5064_channels, 16);

static const struct ad5064_chip_info ad5064_chip_info_tbl[] = {
	[ID_AD5024] = {
		.shared_vref = false,
		.channels = ad5024_channels,
		.num_channels = 4,
	},
	[ID_AD5025] = {
		.shared_vref = false,
		.channels = ad5024_channels,
		.num_channels = 2,
	},
	[ID_AD5044] = {
		.shared_vref = false,
		.channels = ad5044_channels,
		.num_channels = 4,
	},
	[ID_AD5045] = {
		.shared_vref = false,
		.channels = ad5044_channels,
		.num_channels = 2,
	},
	[ID_AD5064] = {
		.shared_vref = false,
		.channels = ad5064_channels,
		.num_channels = 4,
	},
	[ID_AD5064_1] = {
		.shared_vref = true,
		.channels = ad5064_channels,
		.num_channels = 4,
	},
	[ID_AD5065] = {
		.shared_vref = false,
		.channels = ad5064_channels,
		.num_channels = 2,
	},
	[ID_AD5628_1] = {
		.shared_vref = true,
		.internal_vref = 2500000,
		.channels = ad5024_channels,
		.num_channels = 8,
	},
	[ID_AD5628_2] = {
		.shared_vref = true,
		.internal_vref = 5000000,
		.channels = ad5024_channels,
		.num_channels = 8,
	},
	[ID_AD5648_1] = {
		.shared_vref = true,
		.internal_vref = 2500000,
		.channels = ad5044_channels,
		.num_channels = 8,
	},
	[ID_AD5648_2] = {
		.shared_vref = true,
		.internal_vref = 5000000,
		.channels = ad5044_channels,
		.num_channels = 8,
	},
	[ID_AD5666_1] = {
		.shared_vref = true,
		.internal_vref = 2500000,
		.channels = ad5064_channels,
		.num_channels = 4,
	},
	[ID_AD5666_2] = {
		.shared_vref = true,
		.internal_vref = 5000000,
		.channels = ad5064_channels,
		.num_channels = 4,
	},
	[ID_AD5668_1] = {
		.shared_vref = true,
		.internal_vref = 2500000,
		.channels = ad5064_channels,
		.num_channels = 8,
	},
	[ID_AD5668_2] = {
		.shared_vref = true,
		.internal_vref = 5000000,
		.channels = ad5064_channels,
		.num_channels = 8,
	},
};

static inline unsigned int ad5064_num_vref(struct ad5064_state *st)
{
	return st->chip_info->shared_vref ? 1 : st->chip_info->num_channels;
}

static const char * const ad5064_vref_names[] = {
	"vrefA",
	"vrefB",
	"vrefC",
	"vrefD",
};

static const char * const ad5064_vref_name(struct ad5064_state *st,
	unsigned int vref)
{
	return st->chip_info->shared_vref ? "vref" : ad5064_vref_names[vref];
}

static int __devinit ad5064_probe(struct spi_device *spi)
{
	enum ad5064_type type = spi_get_device_id(spi)->driver_data;
	struct iio_dev *indio_dev;
	struct ad5064_state *st;
	unsigned int i;
	int ret;

	indio_dev = iio_allocate_device(sizeof(*st));
	if (indio_dev == NULL)
		return  -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->chip_info = &ad5064_chip_info_tbl[type];
	st->spi = spi;

	for (i = 0; i < ad5064_num_vref(st); ++i)
		st->vref_reg[i].supply = ad5064_vref_name(st, i);

	ret = regulator_bulk_get(&st->spi->dev, ad5064_num_vref(st),
		st->vref_reg);
	if (ret) {
		if (!st->chip_info->internal_vref)
			goto error_free;
		st->use_internal_vref = true;
		ret = ad5064_spi_write(st, AD5064_CMD_CONFIG, 0,
			AD5064_CONFIG_INT_VREF_ENABLE, 0);
		if (ret) {
			dev_err(&spi->dev, "Failed to enable internal vref: %d\n",
				ret);
			goto error_free;
		}
	} else {
		ret = regulator_bulk_enable(ad5064_num_vref(st), st->vref_reg);
		if (ret)
			goto error_free_reg;
	}

	for (i = 0; i < st->chip_info->num_channels; ++i) {
		st->pwr_down_mode[i] = AD5064_LDAC_PWRDN_1K;
		st->dac_cache[i] = 0x8000;
	}

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5064_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg;

	return 0;

error_disable_reg:
	if (!st->use_internal_vref)
		regulator_bulk_disable(ad5064_num_vref(st), st->vref_reg);
error_free_reg:
	if (!st->use_internal_vref)
		regulator_bulk_free(ad5064_num_vref(st), st->vref_reg);
error_free:
	iio_free_device(indio_dev);

	return ret;
}


static int __devexit ad5064_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad5064_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	if (!st->use_internal_vref) {
		regulator_bulk_disable(ad5064_num_vref(st), st->vref_reg);
		regulator_bulk_free(ad5064_num_vref(st), st->vref_reg);
	}

	iio_free_device(indio_dev);

	return 0;
}

static const struct spi_device_id ad5064_id[] = {
	{"ad5024", ID_AD5024},
	{"ad5025", ID_AD5025},
	{"ad5044", ID_AD5044},
	{"ad5045", ID_AD5045},
	{"ad5064", ID_AD5064},
	{"ad5064-1", ID_AD5064_1},
	{"ad5065", ID_AD5065},
	{"ad5628-1", ID_AD5628_1},
	{"ad5628-2", ID_AD5628_2},
	{"ad5648-1", ID_AD5648_1},
	{"ad5648-2", ID_AD5648_2},
	{"ad5666-1", ID_AD5666_1},
	{"ad5666-2", ID_AD5666_2},
	{"ad5668-1", ID_AD5668_1},
	{"ad5668-2", ID_AD5668_2},
	{"ad5668-3", ID_AD5668_2}, /* similar enough to ad5668-2 */
	{}
};
MODULE_DEVICE_TABLE(spi, ad5064_id);

static struct spi_driver ad5064_driver = {
	.driver = {
		   .name = "ad5064",
		   .owner = THIS_MODULE,
	},
	.probe = ad5064_probe,
	.remove = __devexit_p(ad5064_remove),
	.id_table = ad5064_id,
};
module_spi_driver(ad5064_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5024/25/44/45/64/64-1/65, AD5628/48/66/68 DAC");
MODULE_LICENSE("GPL v2");
