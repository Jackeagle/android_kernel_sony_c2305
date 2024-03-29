/*
 * linux/arch/arm/plat-omap/devices.c
 *
 * Common platform device setup/initialization for OMAP1 and OMAP2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/memblock.h>

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/mach/map.h>
#include <asm/memblock.h>

#include <plat/tc.h>
#include <plat/board.h>
#include <plat/mmc.h>
#include <plat/menelaus.h>
#include <plat/omap44xx.h>

#if defined(CONFIG_MMC_OMAP) || defined(CONFIG_MMC_OMAP_MODULE) || \
	defined(CONFIG_MMC_OMAP_HS) || defined(CONFIG_MMC_OMAP_HS_MODULE)

#define OMAP_MMC_NR_RES		2

/*
 * Register MMC devices. Called from mach-omap1 and mach-omap2 device init.
 */
int __init omap_mmc_add(const char *name, int id, unsigned long base,
				unsigned long size, unsigned int irq,
				struct omap_mmc_platform_data *data)
{
	struct platform_device *pdev;
	struct resource res[OMAP_MMC_NR_RES];
	int ret;

	pdev = platform_device_alloc(name, id);
	if (!pdev)
		return -ENOMEM;

	memset(res, 0, OMAP_MMC_NR_RES * sizeof(struct resource));
	res[0].start = base;
	res[0].end = base + size - 1;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = res[1].end = irq;
	res[1].flags = IORESOURCE_IRQ;

	ret = platform_device_add_resources(pdev, res, ARRAY_SIZE(res));
	if (ret == 0)
		ret = platform_device_add_data(pdev, data, sizeof(*data));
	if (ret)
		goto fail;

	ret = platform_device_add(pdev);
	if (ret)
		goto fail;

	/* return device handle to board setup code */
	data->dev = &pdev->dev;
	return 0;

fail:
	platform_device_put(pdev);
	return ret;
}

#endif

/*-------------------------------------------------------------------------*/

#if defined(CONFIG_HW_RANDOM_OMAP) || defined(CONFIG_HW_RANDOM_OMAP_MODULE)

#ifdef CONFIG_ARCH_OMAP2
#define	OMAP_RNG_BASE		0x480A0000
#else
#define	OMAP_RNG_BASE		0xfffe5000
#endif

static struct resource rng_resources[] = {
	{
		.start		= OMAP_RNG_BASE,
		.end		= OMAP_RNG_BASE + 0x4f,
		.flags		= IORESOURCE_MEM,
	},
};

static struct platform_device omap_rng_device = {
	.name		= "omap_rng",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rng_resources),
	.resource	= rng_resources,
};

static void omap_init_rng(void)
{
	(void) platform_device_register(&omap_rng_device);
}
#else
static inline void omap_init_rng(void) {}
#endif

/*-------------------------------------------------------------------------*/

/* Numbering for the SPI-capable controllers when used for SPI:
 * spi		= 1
 * uwire	= 2
 * mmc1..2	= 3..4
 * mcbsp1..3	= 5..7
 */

#if defined(CONFIG_SPI_OMAP_UWIRE) || defined(CONFIG_SPI_OMAP_UWIRE_MODULE)

#define	OMAP_UWIRE_BASE		0xfffb3000

static struct resource uwire_resources[] = {
	{
		.start		= OMAP_UWIRE_BASE,
		.end		= OMAP_UWIRE_BASE + 0x20,
		.flags		= IORESOURCE_MEM,
	},
};

static struct platform_device omap_uwire_device = {
	.name	   = "omap_uwire",
	.id	     = -1,
	.num_resources	= ARRAY_SIZE(uwire_resources),
	.resource	= uwire_resources,
};

static void omap_init_uwire(void)
{
	/* FIXME define and use a boot tag; not all boards will be hooking
	 * up devices to the microwire controller, and multi-board configs
	 * mean that CONFIG_SPI_OMAP_UWIRE may be configured anyway...
	 */

	/* board-specific code must configure chipselects (only a few
	 * are normally used) and SCLK/SDI/SDO (each has two choices).
	 */
	(void) platform_device_register(&omap_uwire_device);
}
#else
static inline void omap_init_uwire(void) {}
#endif

#if defined(CONFIG_TIDSPBRIDGE) || defined(CONFIG_TIDSPBRIDGE_MODULE)

static phys_addr_t omap_dsp_phys_mempool_base;

void __init omap_dsp_reserve_sdram_memblock(void)
{
	phys_addr_t size = CONFIG_TIDSPBRIDGE_MEMPOOL_SIZE;
	phys_addr_t paddr;

	if (!size)
		return;

	paddr = arm_memblock_steal(size, SZ_1M);
	if (!paddr) {
		pr_err("%s: failed to reserve %x bytes\n",
				__func__, size);
		return;
	}

	omap_dsp_phys_mempool_base = paddr;
}

phys_addr_t omap_dsp_get_mempool_base(void)
{
	return omap_dsp_phys_mempool_base;
}
EXPORT_SYMBOL(omap_dsp_get_mempool_base);
#endif

/*
 * This gets called after board-specific INIT_MACHINE, and initializes most
 * on-chip peripherals accessible on this board (except for few like USB):
 *
 *  (a) Does any "standard config" pin muxing needed.  Board-specific
 *	code will have muxed GPIO pins and done "nonstandard" setup;
 *	that code could live in the boot loader.
 *  (b) Populating board-specific platform_data with the data drivers
 *	rely on to handle wiring variations.
 *  (c) Creating platform devices as meaningful on this board and
 *	with this kernel configuration.
 *
 * Claiming GPIOs, and setting their direction and initial values, is the
 * responsibility of the device drivers.  So is responding to probe().
 *
 * Board-specific knowledge like creating devices or pin setup is to be
 * kept out of drivers as much as possible.  In particular, pin setup
 * may be handled by the boot loader, and drivers should expect it will
 * normally have been done by the time they're probed.
 */
static int __init omap_init_devices(void)
{
	/* please keep these calls, and their implementations above,
	 * in alphabetical order so they're easier to sort through.
	 */
	omap_init_rng();
	omap_init_uwire();
	return 0;
}
arch_initcall(omap_init_devices);
