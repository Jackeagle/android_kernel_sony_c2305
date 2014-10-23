/*
 * Freescale GPMI NAND Flash Driver
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 * Copyright 2008 Embedded Alley Solutions, Inc.
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
#ifndef __GPMI_NAND_GPMI_REGS_H
#define __GPMI_NAND_GPMI_REGS_H

#define HW_GPMI_CTRL0					0x00000000
#define HW_GPMI_CTRL0_SET				0x00000004
#define HW_GPMI_CTRL0_CLR				0x00000008
#define HW_GPMI_CTRL0_TOG				0x0000000c

#define BP_GPMI_CTRL0_COMMAND_MODE			24
#define BM_GPMI_CTRL0_COMMAND_MODE	(3 << BP_GPMI_CTRL0_COMMAND_MODE)
#define BF_GPMI_CTRL0_COMMAND_MODE(v)	\
	(((v) << BP_GPMI_CTRL0_COMMAND_MODE) & BM_GPMI_CTRL0_COMMAND_MODE)
#define BV_GPMI_CTRL0_COMMAND_MODE__WRITE		0x0
#define BV_GPMI_CTRL0_COMMAND_MODE__READ		0x1
#define BV_GPMI_CTRL0_COMMAND_MODE__READ_AND_COMPARE	0x2
#define BV_GPMI_CTRL0_COMMAND_MODE__WAIT_FOR_READY	0x3

#define BM_GPMI_CTRL0_WORD_LENGTH			(1 << 23)
#define BV_GPMI_CTRL0_WORD_LENGTH__16_BIT		0x0
#define BV_GPMI_CTRL0_WORD_LENGTH__8_BIT		0x1

/*
 *  Difference in LOCK_CS between imx23 and imx28 :
 *  This bit may impact the _POWER_ consumption. So some chips
 *  do not set it.
 */
#define MX23_BP_GPMI_CTRL0_LOCK_CS			22
#define MX28_BP_GPMI_CTRL0_LOCK_CS			27
#define LOCK_CS_ENABLE					0x1
#define BF_GPMI_CTRL0_LOCK_CS(v, x)			0x0

/* Difference in CS between imx23 and imx28 */
#define BP_GPMI_CTRL0_CS				20
#define MX23_BM_GPMI_CTRL0_CS		(3 << BP_GPMI_CTRL0_CS)
#define MX28_BM_GPMI_CTRL0_CS		(7 << BP_GPMI_CTRL0_CS)
#define BF_GPMI_CTRL0_CS(v, x)		(((v) << BP_GPMI_CTRL0_CS) & \
						(GPMI_IS_MX23((x)) \
						? MX23_BM_GPMI_CTRL0_CS	\
						: MX28_BM_GPMI_CTRL0_CS))

#define BP_GPMI_CTRL0_ADDRESS				17
#define BM_GPMI_CTRL0_ADDRESS		(3 << BP_GPMI_CTRL0_ADDRESS)
#define BF_GPMI_CTRL0_ADDRESS(v)	\
		(((v) << BP_GPMI_CTRL0_ADDRESS) & BM_GPMI_CTRL0_ADDRESS)
#define BV_GPMI_CTRL0_ADDRESS__NAND_DATA		0x0
#define BV_GPMI_CTRL0_ADDRESS__NAND_CLE			0x1
#define BV_GPMI_CTRL0_ADDRESS__NAND_ALE			0x2

#define BM_GPMI_CTRL0_ADDRESS_INCREMENT			(1 << 16)
#define BV_GPMI_CTRL0_ADDRESS_INCREMENT__DISABLED	0x0
#define BV_GPMI_CTRL0_ADDRESS_INCREMENT__ENABLED	0x1

#define BP_GPMI_CTRL0_XFER_COUNT			0
#define BM_GPMI_CTRL0_XFER_COUNT	(0xffff << BP_GPMI_CTRL0_XFER_COUNT)
#define BF_GPMI_CTRL0_XFER_COUNT(v)	\
		(((v) << BP_GPMI_CTRL0_XFER_COUNT) & BM_GPMI_CTRL0_XFER_COUNT)

#define HW_GPMI_COMPARE					0x00000010

#define HW_GPMI_ECCCTRL					0x00000020
#define HW_GPMI_ECCCTRL_SET				0x00000024
#define HW_GPMI_ECCCTRL_CLR				0x00000028
#define HW_GPMI_ECCCTRL_TOG				0x0000002c

#define BP_GPMI_ECCCTRL_ECC_CMD				13
#define BM_GPMI_ECCCTRL_ECC_CMD		(3 << BP_GPMI_ECCCTRL_ECC_CMD)
#define BF_GPMI_ECCCTRL_ECC_CMD(v)	\
		(((v) << BP_GPMI_ECCCTRL_ECC_CMD) & BM_GPMI_ECCCTRL_ECC_CMD)
#define BV_GPMI_ECCCTRL_ECC_CMD__BCH_DECODE		0x0
#define BV_GPMI_ECCCTRL_ECC_CMD__BCH_ENCODE		0x1

#define BM_GPMI_ECCCTRL_ENABLE_ECC			(1 << 12)
#define BV_GPMI_ECCCTRL_ENABLE_ECC__ENABLE		0x1
#define BV_GPMI_ECCCTRL_ENABLE_ECC__DISABLE		0x0

