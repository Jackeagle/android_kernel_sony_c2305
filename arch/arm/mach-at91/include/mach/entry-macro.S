/*
 * arch/arm/mach-at91/include/mach/entry-macro.S
 *
 *  Copyright (C) 2003-2005 SAN People
 *
 * Low-level IRQ helper macros for AT91RM9200 platforms
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <mach/hardware.h>
#include <mach/at91_aic.h>

	.macro  get_irqnr_preamble, base, tmp
	ldr	\base, =at91_aic_base		@ base virtual address of AIC peripheral
	ldr	\base, [\base]
	.endm

	.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp
	ldr	\irqnr, [\base, #AT91_AIC_IVR]		@ read IRQ vector register: de-asserts nIRQ to processor (and clears interrupt)
	ldr	\irqstat, [\base, #AT91_AIC_ISR]	@ read interrupt source number
	teq	\irqstat, #0				@ ISR is 0 when no current interrupt, or spurious interrupt
	streq	\tmp, [\base, #AT91_AIC_EOICR]		@ not going to be handled further, then ACK it now.
	.endm

