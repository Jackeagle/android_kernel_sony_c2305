/*
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 *
 * Copyright (C) 2010 John Crispin <blogic@openwrt.org>
 * Copyright (C) 2010 Thomas Langer <thomas.langer@lantiq.com>
 */

#include <linux/interrupt.h>
#include <linux/ioport.h>

#include <asm/bootinfo.h>
#include <asm/irq_cpu.h>

#include <lantiq_soc.h>
#include <irq.h>

/* register definitions */
#define LTQ_ICU_IM0_ISR		0x0000
#define LTQ_ICU_IM0_IER		0x0008
#define LTQ_ICU_IM0_IOSR	0x0010
#define LTQ_ICU_IM0_IRSR	0x0018
#define LTQ_ICU_IM0_IMR		0x0020
#define LTQ_ICU_IM1_ISR		0x0028
#define LTQ_ICU_OFFSET		(LTQ_ICU_IM1_ISR - LTQ_ICU_IM0_ISR)

#define LTQ_EIU_EXIN_C		0x0000
#define LTQ_EIU_EXIN_INIC	0x0004
#define LTQ_EIU_EXIN_INEN	0x000C

/* irq numbers used by the external interrupt unit (EIU) */
#define LTQ_EIU_IR0		(INT_NUM_IM4_IRL0 + 30)
#define LTQ_EIU_IR1		(INT_NUM_IM3_IRL0 + 31)
#define LTQ_EIU_IR2		(INT_NUM_IM1_IRL0 + 26)
#define LTQ_EIU_IR3		INT_NUM_IM1_IRL0
#define LTQ_EIU_IR4		(INT_NUM_IM1_IRL0 + 1)
#define LTQ_EIU_IR5		(INT_NUM_IM1_IRL0 + 2)
#define LTQ_EIU_IR6		(INT_NUM_IM2_IRL0 + 30)

#define MAX_EIU			6

/* irqs generated by device attached to the EBU need to be acked in
 * a special manner
 */
#define LTQ_ICU_EBU_IRQ		22

#define ltq_icu_w32(x, y)	ltq_w32((x), ltq_icu_membase + (y))
#define ltq_icu_r32(x)		ltq_r32(ltq_icu_membase + (x))

#define ltq_eiu_w32(x, y)	ltq_w32((x), ltq_eiu_membase + (y))
#define ltq_eiu_r32(x)		ltq_r32(ltq_eiu_membase + (x))

static unsigned short ltq_eiu_irq[MAX_EIU] = {
	LTQ_EIU_IR0,
	LTQ_EIU_IR1,
	LTQ_EIU_IR2,
	LTQ_EIU_IR3,
	LTQ_EIU_IR4,
	LTQ_EIU_IR5,
};

static struct resource ltq_icu_resource = {
	.name	= "icu",
	.start	= LTQ_ICU_BASE_ADDR,
	.end	= LTQ_ICU_BASE_ADDR + LTQ_ICU_SIZE - 1,
	.flags	= IORESOURCE_MEM,
};

static struct resource ltq_eiu_resource = {
	.name	= "eiu",
	.start	= LTQ_EIU_BASE_ADDR,
	.end	= LTQ_EIU_BASE_ADDR + LTQ_ICU_SIZE - 1,
	.flags	= IORESOURCE_MEM,
};

static void __iomem *ltq_icu_membase;
static void __iomem *ltq_eiu_membase;

void ltq_disable_irq(struct irq_data *d)
{
	u32 ier = LTQ_ICU_IM0_IER;
	int irq_nr = d->irq - INT_NUM_IRQ0;

	ier += LTQ_ICU_OFFSET * (irq_nr / INT_NUM_IM_OFFSET);
	irq_nr %= INT_NUM_IM_OFFSET;
	ltq_icu_w32(ltq_icu_r32(ier) & ~(1 << irq_nr), ier);
}

void ltq_mask_and_ack_irq(struct irq_data *d)
{
	u32 ier = LTQ_ICU_IM0_IER;
	u32 isr = LTQ_ICU_IM0_ISR;
	int irq_nr = d->irq - INT_NUM_IRQ0;

	ier += LTQ_ICU_OFFSET * (irq_nr / INT_NUM_IM_OFFSET);
	isr += LTQ_ICU_OFFSET * (irq_nr / INT_NUM_IM_OFFSET);
	irq_nr %= INT_NUM_IM_OFFSET;
	ltq_icu_w32(ltq_icu_r32(ier) & ~(1 << irq_nr), ier);
	ltq_icu_w32((1 << irq_nr), isr);
}

