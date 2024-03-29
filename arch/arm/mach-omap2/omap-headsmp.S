/*
 * Secondary CPU startup routine source file.
 *
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Author:
 *      Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Interface functions needed for the SMP. This file is based on arm
 * realview smp platform.
 * Copyright (c) 2003 ARM Limited.
 *
 * This program is free software,you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/linkage.h>
#include <linux/init.h>

	__CPUINIT
/*
 * OMAP4 specific entry point for secondary CPU to jump from ROM
 * code.  This routine also provides a holding flag into which
 * secondary core is held until we're ready for it to initialise.
 * The primary core will update this flag using a hardware
 * register AuxCoreBoot0.
 */
ENTRY(omap_secondary_startup)
hold:	ldr	r12,=0x103
	dsb
	smc	#0			@ read from AuxCoreBoot0
	mov	r0, r0, lsr #9
	mrc	p15, 0, r4, c0, c0, 5
	and	r4, r4, #0x0f
	cmp	r0, r4
	bne	hold

	/*
	 * we've been released from the wait loop,secondary_stack
	 * should now contain the SVC stack for this core
	 */
	b	secondary_startup
ENDPROC(omap_secondary_startup)

