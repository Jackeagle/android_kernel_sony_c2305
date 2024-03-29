/*
 * wm_hubs.h  --  WM899x common code
 *
 * Copyright 2009 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@opensource.wolfsonmicro.com>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _WM_HUBS_H
#define _WM_HUBS_H

#include <linux/completion.h>
#include <linux/interrupt.h>

struct snd_soc_codec;

extern const unsigned int wm_hubs_spkmix_tlv[];

/* This *must* be the first element of the codec->private_data struct */
struct wm_hubs_data {
	int dcs_codes_l;
	int dcs_codes_r;
	int dcs_readback_mode;
	int hp_startup_mode;
	int series_startup;
	int no_series_update;

	bool no_cache_class_w;
	bool class_w;
	u16 class_w_dcs;

	bool lineout1_se;
	bool lineout1n_ena;
	bool lineout1p_ena;

	bool lineout2_se;
	bool lineout2n_ena;
	bool lineout2p_ena;

	bool dcs_done_irq;
	struct completion dcs_done;
};

extern int wm_hubs_add_analogue_controls(struct snd_soc_codec *);
extern int wm_hubs_add_analogue_routes(struct snd_soc_codec *, int, int);
extern int wm_hubs_handle_analogue_pdata(struct snd_soc_codec *,
					 int lineout1_diff, int lineout2_diff,
					 int lineout1fb, int lineout2fb,
					 int jd_scthr, int jd_thr,
					 int micbias1_lvl, int micbias2_lvl);

extern irqreturn_t wm_hubs_dcs_done(int irq, void *data);
extern void wm_hubs_vmid_ena(struct snd_soc_codec *codec);
extern void wm_hubs_set_bias_level(struct snd_soc_codec *codec,
				   enum snd_soc_bias_level level);

#endif
