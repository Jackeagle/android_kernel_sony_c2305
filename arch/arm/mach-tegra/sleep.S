/*
 * arch/arm/mach-tegra/sleep.S
 *
 * Copyright (c) 2010-2011, NVIDIA Corporation.
 * Copyright (c) 2011, Google, Inc.
 *
 * Author: Colin Cross <ccross@android.com>
 *         Gary King <gking@nvidia.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <linux/linkage.h>

#include <asm/assembler.h>

#include <mach/iomap.h>

#include "flowctrl.h"

#define TEGRA_FLOW_CTRL_VIRT (TEGRA_FLOW_CTRL_BASE - IO_PPSB_PHYS \
					+ IO_PPSB_VIRT)

/* returns the offset of the flow controller halt register for a cpu */
.macro cpu_to_halt_reg rd, rcpu
	cmp	\rcpu, #0
	subne	\rd, \rcpu, #1
	movne	\rd, \rd, lsl #3
	addne	\rd, \rd, #0x14
	moveq	\rd, #0
.endm

/* returns the offset of the flow controller csr register for a cpu */
.macro cpu_to_csr_reg rd, rcpu
	cmp	\rcpu, #0
	subne	\rd, \rcpu, #1
	movne	\rd, \rd, lsl #3
	addne	\rd, \rd, #0x18
	moveq	\rd, #8
.endm

/* returns the ID of the current processor */
.macro cpu_id, rd
	mrc	p15, 0, \rd, c0, c0, 5
	and	\rd, \rd, #0xF
.endm

/* loads a 32-bit value into a register without a data access */
.macro mov32, reg, val
	movw	\reg, #:lower16:\val
	movt	\reg, #:upper16:\val
.endm

/*
 * tegra_cpu_wfi
 *
 * puts current CPU in clock-gated wfi using the flow controller
 *
 * corrupts r0-r3
 * must be called with MMU on
 */

ENTRY(tegra_cpu_wfi)
	cpu_id	r0
	cpu_to_halt_reg r1, r0
	cpu_to_csr_reg r2, r0
	mov32	r0, TEGRA_FLOW_CTRL_VIRT
	mov	r3, #FLOW_CTRL_CSR_INTR_FLAG | FLOW_CTRL_CSR_EVENT_FLAG
	str	r3, [r0, r2]	@ clear event & interrupt status
	mov	r3, #FLOW_CTRL_WAIT_FOR_INTERRUPT | FLOW_CTRL_JTAG_RESUME
	str	r3, [r0, r1]	@ put flow controller in wait irq mode
	dsb
	wfi
	mov	r3, #0
	str	r3, [r0, r1]	@ clear flow controller halt status
	mov	r3, #FLOW_CTRL_CSR_INTR_FLAG | FLOW_CTRL_CSR_EVENT_FLAG
	str	r3, [r0, r2]	@ clear event & interrupt status
	dsb
	mov	pc, lr
ENDPROC(tegra_cpu_wfi)

