/* arch/arm/mach-h720x/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 *  Copyright (C) 1994-1999 Russell King
 *  Moved from linux/arch/arm/kernel/debug.S by Ben Dooks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
*/

#include <mach/hardware.h>

		.equ    io_virt, IO_VIRT
		.equ    io_phys, IO_PHYS

		.macro  addruart, rp, rv, tmp
		mov     \rp, #0x00020000	@ UART1
		add     \rv, \rp, #io_virt	@ virtual address
		add     \rp, \rp, #io_phys	@ physical base address
		.endm

		.macro  senduart,rd,rx
		str     \rd, [\rx, #0x0]        @ UARTDR

		.endm

		.macro  waituart,rd,rx
1001:		ldr     \rd, [\rx, #0x18]       @ UARTFLG
		tst     \rd, #1 << 5	       @ UARTFLGUTXFF - 1 when full
		bne     1001b
		.endm

		.macro  busyuart,rd,rx
1001:		ldr     \rd, [\rx, #0x18]       @ UARTFLG
		tst     \rd, #1 << 3	       @ UARTFLGUBUSY - 1 when busy
		bne     1001b
		.endm
