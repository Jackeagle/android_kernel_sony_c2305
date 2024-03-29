/* arch/arm/mach-realview/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 *  Copyright (C) 1994-1999 Russell King
 *  Moved from linux/arch/arm/kernel/debug.S by Ben Dooks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifdef CONFIG_DEBUG_REALVIEW_STD_PORT
#define DEBUG_LL_UART_OFFSET	0x00009000
#elif defined(CONFIG_DEBUG_REALVIEW_PB1176_PORT)
#define DEBUG_LL_UART_OFFSET	0x0010c000
#endif

#ifndef DEBUG_LL_UART_OFFSET
#error "Unknown RealView platform"
#endif

		.macro	addruart, rp, rv, tmp
		mov	\rp, #DEBUG_LL_UART_OFFSET
		orr	\rv, \rp, #0xfb000000	@ virtual base
		orr	\rp, \rp, #0x10000000	@ physical base
		.endm

#include <asm/hardware/debug-pl01x.S>
