#ifndef __MT2063_H__
#define __MT2063_H__

#include "dvb_frontend.h"

struct mt2063_config {
	u8 tuner_address;
	u32 refclock;
};

#if defined(CONFIG_MEDIA_TUNER_MT2063) || (defined(CONFIG_MEDIA_TUNER_MT2063_MODULE) && defined(MODULE))
struct dvb_frontend *mt2063_attach(struct dvb_frontend *fe,
				   struct mt2063_config *config,
				   struct i2c_adapter *i2c);

#else

static inline struct dvb_frontend *mt2063_attach(struct dvb_frontend *fe,
				   struct mt2063_config *config,
				   struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	return NULL;
}

/* FIXME: Should use the standard DVB attachment interfaces */
unsigned int tuner_MT2063_SoftwareShutdown(struct dvb_frontend *fe);
unsigned int tuner_MT2063_ClearPowerMaskBits(struct dvb_frontend *fe);

#endif /* CONFIG_DVB_MT2063 */

#endif /* __MT2063_H__ */
