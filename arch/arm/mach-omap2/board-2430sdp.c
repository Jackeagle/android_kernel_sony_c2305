/*
 * linux/arch/arm/mach-omap2/board-2430sdp.c
 *
 * Copyright (C) 2006 Texas Instruments
 *
 * Modified from mach-omap2/board-generic.c
 *
 * Initial Code : Based on a patch from Komal Shah and Richard Woodruff
 * Updated the Code for 2430 SDP : Syed Mohammed Khasim
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/physmap.h>
#include <linux/mmc/host.h>
#include <linux/delay.h>
#include <linux/i2c/twl.h>
#include <linux/regulator/machine.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/gpio.h>

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <plat/board.h>
#include "common.h"
#include <plat/gpmc.h>
#include <plat/usb.h>
#include <plat/gpmc-smc91x.h>

#include <video/omapdss.h>
#include <video/omap-panel-generic-dpi.h>

#include "mux.h"
#include "hsmmc.h"
#include "common-board-devices.h"

#define SDP2430_CS0_BASE	0x04000000
#define SECONDARY_LCD_GPIO		147

static struct mtd_partition sdp2430_partitions[] = {
	/* bootloader (U-Boot, etc) in first sector */
	{
		.name		= "bootloader",
		.offset		= 0,
		.size		= SZ_256K,
		.mask_flags	= MTD_WRITEABLE,	/* force read-only */
	 },
	/* bootloader params in the next sector */
	{
		.name		= "params",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= 0,
	 },
	/* kernel */
	{
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_2M,
		.mask_flags	= 0
	},
	/* file system */
	{
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0
	}
};

static struct physmap_flash_data sdp2430_flash_data = {
	.width		= 2,
	.parts		= sdp2430_partitions,
	.nr_parts	= ARRAY_SIZE(sdp2430_partitions),
};

static struct resource sdp2430_flash_resource = {
	.start		= SDP2430_CS0_BASE,
	.end		= SDP2430_CS0_BASE + SZ_64M - 1,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device sdp2430_flash_device = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev = {
		.platform_data	= &sdp2430_flash_data,
	},
	.num_resources	= 1,
	.resource	= &sdp2430_flash_resource,
};

static struct platform_device *sdp2430_devices[] __initdata = {
	&sdp2430_flash_device,
};

/* LCD */
#define SDP2430_LCD_PANEL_BACKLIGHT_GPIO	91
#define SDP2430_LCD_PANEL_ENABLE_GPIO		154

static int sdp2430_panel_enable_lcd(struct omap_dss_device *dssdev)
{
	gpio_direction_output(SDP2430_LCD_PANEL_ENABLE_GPIO, 1);
	gpio_direction_output(SDP2430_LCD_PANEL_BACKLIGHT_GPIO, 1);

	return 0;
}

static void sdp2430_panel_disable_lcd(struct omap_dss_device *dssdev)
{
	gpio_direction_output(SDP2430_LCD_PANEL_ENABLE_GPIO, 0);
	gpio_direction_output(SDP2430_LCD_PANEL_BACKLIGHT_GPIO, 0);
}

static struct panel_generic_dpi_data sdp2430_panel_data = {
	.name			= "nec_nl2432dr22-11b",
	.platform_enable	= sdp2430_panel_enable_lcd,
	.platform_disable	= sdp2430_panel_disable_lcd,
};

static struct omap_dss_device sdp2430_lcd_device = {
	.name			= "lcd",
	.driver_name		= "generic_dpi_panel",
	.type			= OMAP_DISPLAY_TYPE_DPI,
	.phy.dpi.data_lines	= 16,
	.data			= &sdp2430_panel_data,
};

static struct omap_dss_device *sdp2430_dss_devices[] = {
	&sdp2430_lcd_device,
};

static struct omap_dss_board_info sdp2430_dss_data = {
	.num_devices	= ARRAY_SIZE(sdp2430_dss_devices),
	.devices	= sdp2430_dss_devices,
	.default_device	= &sdp2430_lcd_device,
};

static void __init sdp2430_display_init(void)
{
	int r;

	static struct gpio gpios[] __initdata = {
		{ SDP2430_LCD_PANEL_ENABLE_GPIO, GPIOF_OUT_INIT_LOW,
			"LCD reset" },
		{ SDP2430_LCD_PANEL_BACKLIGHT_GPIO, GPIOF_OUT_INIT_LOW,
			"LCD Backlight" },
	};

	r = gpio_request_array(gpios, ARRAY_SIZE(gpios));
	if (r) {
		pr_err("Cannot request LCD GPIOs, error %d\n", r);
		return;
	}

	omap_display_init(&sdp2430_dss_data);
}

#if defined(CONFIG_SMC91X) || defined(CONFIG_SMC91x_MODULE)

