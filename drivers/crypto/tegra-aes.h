/*
 * Copyright (c) 2010, NVIDIA Corporation.
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

#ifndef __CRYPTODEV_TEGRA_AES_H
#define __CRYPTODEV_TEGRA_AES_H

#define TEGRA_AES_ICMDQUE_WR			0x1000
#define TEGRA_AES_CMDQUE_CONTROL		0x1008
#define TEGRA_AES_INTR_STATUS			0x1018
#define TEGRA_AES_INT_ENB			0x1040
#define TEGRA_AES_CONFIG			0x1044
#define TEGRA_AES_IRAM_ACCESS_CFG		0x10A0
#define TEGRA_AES_SECURE_DEST_ADDR		0x1100
#define TEGRA_AES_SECURE_INPUT_SELECT		0x1104
#define TEGRA_AES_SECURE_CONFIG			0x1108
#define TEGRA_AES_SECURE_CONFIG_EXT		0x110C
#define TEGRA_AES_SECURE_SECURITY		0x1110
#define TEGRA_AES_SECURE_HASH_RESULT0		0x1120
#define TEGRA_AES_SECURE_HASH_RESULT1		0x1124
#define TEGRA_AES_SECURE_HASH_RESULT2		0x1128
#define TEGRA_AES_SECURE_HASH_RESULT3		0x112C
#define TEGRA_AES_SECURE_SEC_SEL0		0x1140
#define TEGRA_AES_SECURE_SEC_SEL1		0x1144
#define TEGRA_AES_SECURE_SEC_SEL2		0x1148
#define TEGRA_AES_SECURE_SEC_SEL3		0x114C
#define TEGRA_AES_SECURE_SEC_SEL4		0x1150
#define TEGRA_AES_SECURE_SEC_SEL5		0x1154
#define TEGRA_AES_SECURE_SEC_SEL6		0x1158
#define TEGRA_AES_SECURE_SEC_SEL7		0x115C

/* interrupt status reg masks and shifts */
#define TEGRA_AES_ENGINE_BUSY_FIELD		BIT(0)
#define TEGRA_AES_ICQ_EMPTY_FIELD		BIT(3)
#define TEGRA_AES_DMA_BUSY_FIELD		BIT(23)

/* secure select reg masks and shifts */
#define TEGRA_AES_SECURE_SEL0_KEYREAD_ENB0_FIELD	BIT(0)

/* secure config ext masks and shifts */
#define TEGRA_AES_SECURE_KEY_SCH_DIS_FIELD	BIT(15)

/* secure config masks and shifts */
#define TEGRA_AES_SECURE_KEY_INDEX_SHIFT	20
#define TEGRA_AES_SECURE_KEY_INDEX_FIELD	(0x1F << TEGRA_AES_SECURE_KEY_INDEX_SHIFT)
#define TEGRA_AES_SECURE_BLOCK_CNT_SHIFT	0
#define TEGRA_AES_SECURE_BLOCK_CNT_FIELD	(0xFFFFF << TEGRA_AES_SECURE_BLOCK_CNT_SHIFT)

/* stream interface select masks and shifts */
#define TEGRA_AES_CMDQ_CTRL_UCMDQEN_FIELD	BIT(0)
#define TEGRA_AES_CMDQ_CTRL_ICMDQEN_FIELD	BIT(1)
#define TEGRA_AES_CMDQ_CTRL_SRC_STM_SEL_FIELD	BIT(4)
#define TEGRA_AES_CMDQ_CTRL_DST_STM_SEL_FIELD	BIT(5)

/* config register masks and shifts */
#define TEGRA_AES_CONFIG_ENDIAN_ENB_FIELD	BIT(10)
#define TEGRA_AES_CONFIG_MODE_SEL_SHIFT		0
#define TEGRA_AES_CONFIG_MODE_SEL_FIELD		(0x1F << TEGRA_AES_CONFIG_MODE_SEL_SHIFT)

/* extended config */
#define TEGRA_AES_SECURE_OFFSET_CNT_SHIFT	24
#define TEGRA_AES_SECURE_OFFSET_CNT_FIELD	(0xFF << TEGRA_AES_SECURE_OFFSET_CNT_SHIFT)
#define TEGRA_AES_SECURE_KEYSCHED_GEN_FIELD	BIT(15)

/* init vector select */
#define TEGRA_AES_SECURE_IV_SELECT_SHIFT	10
#define TEGRA_AES_SECURE_IV_SELECT_FIELD	BIT(10)

/* secure engine input */
#define TEGRA_AES_SECURE_INPUT_ALG_SEL_SHIFT	28
#define TEGRA_AES_SECURE_INPUT_ALG_SEL_FIELD	(0xF << TEGRA_AES_SECURE_INPUT_ALG_SEL_SHIFT)
#define TEGRA_AES_SECURE_INPUT_KEY_LEN_SHIFT	16
#define TEGRA_AES_SECURE_INPUT_KEY_LEN_FIELD	(0xFFF << TEGRA_AES_SECURE_INPUT_KEY_LEN_SHIFT)
#define TEGRA_AES_SECURE_RNG_ENB_FIELD		BIT(11)
#define TEGRA_AES_SECURE_CORE_SEL_SHIFT		9
#define TEGRA_AES_SECURE_CORE_SEL_FIELD		BIT(9)
#define TEGRA_AES_SECURE_VCTRAM_SEL_SHIFT	7
#define TEGRA_AES_SECURE_VCTRAM_SEL_FIELD	(0x3 << TEGRA_AES_SECURE_VCTRAM_SEL_SHIFT)
#define TEGRA_AES_SECURE_INPUT_SEL_SHIFT	5
#define TEGRA_AES_SECURE_INPUT_SEL_FIELD	(0x3 << TEGRA_AES_SECURE_INPUT_SEL_SHIFT)
#define TEGRA_AES_SECURE_XOR_POS_SHIFT		3
#define TEGRA_AES_SECURE_XOR_POS_FIELD		(0x3 << TEGRA_AES_SECURE_XOR_POS_SHIFT)
#define TEGRA_AES_SECURE_HASH_ENB_FIELD		BIT(2)
#define TEGRA_AES_SECURE_ON_THE_FLY_FIELD	BIT(0)

/* interrupt error mask */
#define TEGRA_AES_INT_ERROR_MASK		0xFFF000

#endif
