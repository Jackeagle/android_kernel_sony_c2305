/*
 * Copyright 2007-2008 Nouveau Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __NOUVEAU_BIOS_H__
#define __NOUVEAU_BIOS_H__

#include "nvreg.h"
#include "nouveau_i2c.h"

#define DCB_MAX_NUM_ENTRIES 16
#define DCB_MAX_NUM_I2C_ENTRIES 16
#define DCB_MAX_NUM_GPIO_ENTRIES 32
#define DCB_MAX_NUM_CONNECTOR_ENTRIES 16

#define DCB_LOC_ON_CHIP 0

#define ROM16(x) le16_to_cpu(*(u16 *)&(x))
#define ROM32(x) le32_to_cpu(*(u32 *)&(x))
#define ROM48(x) ({ u8 *p = &(x); (u64)ROM16(p[4]) << 32 | ROM32(p[0]); })
#define ROM64(x) le64_to_cpu(*(u64 *)&(x))
#define ROMPTR(d,x) ({            \
	struct drm_nouveau_private *dev_priv = (d)->dev_private; \
	ROM16(x) ? &dev_priv->vbios.data[ROM16(x)] : NULL; \
})

struct bit_entry {
	uint8_t  id;
	uint8_t  version;
	uint16_t length;
	uint16_t offset;
	uint8_t *data;
};

int bit_table(struct drm_device *, u8 id, struct bit_entry *);

enum dcb_gpio_tag {
	DCB_GPIO_PANEL_POWER = 0x01,
	DCB_GPIO_TVDAC0 = 0x0c,
	DCB_GPIO_TVDAC1 = 0x2d,
	DCB_GPIO_PWM_FAN = 0x09,
	DCB_GPIO_FAN_SENSE = 0x3d,
	DCB_GPIO_UNUSED = 0xff
};

enum dcb_connector_type {
	DCB_CONNECTOR_VGA = 0x00,
	DCB_CONNECTOR_TV_0 = 0x10,
	DCB_CONNECTOR_TV_1 = 0x11,
	DCB_CONNECTOR_TV_3 = 0x13,
	DCB_CONNECTOR_DVI_I = 0x30,
	DCB_CONNECTOR_DVI_D = 0x31,
	DCB_CONNECTOR_DMS59_0 = 0x38,
	DCB_CONNECTOR_DMS59_1 = 0x39,
	DCB_CONNECTOR_LVDS = 0x40,
	DCB_CONNECTOR_LVDS_SPWG = 0x41,
	DCB_CONNECTOR_DP = 0x46,
	DCB_CONNECTOR_eDP = 0x47,
	DCB_CONNECTOR_HDMI_0 = 0x60,
	DCB_CONNECTOR_HDMI_1 = 0x61,
	DCB_CONNECTOR_DMS59_DP0 = 0x64,
	DCB_CONNECTOR_DMS59_DP1 = 0x65,
	DCB_CONNECTOR_NONE = 0xff
};

enum dcb_type {
	OUTPUT_ANALOG = 0,
	OUTPUT_TV = 1,
	OUTPUT_TMDS = 2,
	OUTPUT_LVDS = 3,
	OUTPUT_DP = 6,
	OUTPUT_EOL = 14, /* DCB 4.0+, appears to be end-of-list */
	OUTPUT_UNUSED = 15,
	OUTPUT_ANY = -1
};

struct dcb_entry {
	int index;	/* may not be raw dcb index if merging has happened */
	enum dcb_type type;
	uint8_t i2c_index;
	uint8_t heads;
	uint8_t connector;
	uint8_t bus;
	uint8_t location;
	uint8_t or;
	bool duallink_possible;
	union {
		struct sor_conf {
			int link;
		} sorconf;
		struct {
			int maxfreq;
		} crtconf;
		struct {
			struct sor_conf sor;
			bool use_straps_for_mode;
			bool use_acpi_for_edid;
			bool use_power_scripts;
		} lvdsconf;
		struct {
			bool has_component_output;
		} tvconf;
		struct {
			struct sor_conf sor;
			int link_nr;
			int link_bw;
		} dpconf;
		struct {
			struct sor_conf sor;
			int slave_addr;
		} tmdsconf;
	};
	bool i2c_upper_default;
};

struct dcb_table {
	uint8_t version;
	int entries;
	struct dcb_entry entry[DCB_MAX_NUM_ENTRIES];
};

enum nouveau_or {
	OUTPUT_A = (1 << 0),
	OUTPUT_B = (1 << 1),
	OUTPUT_C = (1 << 2)
};

