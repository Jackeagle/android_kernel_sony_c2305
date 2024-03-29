/*
 * OMAP WakeupGen header file
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef OMAP_ARCH_WAKEUPGEN_H
#define OMAP_ARCH_WAKEUPGEN_H

#define OMAP_WKG_CONTROL_0			0x00
#define OMAP_WKG_ENB_A_0			0x10
#define OMAP_WKG_ENB_B_0			0x14
#define OMAP_WKG_ENB_C_0			0x18
#define OMAP_WKG_ENB_D_0			0x1c
#define OMAP_WKG_ENB_SECURE_A_0			0x20
#define OMAP_WKG_ENB_SECURE_B_0			0x24
#define OMAP_WKG_ENB_SECURE_C_0			0x28
#define OMAP_WKG_ENB_SECURE_D_0			0x2c
#define OMAP_WKG_ENB_A_1			0x410
#define OMAP_WKG_ENB_B_1			0x414
#define OMAP_WKG_ENB_C_1			0x418
#define OMAP_WKG_ENB_D_1			0x41c
#define OMAP_WKG_ENB_SECURE_A_1			0x420
#define OMAP_WKG_ENB_SECURE_B_1			0x424
#define OMAP_WKG_ENB_SECURE_C_1			0x428
#define OMAP_WKG_ENB_SECURE_D_1			0x42c
#define OMAP_AUX_CORE_BOOT_0			0x800
#define OMAP_AUX_CORE_BOOT_1			0x804
#define OMAP_PTMSYNCREQ_MASK			0xc00
#define OMAP_PTMSYNCREQ_EN			0xc04
#define OMAP_TIMESTAMPCYCLELO			0xc08
#define OMAP_TIMESTAMPCYCLEHI			0xc0c

extern int __init omap_wakeupgen_init(void);
#endif
