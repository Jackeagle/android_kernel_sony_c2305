/***************************************************************************/

/*
 *	linux/arch/m68knommu/platform/54xx/config.c
 *
 *	Copyright (C) 2010, Philippe De Muyter <phdm@macqel.be>
 */

/***************************************************************************/

#include <linux/kernel.h>
#include <linux/param.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/bootmem.h>
#include <asm/pgalloc.h>
#include <asm/machdep.h>
#include <asm/coldfire.h>
#include <asm/m54xxsim.h>
#include <asm/mcfuart.h>
#include <asm/m54xxgpt.h>
#ifdef CONFIG_MMU
#include <asm/mmu_context.h>
#endif

/***************************************************************************/

static void __init m54xx_uarts_init(void)
{
	/* enable io pins */
	__raw_writeb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD,
		MCF_MBAR + MCF_PAR_PSC(0));
	__raw_writeb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD | MCF_PAR_PSC_RTS_RTS,
		MCF_MBAR + MCF_PAR_PSC(1));
	__raw_writeb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD | MCF_PAR_PSC_RTS_RTS |
		MCF_PAR_PSC_CTS_CTS, MCF_MBAR + MCF_PAR_PSC(2));
	__raw_writeb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD,
		MCF_MBAR + MCF_PAR_PSC(3));
}

/***************************************************************************/

static void mcf54xx_reset(void)
{
	/* disable interrupts and enable the watchdog */
	asm("movew #0x2700, %sr\n");
	__raw_writel(0, MCF_MBAR + MCF_GPT_GMS0);
	__raw_writel(MCF_GPT_GCIR_CNT(1), MCF_MBAR + MCF_GPT_GCIR0);
	__raw_writel(MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE | MCF_GPT_GMS_TMS(4),
						MCF_MBAR + MCF_GPT_GMS0);
}

/***************************************************************************/

#ifdef CONFIG_MMU

unsigned long num_pages;

static void __init mcf54xx_bootmem_alloc(void)
{
	unsigned long start_pfn;
	unsigned long memstart;

	/* _rambase and _ramend will be naturally page aligned */
	m68k_memory[0].addr = _rambase;
	m68k_memory[0].size = _ramend - _rambase;

	/* compute total pages in system */
	num_pages = (_ramend - _rambase) >> PAGE_SHIFT;

	/* page numbers */
	memstart = PAGE_ALIGN(_ramstart);
	min_low_pfn = _rambase >> PAGE_SHIFT;
	start_pfn = memstart >> PAGE_SHIFT;
	max_low_pfn = _ramend >> PAGE_SHIFT;
	high_memory = (void *)_ramend;

	m68k_virt_to_node_shift = fls(_ramend - _rambase - 1) - 6;
	module_fixup(NULL, __start_fixup, __stop_fixup);

	/* setup bootmem data */
	m68k_setup_node(0);
	memstart += init_bootmem_node(NODE_DATA(0), start_pfn,
		min_low_pfn, max_low_pfn);
	free_bootmem_node(NODE_DATA(0), memstart, _ramend - memstart);
}

#endif /* CONFIG_MMU */

/***************************************************************************/

void __init config_BSP(char *commandp, int size)
{
#ifdef CONFIG_MMU
	mcf54xx_bootmem_alloc();
	mmu_context_init();
#endif
	mach_reset = mcf54xx_reset;
	mach_sched_init = hw_timer_init;
	m54xx_uarts_init();
}

/***************************************************************************/
