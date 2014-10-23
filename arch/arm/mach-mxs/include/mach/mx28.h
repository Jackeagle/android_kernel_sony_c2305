/*
 * Copyright (C) 2009-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __MACH_MX28_H__
#define __MACH_MX28_H__

#include <mach/mxs.h>

/*
 * OCRAM
 */
#define MX28_OCRAM_BASE_ADDR		0x00000000
#define MX28_OCRAM_SIZE			SZ_128K

/*
 * IO
 */
#define MX28_IO_BASE_ADDR		0x80000000
#define MX28_IO_SIZE			SZ_1M

#define MX28_ICOLL_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x000000)
#define MX28_HSADC_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x002000)
#define MX28_APBH_DMA_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x004000)
#define MX28_PERFMON_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x006000)
#define MX28_BCH_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x00a000)
#define MX28_GPMI_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x00c000)
#define MX28_SSP0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x010000)
#define MX28_SSP1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x012000)
#define MX28_SSP2_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x014000)
#define MX28_SSP3_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x016000)
#define MX28_PINCTRL_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x018000)
#define MX28_DIGCTL_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x01c000)
#define MX28_ETM_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x022000)
#define MX28_APBX_DMA_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x024000)
#define MX28_DCP_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x028000)
#define MX28_PXP_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x02a000)
#define MX28_OCOTP_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x02c000)
#define MX28_AXI_AHB0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x02e000)
#define MX28_LCDIF_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x030000)
#define MX28_CAN0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x032000)
#define MX28_CAN1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x034000)
#define MX28_SIMDBG_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x03c000)
#define MX28_SIMGPMISEL_BASE_ADDR	(MX28_IO_BASE_ADDR + 0x03c200)
#define MX28_SIMSSPSEL_BASE_ADDR	(MX28_IO_BASE_ADDR + 0x03c300)
#define MX28_SIMMEMSEL_BASE_ADDR	(MX28_IO_BASE_ADDR + 0x03c400)
#define MX28_GPIOMON_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x03c500)
#define MX28_SIMENET_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x03c700)
#define MX28_ARMJTAG_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x03c800)
#define MX28_CLKCTRL_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x040000)
#define MX28_SAIF0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x042000)
#define MX28_POWER_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x044000)
#define MX28_SAIF1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x046000)
#define MX28_LRADC_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x050000)
#define MX28_SPDIF_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x054000)
#define MX28_RTC_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x056000)
#define MX28_I2C0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x058000)
#define MX28_I2C1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x05a000)
#define MX28_PWM_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x064000)
#define MX28_TIMROT_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x068000)
#define MX28_AUART0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x06a000)
#define MX28_AUART1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x06c000)
#define MX28_AUART2_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x06e000)
#define MX28_AUART3_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x070000)
#define MX28_AUART4_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x072000)
#define MX28_DUART_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x074000)
#define MX28_USBPHY0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x07C000)
#define MX28_USBPHY1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x07e000)
#define MX28_USBCTRL0_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x080000)
#define MX28_USBCTRL1_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x090000)
#define MX28_DFLPT_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x0c0000)
#define MX28_DRAM_BASE_ADDR		(MX28_IO_BASE_ADDR + 0x0e0000)
#define MX28_ENET_MAC0_BASE_ADDR	(MX28_IO_BASE_ADDR + 0x0f0000)
#define MX28_ENET_MAC1_BASE_ADDR	(MX28_IO_BASE_ADDR + 0x0f4000)

#define MX28_IO_P2V(x)			MXS_IO_P2V(x)
#define MX28_IO_ADDRESS(x)		IOMEM(MX28_IO_P2V(x))

/*
 * IRQ
 */