static void ltq_ack_irq(struct irq_data *d)
{
	u32 isr = LTQ_ICU_IM0_ISR;
	int irq_nr = d->irq - INT_NUM_IRQ0;

	isr += LTQ_ICU_OFFSET * (irq_nr / INT_NUM_IM_OFFSET);
	irq_nr %= INT_NUM_IM_OFFSET;
	ltq_icu_w32((1 << irq_nr), isr);
}

void ltq_enable_irq(struct irq_data *d)
{
	u32 ier = LTQ_ICU_IM0_IER;
	int irq_nr = d->irq - INT_NUM_IRQ0;

	ier += LTQ_ICU_OFFSET  * (irq_nr / INT_NUM_IM_OFFSET);
	irq_nr %= INT_NUM_IM_OFFSET;
	ltq_icu_w32(ltq_icu_r32(ier) | (1 << irq_nr), ier);
}

static unsigned int ltq_startup_eiu_irq(struct irq_data *d)
{
	int i;

	ltq_enable_irq(d);
	for (i = 0; i < MAX_EIU; i++) {
		if (d->irq == ltq_eiu_irq[i]) {
			/* low level - we should really handle set_type */
			ltq_eiu_w32(ltq_eiu_r32(LTQ_EIU_EXIN_C) |
				(0x6 << (i * 4)), LTQ_EIU_EXIN_C);
			/* clear all pending */
			ltq_eiu_w32(ltq_eiu_r32(LTQ_EIU_EXIN_INIC) & ~(1 << i),
				LTQ_EIU_EXIN_INIC);
			/* enable */
			ltq_eiu_w32(ltq_eiu_r32(LTQ_EIU_EXIN_INEN) | (1 << i),
				LTQ_EIU_EXIN_INEN);
			break;
		}
	}

	return 0;
}

static void ltq_shutdown_eiu_irq(struct irq_data *d)
{
	int i;

	ltq_disable_irq(d);
	for (i = 0; i < MAX_EIU; i++) {
		if (d->irq == ltq_eiu_irq[i]) {
			/* disable */
			ltq_eiu_w32(ltq_eiu_r32(LTQ_EIU_EXIN_INEN) & ~(1 << i),
				LTQ_EIU_EXIN_INEN);
			break;
		}
	}
}

static struct irq_chip ltq_irq_type = {
	"icu",
	.irq_enable = ltq_enable_irq,
	.irq_disable = ltq_disable_irq,
	.irq_unmask = ltq_enable_irq,
	.irq_ack = ltq_ack_irq,
	.irq_mask = ltq_disable_irq,
	.irq_mask_ack = ltq_mask_and_ack_irq,
};

static struct irq_chip ltq_eiu_type = {
	"eiu",
	.irq_startup = ltq_startup_eiu_irq,
	.irq_shutdown = ltq_shutdown_eiu_irq,
	.irq_enable = ltq_enable_irq,
	.irq_disable = ltq_disable_irq,
	.irq_unmask = ltq_enable_irq,
	.irq_ack = ltq_ack_irq,
	.irq_mask = ltq_disable_irq,
	.irq_mask_ack = ltq_mask_and_ack_irq,
};

static void ltq_hw_irqdispatch(int module)
{
	u32 irq;

	irq = ltq_icu_r32(LTQ_ICU_IM0_IOSR + (module * LTQ_ICU_OFFSET));
	if (irq == 0)
		return;

	/* silicon bug causes only the msb set to 1 to be valid. all
	 * other bits might be bogus
	 */
	irq = __fls(irq);
	do_IRQ((int)irq + INT_NUM_IM0_IRL0 + (INT_NUM_IM_OFFSET * module));

	/* if this is a EBU irq, we need to ack it or get a deadlock */
	if ((irq == LTQ_ICU_EBU_IRQ) && (module == 0))
		ltq_ebu_w32(ltq_ebu_r32(LTQ_EBU_PCC_ISTAT) | 0x10,
			LTQ_EBU_PCC_ISTAT);
}

#define DEFINE_HWx_IRQDISPATCH(x)					\
	static void ltq_hw ## x ## _irqdispatch(void)			\
	{								\
		ltq_hw_irqdispatch(x);					\
	}
DEFINE_HWx_IRQDISPATCH(0)
DEFINE_HWx_IRQDISPATCH(1)
DEFINE_HWx_IRQDISPATCH(2)
DEFINE_HWx_IRQDISPATCH(3)
DEFINE_HWx_IRQDISPATCH(4)