#define BP_GPMI_ECCCTRL_BUFFER_MASK			0
#define BM_GPMI_ECCCTRL_BUFFER_MASK	(0x1ff << BP_GPMI_ECCCTRL_BUFFER_MASK)
#define BF_GPMI_ECCCTRL_BUFFER_MASK(v)	\
	(((v) << BP_GPMI_ECCCTRL_BUFFER_MASK) & BM_GPMI_ECCCTRL_BUFFER_MASK)
#define BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY	0x100
#define BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE		0x1FF

#define HW_GPMI_ECCCOUNT				0x00000030
#define HW_GPMI_PAYLOAD					0x00000040
#define HW_GPMI_AUXILIARY				0x00000050
#define HW_GPMI_CTRL1					0x00000060
#define HW_GPMI_CTRL1_SET				0x00000064
#define HW_GPMI_CTRL1_CLR				0x00000068
#define HW_GPMI_CTRL1_TOG				0x0000006c

#define BM_GPMI_CTRL1_BCH_MODE				(1 << 18)

#define BP_GPMI_CTRL1_DLL_ENABLE			17
#define BM_GPMI_CTRL1_DLL_ENABLE	(1 << BP_GPMI_CTRL1_DLL_ENABLE)

#define BP_GPMI_CTRL1_HALF_PERIOD			16
#define BM_GPMI_CTRL1_HALF_PERIOD	(1 << BP_GPMI_CTRL1_HALF_PERIOD)

#define BP_GPMI_CTRL1_RDN_DELAY				12
#define BM_GPMI_CTRL1_RDN_DELAY		(0xf << BP_GPMI_CTRL1_RDN_DELAY)
#define BF_GPMI_CTRL1_RDN_DELAY(v)	\
		(((v) << BP_GPMI_CTRL1_RDN_DELAY) & BM_GPMI_CTRL1_RDN_DELAY)

#define BM_GPMI_CTRL1_DEV_RESET				(1 << 3)
#define BV_GPMI_CTRL1_DEV_RESET__ENABLED		0x0
#define BV_GPMI_CTRL1_DEV_RESET__DISABLED		0x1

#define BM_GPMI_CTRL1_ATA_IRQRDY_POLARITY		(1 << 2)
#define BV_GPMI_CTRL1_ATA_IRQRDY_POLARITY__ACTIVELOW	0x0
#define BV_GPMI_CTRL1_ATA_IRQRDY_POLARITY__ACTIVEHIGH	0x1

#define BM_GPMI_CTRL1_CAMERA_MODE			(1 << 1)
#define BV_GPMI_CTRL1_GPMI_MODE__NAND			0x0
#define BV_GPMI_CTRL1_GPMI_MODE__ATA			0x1

#define BM_GPMI_CTRL1_GPMI_MODE				(1 << 0)

#define HW_GPMI_TIMING0					0x00000070

#define BP_GPMI_TIMING0_ADDRESS_SETUP			16
#define BM_GPMI_TIMING0_ADDRESS_SETUP	(0xff << BP_GPMI_TIMING0_ADDRESS_SETUP)
#define BF_GPMI_TIMING0_ADDRESS_SETUP(v)	\
	(((v) << BP_GPMI_TIMING0_ADDRESS_SETUP) & BM_GPMI_TIMING0_ADDRESS_SETUP)

#define BP_GPMI_TIMING0_DATA_HOLD			8
#define BM_GPMI_TIMING0_DATA_HOLD	(0xff << BP_GPMI_TIMING0_DATA_HOLD)
#define BF_GPMI_TIMING0_DATA_HOLD(v)		\
	(((v) << BP_GPMI_TIMING0_DATA_HOLD) & BM_GPMI_TIMING0_DATA_HOLD)

#define BP_GPMI_TIMING0_DATA_SETUP			0
#define BM_GPMI_TIMING0_DATA_SETUP	(0xff << BP_GPMI_TIMING0_DATA_SETUP)
#define BF_GPMI_TIMING0_DATA_SETUP(v)		\
	(((v) << BP_GPMI_TIMING0_DATA_SETUP) & BM_GPMI_TIMING0_DATA_SETUP)

#define HW_GPMI_TIMING1					0x00000080
#define BP_GPMI_TIMING1_BUSY_TIMEOUT			16

#define HW_GPMI_TIMING2					0x00000090
#define HW_GPMI_DATA					0x000000a0

/* MX28 uses this to detect READY. */
#define HW_GPMI_STAT					0x000000b0
#define MX28_BP_GPMI_STAT_READY_BUSY			24
#define MX28_BM_GPMI_STAT_READY_BUSY	(0xff << MX28_BP_GPMI_STAT_READY_BUSY)
#define MX28_BF_GPMI_STAT_READY_BUSY(v)		\
	(((v) << MX28_BP_GPMI_STAT_READY_BUSY) & MX28_BM_GPMI_STAT_READY_BUSY)

/* MX23 uses this to detect READY. */
#define HW_GPMI_DEBUG					0x000000c0
#define MX23_BP_GPMI_DEBUG_READY0			28
#define MX23_BM_GPMI_DEBUG_READY0	(1 << MX23_BP_GPMI_DEBUG_READY0)
#endif