static struct omap_smc91x_platform_data board_smc91x_data = {
	.cs		= 5,
	.gpio_irq	= 149,
	.flags		= GPMC_MUX_ADD_DATA | GPMC_TIMINGS_SMC91C96 |
				IORESOURCE_IRQ_LOWLEVEL,

};

static void __init board_smc91x_init(void)
{
	omap_mux_init_gpio(149, OMAP_PIN_INPUT);
	gpmc_smc91x_init(&board_smc91x_data);
}

#else

static inline void board_smc91x_init(void)
{
}

#endif

static struct regulator_consumer_supply sdp2430_vmmc1_supplies[] = {
	REGULATOR_SUPPLY("vmmc", "omap_hsmmc.0"),
};

/* VMMC1 for OMAP VDD_MMC1 (i/o) and MMC1 card */
static struct regulator_init_data sdp2430_vmmc1 = {
	.constraints = {
		.min_uV			= 1850000,
		.max_uV			= 3150000,
		.valid_modes_mask	= REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
		.valid_ops_mask		= REGULATOR_CHANGE_VOLTAGE
					| REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= ARRAY_SIZE(sdp2430_vmmc1_supplies),
	.consumer_supplies	= &sdp2430_vmmc1_supplies[0],
};

static struct twl4030_gpio_platform_data sdp2430_gpio_data = {
	.gpio_base	= OMAP_MAX_GPIO_LINES,
	.irq_base	= TWL4030_GPIO_IRQ_BASE,
	.irq_end	= TWL4030_GPIO_IRQ_END,
};

static struct twl4030_platform_data sdp2430_twldata = {
	.irq_base	= TWL4030_IRQ_BASE,
	.irq_end	= TWL4030_IRQ_END,

	/* platform_data for children goes here */
	.gpio		= &sdp2430_gpio_data,
	.vmmc1		= &sdp2430_vmmc1,
};

static struct i2c_board_info __initdata sdp2430_i2c1_boardinfo[] = {
	{
		I2C_BOARD_INFO("isp1301_omap", 0x2D),
		.flags = I2C_CLIENT_WAKE,
	},
};

static int __init omap2430_i2c_init(void)
{
	sdp2430_i2c1_boardinfo[0].irq = gpio_to_irq(78);
	omap_register_i2c_bus(1, 100, sdp2430_i2c1_boardinfo,
			ARRAY_SIZE(sdp2430_i2c1_boardinfo));
	omap_pmic_init(2, 100, "twl4030", INT_24XX_SYS_NIRQ,
			&sdp2430_twldata);
	return 0;
}

static struct omap2_hsmmc_info mmc[] __initdata = {
	{
		.mmc		= 1,
		.caps		= MMC_CAP_4_BIT_DATA,
		.gpio_cd	= -EINVAL,
		.gpio_wp	= -EINVAL,
		.ext_clock	= 1,
	},
	{}	/* Terminator */
};

static struct omap_usb_config sdp2430_usb_config __initdata = {
	.otg		= 1,
#ifdef  CONFIG_USB_GADGET_OMAP
	.hmc_mode	= 0x0,
#elif   defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
	.hmc_mode	= 0x1,
#endif
	.pins[0]	= 3,
};

#ifdef CONFIG_OMAP_MUX
static struct omap_board_mux board_mux[] __initdata = {
	{ .reg_offset = OMAP_MUX_TERMINATOR },
};
#endif

static void __init omap_2430sdp_init(void)
{
	omap2430_mux_init(board_mux, OMAP_PACKAGE_ZAC);

	omap2430_i2c_init();

	platform_add_devices(sdp2430_devices, ARRAY_SIZE(sdp2430_devices));
	omap_serial_init();
	omap_sdrc_init(NULL, NULL);
	omap_hsmmc_init(mmc);
	omap2_usbfs_init(&sdp2430_usb_config);

	omap_mux_init_signal("usb0hs_stp", OMAP_PULL_ENA | OMAP_PULL_UP);
	usb_musb_init(NULL);

	board_smc91x_init();

	/* Turn off secondary LCD backlight */
	gpio_request_one(SECONDARY_LCD_GPIO, GPIOF_OUT_INIT_LOW,
			 "Secondary LCD backlight");

	sdp2430_display_init();
}

MACHINE_START(OMAP_2430SDP, "OMAP2430 sdp2430 board")
	/* Maintainer: Syed Khasim - Texas Instruments Inc */
	.atag_offset	= 0x100,
	.reserve	= omap_reserve,
	.map_io		= omap243x_map_io,
	.init_early	= omap2430_init_early,
	.init_irq	= omap2_init_irq,
	.handle_irq	= omap2_intc_handle_irq,
	.init_machine	= omap_2430sdp_init,
	.timer		= &omap2_timer,
	.restart	= omap_prcm_restart,
MACHINE_END