enum LVDS_script {
	/* Order *does* matter here */
	LVDS_INIT = 1,
	LVDS_RESET,
	LVDS_BACKLIGHT_ON,
	LVDS_BACKLIGHT_OFF,
	LVDS_PANEL_ON,
	LVDS_PANEL_OFF
};

/* these match types in pll limits table version 0x40,
 * nouveau uses them on all chipsets internally where a
 * specific pll needs to be referenced, but the exact
 * register isn't known.
 */
enum pll_types {
	PLL_CORE   = 0x01,
	PLL_SHADER = 0x02,
	PLL_UNK03  = 0x03,
	PLL_MEMORY = 0x04,
	PLL_VDEC   = 0x05,
	PLL_UNK40  = 0x40,
	PLL_UNK41  = 0x41,
	PLL_UNK42  = 0x42,
	PLL_VPLL0  = 0x80,
	PLL_VPLL1  = 0x81,
	PLL_MAX    = 0xff
};

struct pll_lims {
	u32 reg;

	struct {
		int minfreq;
		int maxfreq;
		int min_inputfreq;
		int max_inputfreq;

		uint8_t min_m;
		uint8_t max_m;
		uint8_t min_n;
		uint8_t max_n;
	} vco1, vco2;

	uint8_t max_log2p;
	/*
	 * for most pre nv50 cards setting a log2P of 7 (the common max_log2p
	 * value) is no different to 6 (at least for vplls) so allowing the MNP
	 * calc to use 7 causes the generated clock to be out by a factor of 2.
	 * however, max_log2p cannot be fixed-up during parsing as the
	 * unmodified max_log2p value is still needed for setting mplls, hence
	 * an additional max_usable_log2p member
	 */
	uint8_t max_usable_log2p;
	uint8_t log2p_bias;

	uint8_t min_p;
	uint8_t max_p;

	int refclk;
};

struct nvbios {
	struct drm_device *dev;
	enum {
		NVBIOS_BMP,
		NVBIOS_BIT
	} type;
	uint16_t offset;
	uint32_t length;
	uint8_t *data;

	uint8_t chip_version;

	uint32_t dactestval;
	uint32_t tvdactestval;
	uint8_t digital_min_front_porch;
	bool fp_no_ddc;

	spinlock_t lock;

	bool execute;

	uint8_t major_version;
	uint8_t feature_byte;
	bool is_mobile;

	uint32_t fmaxvco, fminvco;

	bool old_style_init;
	uint16_t init_script_tbls_ptr;
	uint16_t extra_init_script_tbl_ptr;
	uint16_t macro_index_tbl_ptr;
	uint16_t macro_tbl_ptr;
	uint16_t condition_tbl_ptr;
	uint16_t io_condition_tbl_ptr;
	uint16_t io_flag_condition_tbl_ptr;
	uint16_t init_function_tbl_ptr;

	uint16_t pll_limit_tbl_ptr;
	uint16_t ram_restrict_tbl_ptr;
	uint8_t ram_restrict_group_count;

	uint16_t some_script_ptr; /* BIT I + 14 */
	uint16_t init96_tbl_ptr; /* BIT I + 16 */

	struct dcb_table dcb;

	struct {
		int crtchead;
	} state;

	struct {
		struct dcb_entry *output;
		int crtc;
		uint16_t script_table_ptr;
	} display;

	struct {
		uint16_t fptablepointer;	/* also used by tmds */
		uint16_t fpxlatetableptr;
		int xlatwidth;
		uint16_t lvdsmanufacturerpointer;
		uint16_t fpxlatemanufacturertableptr;
		uint16_t mode_ptr;
		uint16_t xlated_entry;
		bool power_off_for_reset;
		bool reset_after_pclk_change;
		bool dual_link;
		bool link_c_increment;
		bool if_is_24bit;
		int duallink_transition_clk;
		uint8_t strapless_is_24bit;
		uint8_t *edid;

		/* will need resetting after suspend */
		int last_script_invoc;
		bool lvds_init_run;
	} fp;

	struct {
		uint16_t output0_script_ptr;
		uint16_t output1_script_ptr;
	} tmds;

	struct {
		uint16_t mem_init_tbl_ptr;
		uint16_t sdr_seq_tbl_ptr;
		uint16_t ddr_seq_tbl_ptr;

		struct {
			uint8_t crt, tv, panel;
		} i2c_indices;

		uint16_t lvds_single_a_script_ptr;
	} legacy;
};

void *dcb_table(struct drm_device *);
void *dcb_outp(struct drm_device *, u8 idx);
int dcb_outp_foreach(struct drm_device *, void *data,
		     int (*)(struct drm_device *, void *, int idx, u8 *outp));
u8 *dcb_conntab(struct drm_device *);
u8 *dcb_conn(struct drm_device *, u8 idx);

#endif
