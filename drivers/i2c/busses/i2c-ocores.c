/*
 * i2c-ocores.c: I2C bus driver for OpenCores I2C controller
 * (http://www.opencores.org/projects.cgi/web/i2c/overview).
 *
 * Peter Korsgaard <jacmet@sunsite.dk>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

/*
 * Device tree configuration:
 *
 * Required properties:
 * - compatible      : "opencores,i2c-ocores"
 * - reg             : bus address start and address range size of device
 * - interrupts      : interrupt number
 * - regstep         : size of device registers in bytes
 * - clock-frequency : frequency of bus clock in Hz
 * 
 * Example:
 *
 *  i2c0: ocores@a0000000 {
 *              compatible = "opencores,i2c-ocores";
 *              reg = <0xa0000000 0x8>;
 *              interrupts = <10>;
 *
 *              regstep = <1>;
 *              clock-frequency = <20000000>;
 *
 * -- Devices connected on this I2C bus get
 * -- defined here; address- and size-cells
 * -- apply to these child devices
 *
 *              #address-cells = <1>;
 *              #size-cells = <0>;
 *
 *              dummy@60 {
 *                     compatible = "dummy";
 *                     reg = <60>;
 *              };
 *  };
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/i2c-ocores.h>
#include <linux/slab.h>
#include <linux/io.h>

struct ocores_i2c {
	void __iomem *base;
	int regstep;
	wait_queue_head_t wait;
	struct i2c_adapter adap;
	struct i2c_msg *msg;
	int pos;
	int nmsgs;
	int state; /* see STATE_ */
	int clock_khz;
};

/* registers */
#define OCI2C_PRELOW		0
#define OCI2C_PREHIGH		1
#define OCI2C_CONTROL		2
#define OCI2C_DATA		3
#define OCI2C_CMD		4 /* write only */
#define OCI2C_STATUS		4 /* read only, same address as OCI2C_CMD */

#define OCI2C_CTRL_IEN		0x40
#define OCI2C_CTRL_EN		0x80

#define OCI2C_CMD_START		0x91
#define OCI2C_CMD_STOP		0x41
#define OCI2C_CMD_READ		0x21
#define OCI2C_CMD_WRITE		0x11
#define OCI2C_CMD_READ_ACK	0x21
#define OCI2C_CMD_READ_NACK	0x29
#define OCI2C_CMD_IACK		0x01

#define OCI2C_STAT_IF		0x01
#define OCI2C_STAT_TIP		0x02
#define OCI2C_STAT_ARBLOST	0x20
#define OCI2C_STAT_BUSY		0x40
#define OCI2C_STAT_NACK		0x80

#define STATE_DONE		0
#define STATE_START		1
#define STATE_WRITE		2
#define STATE_READ		3
#define STATE_ERROR		4

static inline void oc_setreg(struct ocores_i2c *i2c, int reg, u8 value)
{
	iowrite8(value, i2c->base + reg * i2c->regstep);
}

static inline u8 oc_getreg(struct ocores_i2c *i2c, int reg)
{
	return ioread8(i2c->base + reg * i2c->regstep);
}

