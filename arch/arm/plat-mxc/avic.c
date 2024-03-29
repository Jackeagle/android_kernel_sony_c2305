/*
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include <linux/module.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <mach/common.h>
#include <asm/mach/irq.h>
#include <asm/exception.h>
#include <mach/hardware.h>

#include "irq-common.h"

#define AVIC_INTCNTL		0x00	/* int control reg */
#define AVIC_NIMASK		0x04	/* int mask reg */
#define AVIC_INTENNUM		0x08	/* int enable number reg */
#define AVIC_INTDISNUM		0x0C	/* int disable number reg */
#define AVIC_INTENABLEH		0x10	/* int enable reg high */
#define AVIC_INTENABLEL		0x14	/* int enable reg low */
#define AVIC_INTTYPEH		0x18	/* int type reg high */
#define AVIC_INTTYPEL		0x1C	/* int type reg low */
#define AVIC_NIPRIORITY(x)	(0x20 + 4 * (7 - (x))) /* int priority */
#define AVIC_NIVECSR		0x40	/* norm int vector/status */
#define AVIC_FIVECSR		0x44	/* fast int vector/status */
#define AVIC_INTSRCH		0x48	/* int source reg high */
#define AVIC_INTSRCL		0x4C	/* int source reg low */
#define AVIC_INTFRCH		0x50	/* int force reg high */
#define AVIC_INTFRCL		0x54	/* int force reg low */
#define AVIC_NIPNDH		0x58	/* norm int pending high */
#define AVIC_NIPNDL		0x5C	/* norm int pending low */
#define AVIC_FIPNDH		0x60	/* fast int pending high */
#define AVIC_FIPNDL		0x64	/* fast int pending low */

#define AVIC_NUM_IRQS 64

void __iomem *avic_base;

static u32 avic_saved_mask_reg[2];

#ifdef CONFIG_MXC_IRQ_PRIOR
static int avic_irq_set_priority(unsigned char irq, unsigned char prio)
{
	unsigned int temp;
	unsigned int mask = 0x0F << irq % 8 * 4;

	if (irq >= AVIC_NUM_IRQS)
		return -EINVAL;

	temp = __raw_readl(avic_base + AVIC_NIPRIORITY(irq / 8));
	temp &= ~mask;
	temp |= prio & mask;

	__raw_writel(temp, avic_base + AVIC_NIPRIORITY(irq / 8));

	return 0;
}
#endif

#ifdef CONFIG_FIQ
static int avic_set_irq_fiq(unsigned int irq, unsigned int type)
{
	unsigned int irqt;

	if (irq >= AVIC_NUM_IRQS)
		return -EINVAL;

	if (irq < AVIC_NUM_IRQS / 2) {
		irqt = __raw_readl(avic_base + AVIC_INTTYPEL) & ~(1 << irq);
		__raw_writel(irqt | (!!type << irq), avic_base + AVIC_INTTYPEL);
	} else {
		irq -= AVIC_NUM_IRQS / 2;
		irqt = __raw_readl(avic_base + AVIC_INTTYPEH) & ~(1 << irq);
		__raw_writel(irqt | (!!type << irq), avic_base + AVIC_INTTYPEH);
	}

	return 0;
}
#endif /* CONFIG_FIQ */


static struct mxc_extra_irq avic_extra_irq = {
#ifdef CONFIG_MXC_IRQ_PRIOR
	.set_priority = avic_irq_set_priority,
#endif
#ifdef CONFIG_FIQ
	.set_irq_fiq = avic_set_irq_fiq,
#endif
};

#ifdef CONFIG_PM
static void avic_irq_suspend(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct irq_chip_type *ct = gc->chip_types;
	int idx = gc->irq_base >> 5;

	avic_saved_mask_reg[idx] = __raw_readl(avic_base + ct->regs.mask);
	__raw_writel(gc->wake_active, avic_base + ct->regs.mask);
}

static void avic_irq_resume(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct irq_chip_type *ct = gc->chip_types;
	int idx = gc->irq_base >> 5;

	__raw_writel(avic_saved_mask_reg[idx], avic_base + ct->regs.mask);
}

#else
#define avic_irq_suspend NULL
#define avic_irq_resume NULL
#endif

static __init void avic_init_gc(unsigned int irq_start)
{
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	int idx = irq_start >> 5;

	gc = irq_alloc_generic_chip("mxc-avic", 1, irq_start, avic_base,
				    handle_level_irq);
	gc->private = &avic_extra_irq;
	gc->wake_enabled = IRQ_MSK(32);

	ct = gc->chip_types;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	ct->chip.irq_ack = irq_gc_mask_clr_bit;
	ct->chip.irq_set_wake = irq_gc_set_wake;
	ct->chip.irq_suspend = avic_irq_suspend;
	ct->chip.irq_resume = avic_irq_resume;
	ct->regs.mask = !idx ? AVIC_INTENABLEL : AVIC_INTENABLEH;
	ct->regs.ack = ct->regs.mask;

	irq_setup_generic_chip(gc, IRQ_MSK(32), 0, IRQ_NOREQUEST, 0);
}

asmlinkage void __exception_irq_entry avic_handle_irq(struct pt_regs *regs)
{
	u32 nivector;

	do {
		nivector = __raw_readl(avic_base + AVIC_NIVECSR) >> 16;
		if (nivector == 0xffff)
			break;

		handle_IRQ(nivector, regs);
	} while (1);
}

/*
 * This function initializes the AVIC hardware and disables all the
 * interrupts. It registers the interrupt enable and disable functions
 * to the kernel for each interrupt source.
 */
void __init mxc_init_irq(void __iomem *irqbase)
{
	int i;

	avic_base = irqbase;

	/* put the AVIC into the reset value with
	 * all interrupts disabled
	 */
	__raw_writel(0, avic_base + AVIC_INTCNTL);
	__raw_writel(0x1f, avic_base + AVIC_NIMASK);

	/* disable all interrupts */
	__raw_writel(0, avic_base + AVIC_INTENABLEH);
	__raw_writel(0, avic_base + AVIC_INTENABLEL);

	/* all IRQ no FIQ */
	__raw_writel(0, avic_base + AVIC_INTTYPEH);
	__raw_writel(0, avic_base + AVIC_INTTYPEL);

	for (i = 0; i < AVIC_NUM_IRQS; i += 32)
		avic_init_gc(i);

	/* Set default priority value (0) for all IRQ's */
	for (i = 0; i < 8; i++)
		__raw_writel(0, avic_base + AVIC_NIPRIORITY(i));

#ifdef CONFIG_FIQ
	/* Initialize FIQ */
	init_FIQ();
#endif

	printk(KERN_INFO "MXC IRQ initialized\n");
}