#define MX28_INT_BATT_BRNOUT		0
#define MX28_INT_VDDD_BRNOUT		1
#define MX28_INT_VDDIO_BRNOUT		2
#define MX28_INT_VDDA_BRNOUT		3
#define MX28_INT_VDD5V_DROOP		4
#define MX28_INT_DCDC4P2_BRNOUT		5
#define MX28_INT_VDD5V			6
#define MX28_INT_CAN0			8
#define MX28_INT_CAN1			9
#define MX28_INT_LRADC_TOUCH		10
#define MX28_INT_HSADC			13
#define MX28_INT_LRADC_THRESH0		14
#define MX28_INT_LRADC_THRESH1		15
#define MX28_INT_LRADC_CH0		16
#define MX28_INT_LRADC_CH1		17
#define MX28_INT_LRADC_CH2		18
#define MX28_INT_LRADC_CH3		19
#define MX28_INT_LRADC_CH4		20
#define MX28_INT_LRADC_CH5		21
#define MX28_INT_LRADC_CH6		22
#define MX28_INT_LRADC_CH7		23
#define MX28_INT_LRADC_BUTTON0		24
#define MX28_INT_LRADC_BUTTON1		25
#define MX28_INT_PERFMON		27
#define MX28_INT_RTC_1MSEC		28
#define MX28_INT_RTC_ALARM		29
#define MX28_INT_COMMS			31
#define MX28_INT_EMI_ERR		32
#define MX28_INT_LCDIF			38
#define MX28_INT_PXP			39
#define MX28_INT_BCH			41
#define MX28_INT_GPMI			42
#define MX28_INT_SPDIF_ERROR		45
#define MX28_INT_DUART			47
#define MX28_INT_TIMER0			48
#define MX28_INT_TIMER1			49
#define MX28_INT_TIMER2			50
#define MX28_INT_TIMER3			51
#define MX28_INT_DCP_VMI		52
#define MX28_INT_DCP			53
#define MX28_INT_DCP_SECURE		54
#define MX28_INT_SAIF1			58
#define MX28_INT_SAIF0			59
#define MX28_INT_SPDIF_DMA		66
#define MX28_INT_I2C0_DMA		68
#define MX28_INT_I2C1_DMA		69
#define MX28_INT_AUART0_RX_DMA		70
#define MX28_INT_AUART0_TX_DMA		71
#define MX28_INT_AUART1_RX_DMA		72
#define MX28_INT_AUART1_TX_DMA		73
#define MX28_INT_AUART2_RX_DMA		74
#define MX28_INT_AUART2_TX_DMA		75
#define MX28_INT_AUART3_RX_DMA		76
#define MX28_INT_AUART3_TX_DMA		77
#define MX28_INT_AUART4_RX_DMA		78
#define MX28_INT_AUART4_TX_DMA		79
#define MX28_INT_SAIF0_DMA		80
#define MX28_INT_SAIF1_DMA		81
#define MX28_INT_SSP0_DMA		82
#define MX28_INT_SSP1_DMA		83
#define MX28_INT_SSP2_DMA		84
#define MX28_INT_SSP3_DMA		85
#define MX28_INT_LCDIF_DMA		86
#define MX28_INT_HSADC_DMA		87
#define MX28_INT_GPMI_DMA		88
#define MX28_INT_DIGCTL_DEBUG_TRAP	89
#define MX28_INT_USB1			92
#define MX28_INT_USB0			93
#define MX28_INT_USB1_WAKEUP		94
#define MX28_INT_USB0_WAKEUP		95
#define MX28_INT_SSP0_ERROR		96
#define MX28_INT_SSP1_ERROR		97
#define MX28_INT_SSP2_ERROR		98
#define MX28_INT_SSP3_ERROR		99
#define MX28_INT_ENET_SWI		100
#define MX28_INT_ENET_MAC0		101
#define MX28_INT_ENET_MAC1		102
#define MX28_INT_ENET_MAC0_1588		103
#define MX28_INT_ENET_MAC1_1588		104
#define MX28_INT_I2C1_ERROR		110
#define MX28_INT_I2C0_ERROR		111
#define MX28_INT_AUART0			112
#define MX28_INT_AUART1			113
#define MX28_INT_AUART2			114
#define MX28_INT_AUART3			115
#define MX28_INT_AUART4			116
#define MX28_INT_GPIO4			123
#define MX28_INT_GPIO3			124
#define MX28_INT_GPIO2			125
#define MX28_INT_GPIO1			126
#define MX28_INT_GPIO0			127

/*
 * APBH DMA
 */
#define MX28_DMA_SSP0			0
#define MX28_DMA_SSP1			1
#define MX28_DMA_SSP2			2
#define MX28_DMA_SSP3			3
#define MX28_DMA_GPMI0			4
#define MX28_DMA_GPMI1			5
#define MX28_DMA_GPMI2			6
#define MX28_DMA_GPMI3			7
#define MX28_DMA_GPMI4			8
#define MX28_DMA_GPMI5			9
#define MX28_DMA_GPMI6			10
#define MX28_DMA_GPMI7			11
#define MX28_DMA_HSADC			12
#define MX28_DMA_LCDIF			13

/*
 * APBX DMA
 */
#define MX28_DMA_AUART4_RX		0
#define MX28_DMA_AUART4_TX		1
#define MX28_DMA_SPDIF_TX		2
#define MX28_DMA_SAIF0			4
#define MX28_DMA_SAIF1			5
#define MX28_DMA_I2C0			6
#define MX28_DMA_I2C1			7
#define MX28_DMA_AUART0_RX		8
#define MX28_DMA_AUART0_TX		9
#define MX28_DMA_AUART1_RX		10
#define MX28_DMA_AUART1_TX		11
#define MX28_DMA_AUART2_RX		12
#define MX28_DMA_AUART2_TX		13
#define MX28_DMA_AUART3_RX		14
#define MX28_DMA_AUART3_TX		15

#endif /* __MACH_MX28_H__ */