static void ocores_process(struct ocores_i2c *i2c)
{
	struct i2c_msg *msg = i2c->msg;
	u8 stat = oc_getreg(i2c, OCI2C_STATUS);

	if ((i2c->state == STATE_DONE) || (i2c->state == STATE_ERROR)) {
		/* stop has been sent */
		oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_IACK);
		wake_up(&i2c->wait);
		return;
	}

	/* error? */
	if (stat & OCI2C_STAT_ARBLOST) {
		i2c->state = STATE_ERROR;
		oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
		return;
	}

	if ((i2c->state == STATE_START) || (i2c->state == STATE_WRITE)) {
		i2c->state =
			(msg->flags & I2C_M_RD) ? STATE_READ : STATE_WRITE;

		if (stat & OCI2C_STAT_NACK) {
			i2c->state = STATE_ERROR;
			oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
			return;
		}
	} else
		msg->buf[i2c->pos++] = oc_getreg(i2c, OCI2C_DATA);

	/* end of msg? */
	if (i2c->pos == msg->len) {
		i2c->nmsgs--;
		i2c->msg++;
		i2c->pos = 0;
		msg = i2c->msg;

		if (i2c->nmsgs) {	/* end? */
			/* send start? */
			if (!(msg->flags & I2C_M_NOSTART)) {
				u8 addr = (msg->addr << 1);

				if (msg->flags & I2C_M_RD)
					addr |= 1;

				i2c->state = STATE_START;

				oc_setreg(i2c, OCI2C_DATA, addr);
				oc_setreg(i2c, OCI2C_CMD,  OCI2C_CMD_START);
				return;
			} else
				i2c->state = (msg->flags & I2C_M_RD)
					? STATE_READ : STATE_WRITE;
		} else {
			i2c->state = STATE_DONE;
			oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_STOP);
			return;
		}
	}

	if (i2c->state == STATE_READ) {
		oc_setreg(i2c, OCI2C_CMD, i2c->pos == (msg->len-1) ?
			  OCI2C_CMD_READ_NACK : OCI2C_CMD_READ_ACK);
	} else {
		oc_setreg(i2c, OCI2C_DATA, msg->buf[i2c->pos++]);
		oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_WRITE);
	}
}

static irqreturn_t ocores_isr(int irq, void *dev_id)
{
	struct ocores_i2c *i2c = dev_id;

	ocores_process(i2c);

	return IRQ_HANDLED;
}

static int ocores_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	struct ocores_i2c *i2c = i2c_get_adapdata(adap);

	i2c->msg = msgs;
	i2c->pos = 0;
	i2c->nmsgs = num;
	i2c->state = STATE_START;

	oc_setreg(i2c, OCI2C_DATA,
			(i2c->msg->addr << 1) |
			((i2c->msg->flags & I2C_M_RD) ? 1:0));

	oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_START);

	if (wait_event_timeout(i2c->wait, (i2c->state == STATE_ERROR) ||
			       (i2c->state == STATE_DONE), HZ))
		return (i2c->state == STATE_DONE) ? num : -EIO;
	else
		return -ETIMEDOUT;
}

static void ocores_init(struct ocores_i2c *i2c)
{
	int prescale;
	u8 ctrl = oc_getreg(i2c, OCI2C_CONTROL);

	/* make sure the device is disabled */
	oc_setreg(i2c, OCI2C_CONTROL, ctrl & ~(OCI2C_CTRL_EN|OCI2C_CTRL_IEN));

	prescale = (i2c->clock_khz / (5*100)) - 1;
	oc_setreg(i2c, OCI2C_PRELOW, prescale & 0xff);
	oc_setreg(i2c, OCI2C_PREHIGH, prescale >> 8);

	/* Init the device */
	oc_setreg(i2c, OCI2C_CMD, OCI2C_CMD_IACK);
	oc_setreg(i2c, OCI2C_CONTROL, ctrl | OCI2C_CTRL_IEN | OCI2C_CTRL_EN);
}


static u32 ocores_func(struct i2c_adapter *adap)
{
	return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
}

static const struct i2c_algorithm ocores_algorithm = {
	.master_xfer	= ocores_xfer,
	.functionality	= ocores_func,
};

static struct i2c_adapter ocores_adapter = {
	.owner		= THIS_MODULE,
	.name		= "i2c-ocores",
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &ocores_algorithm,
};

#ifdef CONFIG_OF
static int ocores_i2c_of_probe(struct platform_device* pdev,
				struct ocores_i2c* i2c)
{
	const __be32* val;

	val = of_get_property(pdev->dev.of_node, "regstep", NULL);
	if (!val) {
		dev_err(&pdev->dev, "Missing required parameter 'regstep'");
		return -ENODEV;
	}
	i2c->regstep = be32_to_cpup(val);

	val = of_get_property(pdev->dev.of_node, "clock-frequency", NULL);
	if (!val) {
		dev_err(&pdev->dev,
			"Missing required parameter 'clock-frequency'");
		return -ENODEV;
	}
	i2c->clock_khz = be32_to_cpup(val) / 1000;