static void ltq_hw5_irqdispatch(void)
{
	do_IRQ(MIPS_CPU_TIMER_IRQ);
}

asmlinkage void plat_irq_dispatch(void)
{
	unsigned int pending = read_c0_status() & read_c0_cause() & ST0_IM;
	unsigned int i;

	if (pending & CAUSEF_IP7) {
		do_IRQ(MIPS_CPU_TIMER_IRQ);
		goto out;
	} else {
		for (i = 0; i < 5; i++) {
			if (pending & (CAUSEF_IP2 << i)) {
				ltq_hw_irqdispatch(i);
				goto out;
			}
		}
	}
	pr_alert("Spurious IRQ: CAUSE=0x%08x\n", read_c0_status());

out:
	return;
}

static struct irqaction cascade = {
	.handler = no_action,
	.name = "cascade",
};

void __init arch_init_irq(void)
{
	int i;

	if (insert_resource(&iomem_resource, &ltq_icu_resource) < 0)
		panic("Failed to insert icu memory");

	if (request_mem_region(ltq_icu_resource.start,
			resource_size(&ltq_icu_resource), "icu") < 0)
		panic("Failed to request icu memory");

	ltq_icu_membase = ioremap_nocache(ltq_icu_resource.start,
				resource_size(&ltq_icu_resource));
	if (!ltq_icu_membase)
		panic("Failed to remap icu memory");

	if (insert_resource(&iomem_resource, &ltq_eiu_resource) < 0)
		panic("Failed to insert eiu memory");

	if (request_mem_region(ltq_eiu_resource.start,
			resource_size(&ltq_eiu_resource), "eiu") < 0)
		panic("Failed to request eiu memory");

	ltq_eiu_membase = ioremap_nocache(ltq_eiu_resource.start,
				resource_size(&ltq_eiu_resource));
	if (!ltq_eiu_membase)
		panic("Failed to remap eiu memory");

	/* make sure all irqs are turned off by default */
	for (i = 0; i < 5; i++)
		ltq_icu_w32(0, LTQ_ICU_IM0_IER + (i * LTQ_ICU_OFFSET));

	/* clear all possibly pending interrupts */
	ltq_icu_w32(~0, LTQ_ICU_IM0_ISR + (i * LTQ_ICU_OFFSET));

	mips_cpu_irq_init();

	for (i = 2; i <= 6; i++)
		setup_irq(i, &cascade);

	if (cpu_has_vint) {
		pr_info("Setting up vectored interrupts\n");
		set_vi_handler(2, ltq_hw0_irqdispatch);
		set_vi_handler(3, ltq_hw1_irqdispatch);
		set_vi_handler(4, ltq_hw2_irqdispatch);
		set_vi_handler(5, ltq_hw3_irqdispatch);
		set_vi_handler(6, ltq_hw4_irqdispatch);
		set_vi_handler(7, ltq_hw5_irqdispatch);
	}

	for (i = INT_NUM_IRQ0;
		i <= (INT_NUM_IRQ0 + (5 * INT_NUM_IM_OFFSET)); i++)
		if ((i == LTQ_EIU_IR0) || (i == LTQ_EIU_IR1) ||
			(i == LTQ_EIU_IR2))
			irq_set_chip_and_handler(i, &ltq_eiu_type,
				handle_level_irq);
		/* EIU3-5 only exist on ar9 and vr9 */
		else if (((i == LTQ_EIU_IR3) || (i == LTQ_EIU_IR4) ||
			(i == LTQ_EIU_IR5)) && (ltq_is_ar9() || ltq_is_vr9()))
			irq_set_chip_and_handler(i, &ltq_eiu_type,
				handle_level_irq);
		else
			irq_set_chip_and_handler(i, &ltq_irq_type,
				handle_level_irq);

#if !defined(CONFIG_MIPS_MT_SMP) && !defined(CONFIG_MIPS_MT_SMTC)
	set_c0_status(IE_IRQ0 | IE_IRQ1 | IE_IRQ2 |
		IE_IRQ3 | IE_IRQ4 | IE_IRQ5);
#else
	set_c0_status(IE_SW0 | IE_SW1 | IE_IRQ0 | IE_IRQ1 |
		IE_IRQ2 | IE_IRQ3 | IE_IRQ4 | IE_IRQ5);
#endif
}

unsigned int __cpuinit get_c0_compare_int(void)
{
	return CP0_LEGACY_COMPARE_IRQ;
}