	return 0;
}
#else
#define ocores_i2c_of_probe(pdev,i2c) -ENODEV
#endif

static int __devinit ocores_i2c_probe(struct platform_device *pdev)
{
	struct ocores_i2c *i2c;
	struct ocores_i2c_platform_data *pdata;
	struct resource *res, *res2;
	int ret;
	int i;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	res2 = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res2)
		return -ENODEV;

	i2c = devm_kzalloc(&pdev->dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	if (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), pdev->name)) {
		dev_err(&pdev->dev, "Memory region busy\n");
		return -EBUSY;
	}

	i2c->base = devm_ioremap_nocache(&pdev->dev, res->start,
					 resource_size(res));
	if (!i2c->base) {
		dev_err(&pdev->dev, "Unable to map registers\n");
		return -EIO;
	}

	pdata = pdev->dev.platform_data;
	if (pdata) {
		i2c->regstep = pdata->regstep;
		i2c->clock_khz = pdata->clock_khz;
	} else {
		ret = ocores_i2c_of_probe(pdev, i2c);
		if (ret)
			return ret;
	}

	ocores_init(i2c);

	init_waitqueue_head(&i2c->wait);
	ret = devm_request_irq(&pdev->dev, res2->start, ocores_isr, 0,
			       pdev->name, i2c);
	if (ret) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		return ret;
	}

	/* hook up driver to tree */
	platform_set_drvdata(pdev, i2c);
	i2c->adap = ocores_adapter;
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	/* add i2c adapter to i2c tree */
	ret = i2c_add_adapter(&i2c->adap);
	if (ret) {
		dev_err(&pdev->dev, "Failed to add adapter\n");
		return ret;
	}

	/* add in known devices to the bus */
	if (pdata) {
		for (i = 0; i < pdata->num_devices; i++)
			i2c_new_device(&i2c->adap, pdata->devices + i);
	}

	return 0;
}

static int __devexit ocores_i2c_remove(struct platform_device* pdev)
{
	struct ocores_i2c *i2c = platform_get_drvdata(pdev);

	/* disable i2c logic */
	oc_setreg(i2c, OCI2C_CONTROL, oc_getreg(i2c, OCI2C_CONTROL)
		  & ~(OCI2C_CTRL_EN|OCI2C_CTRL_IEN));

	/* remove adapter & data */
	i2c_del_adapter(&i2c->adap);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

#ifdef CONFIG_PM
static int ocores_i2c_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct ocores_i2c *i2c = platform_get_drvdata(pdev);
	u8 ctrl = oc_getreg(i2c, OCI2C_CONTROL);

	/* make sure the device is disabled */
	oc_setreg(i2c, OCI2C_CONTROL, ctrl & ~(OCI2C_CTRL_EN|OCI2C_CTRL_IEN));

	return 0;
}

static int ocores_i2c_resume(struct platform_device *pdev)
{
	struct ocores_i2c *i2c = platform_get_drvdata(pdev);

	ocores_init(i2c);

	return 0;
}
#else
#define ocores_i2c_suspend	NULL
#define ocores_i2c_resume	NULL
#endif

static struct of_device_id ocores_i2c_match[] = {
	{ .compatible = "opencores,i2c-ocores", },
	{},
};
MODULE_DEVICE_TABLE(of, ocores_i2c_match);

static struct platform_driver ocores_i2c_driver = {
	.probe   = ocores_i2c_probe,
	.remove  = __devexit_p(ocores_i2c_remove),
	.suspend = ocores_i2c_suspend,
	.resume  = ocores_i2c_resume,
	.driver  = {
		.owner = THIS_MODULE,
		.name = "ocores-i2c",
		.of_match_table = ocores_i2c_match,
	},
};

module_platform_driver(ocores_i2c_driver);

MODULE_AUTHOR("Peter Korsgaard <jacmet@sunsite.dk>");
MODULE_DESCRIPTION("OpenCores I2C bus driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ocores-i2c");
