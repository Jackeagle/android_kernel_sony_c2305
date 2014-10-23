/*
 * Copyright (C) 2011  Renesas Solutions Corp.
 * Copyright (C) 2011  Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __ASM_R8A7740_H__
#define __ASM_R8A7740_H__

/*
 * MD_CKx pin
 */
#define MD_CK2	(1 << 2)
#define MD_CK1	(1 << 1)
#define MD_CK0	(1 << 0)

/*
 * Pin Function Controller:
 *	GPIO_FN_xx - GPIO used to select pin function
 *	GPIO_PORTxx - GPIO mapped to real I/O pin on CPU
 */
enum {
	/* PORT */
	GPIO_PORT0, GPIO_PORT1, GPIO_PORT2, GPIO_PORT3, GPIO_PORT4,
	GPIO_PORT5, GPIO_PORT6, GPIO_PORT7, GPIO_PORT8, GPIO_PORT9,

	GPIO_PORT10, GPIO_PORT11, GPIO_PORT12, GPIO_PORT13, GPIO_PORT14,
	GPIO_PORT15, GPIO_PORT16, GPIO_PORT17, GPIO_PORT18, GPIO_PORT19,

	GPIO_PORT20, GPIO_PORT21, GPIO_PORT22, GPIO_PORT23, GPIO_PORT24,
	GPIO_PORT25, GPIO_PORT26, GPIO_PORT27, GPIO_PORT28, GPIO_PORT29,

	GPIO_PORT30, GPIO_PORT31, GPIO_PORT32, GPIO_PORT33, GPIO_PORT34,
	GPIO_PORT35, GPIO_PORT36, GPIO_PORT37, GPIO_PORT38, GPIO_PORT39,

	GPIO_PORT40, GPIO_PORT41, GPIO_PORT42, GPIO_PORT43, GPIO_PORT44,
	GPIO_PORT45, GPIO_PORT46, GPIO_PORT47, GPIO_PORT48, GPIO_PORT49,

	GPIO_PORT50, GPIO_PORT51, GPIO_PORT52, GPIO_PORT53, GPIO_PORT54,
	GPIO_PORT55, GPIO_PORT56, GPIO_PORT57, GPIO_PORT58, GPIO_PORT59,

	GPIO_PORT60, GPIO_PORT61, GPIO_PORT62, GPIO_PORT63, GPIO_PORT64,
	GPIO_PORT65, GPIO_PORT66, GPIO_PORT67, GPIO_PORT68, GPIO_PORT69,

	GPIO_PORT70, GPIO_PORT71, GPIO_PORT72, GPIO_PORT73, GPIO_PORT74,
	GPIO_PORT75, GPIO_PORT76, GPIO_PORT77, GPIO_PORT78, GPIO_PORT79,

	GPIO_PORT80, GPIO_PORT81, GPIO_PORT82, GPIO_PORT83, GPIO_PORT84,
	GPIO_PORT85, GPIO_PORT86, GPIO_PORT87, GPIO_PORT88, GPIO_PORT89,

	GPIO_PORT90, GPIO_PORT91, GPIO_PORT92, GPIO_PORT93, GPIO_PORT94,
	GPIO_PORT95, GPIO_PORT96, GPIO_PORT97, GPIO_PORT98, GPIO_PORT99,

	GPIO_PORT100, GPIO_PORT101, GPIO_PORT102, GPIO_PORT103, GPIO_PORT104,
	GPIO_PORT105, GPIO_PORT106, GPIO_PORT107, GPIO_PORT108, GPIO_PORT109,

	GPIO_PORT110, GPIO_PORT111, GPIO_PORT112, GPIO_PORT113, GPIO_PORT114,
	GPIO_PORT115, GPIO_PORT116, GPIO_PORT117, GPIO_PORT118, GPIO_PORT119,

	GPIO_PORT120, GPIO_PORT121, GPIO_PORT122, GPIO_PORT123, GPIO_PORT124,
	GPIO_PORT125, GPIO_PORT126, GPIO_PORT127, GPIO_PORT128, GPIO_PORT129,

	GPIO_PORT130, GPIO_PORT131, GPIO_PORT132, GPIO_PORT133, GPIO_PORT134,
	GPIO_PORT135, GPIO_PORT136, GPIO_PORT137, GPIO_PORT138, GPIO_PORT139,

	GPIO_PORT140, GPIO_PORT141, GPIO_PORT142, GPIO_PORT143, GPIO_PORT144,
	GPIO_PORT145, GPIO_PORT146, GPIO_PORT147, GPIO_PORT148, GPIO_PORT149,

	GPIO_PORT150, GPIO_PORT151, GPIO_PORT152, GPIO_PORT153, GPIO_PORT154,
	GPIO_PORT155, GPIO_PORT156, GPIO_PORT157, GPIO_PORT158, GPIO_PORT159,

	GPIO_PORT160, GPIO_PORT161, GPIO_PORT162, GPIO_PORT163, GPIO_PORT164,
	GPIO_PORT165, GPIO_PORT166, GPIO_PORT167, GPIO_PORT168, GPIO_PORT169,

	GPIO_PORT170, GPIO_PORT171, GPIO_PORT172, GPIO_PORT173, GPIO_PORT174,
	GPIO_PORT175, GPIO_PORT176, GPIO_PORT177, GPIO_PORT178, GPIO_PORT179,

	GPIO_PORT180, GPIO_PORT181, GPIO_PORT182, GPIO_PORT183, GPIO_PORT184,
	GPIO_PORT185, GPIO_PORT186, GPIO_PORT187, GPIO_PORT188, GPIO_PORT189,

	GPIO_PORT190, GPIO_PORT191, GPIO_PORT192, GPIO_PORT193, GPIO_PORT194,
	GPIO_PORT195, GPIO_PORT196, GPIO_PORT197, GPIO_PORT198, GPIO_PORT199,

	GPIO_PORT200, GPIO_PORT201, GPIO_PORT202, GPIO_PORT203, GPIO_PORT204,
	GPIO_PORT205, GPIO_PORT206, GPIO_PORT207, GPIO_PORT208, GPIO_PORT209,

	GPIO_PORT210, GPIO_PORT211,

	/* IRQ */
	GPIO_FN_IRQ0_PORT2,	GPIO_FN_IRQ0_PORT13,
	GPIO_FN_IRQ1,
	GPIO_FN_IRQ2_PORT11,	GPIO_FN_IRQ2_PORT12,
	GPIO_FN_IRQ3_PORT10,	GPIO_FN_IRQ3_PORT14,
	GPIO_FN_IRQ4_PORT15,	GPIO_FN_IRQ4_PORT172,
	GPIO_FN_IRQ5_PORT0,	GPIO_FN_IRQ5_PORT1,
	GPIO_FN_IRQ6_PORT121,	GPIO_FN_IRQ6_PORT173,
	GPIO_FN_IRQ7_PORT120,	GPIO_FN_IRQ7_PORT209,
	GPIO_FN_IRQ8,
	GPIO_FN_IRQ9_PORT118,	GPIO_FN_IRQ9_PORT210,
	GPIO_FN_IRQ10,
	GPIO_FN_IRQ11,
	GPIO_FN_IRQ12_PORT42,	GPIO_FN_IRQ12_PORT97,
	GPIO_FN_IRQ13_PORT64,	GPIO_FN_IRQ13_PORT98,
	GPIO_FN_IRQ14_PORT63,	GPIO_FN_IRQ14_PORT99,
	GPIO_FN_IRQ15_PORT62,	GPIO_FN_IRQ15_PORT100,
	GPIO_FN_IRQ16_PORT68,	GPIO_FN_IRQ16_PORT211,
	GPIO_FN_IRQ17,
	GPIO_FN_IRQ18,
	GPIO_FN_IRQ19,
	GPIO_FN_IRQ20,
	GPIO_FN_IRQ21,
	GPIO_FN_IRQ22,
	GPIO_FN_IRQ23,
	GPIO_FN_IRQ24,
	GPIO_FN_IRQ25,
	GPIO_FN_IRQ26_PORT58,	GPIO_FN_IRQ26_PORT81,
	GPIO_FN_IRQ27_PORT57,	GPIO_FN_IRQ27_PORT168,
	GPIO_FN_IRQ28_PORT56,	GPIO_FN_IRQ28_PORT169,
	GPIO_FN_IRQ29_PORT50,	GPIO_FN_IRQ29_PORT170,
	GPIO_FN_IRQ30_PORT49,	GPIO_FN_IRQ30_PORT171,
	GPIO_FN_IRQ31_PORT41,	GPIO_FN_IRQ31_PORT167,

	/* Function */

	/* DBGT */
	GPIO_FN_DBGMDT2,	GPIO_FN_DBGMDT1,	GPIO_FN_DBGMDT0,
	GPIO_FN_DBGMD10,	GPIO_FN_DBGMD11,	GPIO_FN_DBGMD20,
	GPIO_FN_DBGMD21,

	/* FSI */
	GPIO_FN_FSIAISLD_PORT0,		/* FSIAISLD Port 0/5 */
	GPIO_FN_FSIAISLD_PORT5,
	GPIO_FN_FSIASPDIF_PORT9,	/* FSIASPDIF Port 9/18 */
	GPIO_FN_FSIASPDIF_PORT18,
	GPIO_FN_FSIAOSLD1,	GPIO_FN_FSIAOSLD2,
	GPIO_FN_FSIAOLR,	GPIO_FN_FSIAOBT,
	GPIO_FN_FSIAOSLD,	GPIO_FN_FSIAOMC,
	GPIO_FN_FSIACK,		GPIO_FN_FSIAILR,
	GPIO_FN_FSIAIBT,

	/* FMSI */
	GPIO_FN_FMSISLD_PORT1, /* FMSISLD Port 1/6 */
	GPIO_FN_FMSISLD_PORT6,
	GPIO_FN_FMSIILR,	GPIO_FN_FMSIIBT,
	GPIO_FN_FMSIOLR,	GPIO_FN_FMSIOBT,
	GPIO_FN_FMSICK,		GPIO_FN_FMSOILR,
	GPIO_FN_FMSOIBT,	GPIO_FN_FMSOOLR,
	GPIO_FN_FMSOOBT,	GPIO_FN_FMSOSLD,
	GPIO_FN_FMSOCK,

	/* SCIFA0 */
	GPIO_FN_SCIFA0_SCK,	GPIO_FN_SCIFA0_CTS,
	GPIO_FN_SCIFA0_RTS,	GPIO_FN_SCIFA0_RXD,
	GPIO_FN_SCIFA0_TXD,

	/* SCIFA1 */
	GPIO_FN_SCIFA1_CTS,	GPIO_FN_SCIFA1_SCK,
	GPIO_FN_SCIFA1_RXD,	GPIO_FN_SCIFA1_TXD,
	GPIO_FN_SCIFA1_RTS,

	/* SCIFA2 */
	GPIO_FN_SCIFA2_SCK_PORT22, /* SCIFA2_SCK Port 22/199 */
	GPIO_FN_SCIFA2_SCK_PORT199,
	GPIO_FN_SCIFA2_RXD,	GPIO_FN_SCIFA2_TXD,
	GPIO_FN_SCIFA2_CTS,	GPIO_FN_SCIFA2_RTS,

	/* SCIFA3 */
	GPIO_FN_SCIFA3_RTS_PORT105, /* MSEL5CR_8_0 */
	GPIO_FN_SCIFA3_SCK_PORT116,
	GPIO_FN_SCIFA3_CTS_PORT117,
	GPIO_FN_SCIFA3_RXD_PORT174,
	GPIO_FN_SCIFA3_TXD_PORT175,

	GPIO_FN_SCIFA3_RTS_PORT161, /* MSEL5CR_8_1 */
	GPIO_FN_SCIFA3_SCK_PORT158,
	GPIO_FN_SCIFA3_CTS_PORT162,
	GPIO_FN_SCIFA3_RXD_PORT159,
	GPIO_FN_SCIFA3_TXD_PORT160,

	/* SCIFA4 */
	GPIO_FN_SCIFA4_RXD_PORT12, /* MSEL5CR[12:11] = 00 */
	GPIO_FN_SCIFA4_TXD_PORT13,

	GPIO_FN_SCIFA4_RXD_PORT204, /* MSEL5CR[12:11] = 01 */
	GPIO_FN_SCIFA4_TXD_PORT203,

	GPIO_FN_SCIFA4_RXD_PORT94, /* MSEL5CR[12:11] = 10 */
	GPIO_FN_SCIFA4_TXD_PORT93,

	GPIO_FN_SCIFA4_SCK_PORT21, /* SCIFA4_SCK Port 21/205 */
	GPIO_FN_SCIFA4_SCK_PORT205,

	/* SCIFA5 */
	GPIO_FN_SCIFA5_TXD_PORT20, /* MSEL5CR[15:14] = 00 */
	GPIO_FN_SCIFA5_RXD_PORT10,

	GPIO_FN_SCIFA5_RXD_PORT207, /* MSEL5CR[15:14] = 01 */
	GPIO_FN_SCIFA5_TXD_PORT208,

	GPIO_FN_SCIFA5_TXD_PORT91, /* MSEL5CR[15:14] = 10 */
	GPIO_FN_SCIFA5_RXD_PORT92,

	GPIO_FN_SCIFA5_SCK_PORT23, /* SCIFA5_SCK Port 23/206 */
	GPIO_FN_SCIFA5_SCK_PORT206,

	/* SCIFA6 */
	GPIO_FN_SCIFA6_SCK,	GPIO_FN_SCIFA6_RXD,	GPIO_FN_SCIFA6_TXD,

	/* SCIFA7 */
	GPIO_FN_SCIFA7_TXD,	GPIO_FN_SCIFA7_RXD,

	/* SCIFAB */
	GPIO_FN_SCIFB_SCK_PORT190, /* MSEL5CR_17_0 */
	GPIO_FN_SCIFB_RXD_PORT191,
	GPIO_FN_SCIFB_TXD_PORT192,
	GPIO_FN_SCIFB_RTS_PORT186,
	GPIO_FN_SCIFB_CTS_PORT187,

	GPIO_FN_SCIFB_SCK_PORT2, /* MSEL5CR_17_1 */
	GPIO_FN_SCIFB_RXD_PORT3,
	GPIO_FN_SCIFB_TXD_PORT4,
	GPIO_FN_SCIFB_RTS_PORT172,
	GPIO_FN_SCIFB_CTS_PORT173,

	/* LCD0 */
	GPIO_FN_LCDC0_SELECT,
	GPIO_FN_LCD0_D0,	GPIO_FN_LCD0_D1,	GPIO_FN_LCD0_D2,
	GPIO_FN_LCD0_D3,	GPIO_FN_LCD0_D4,	GPIO_FN_LCD0_D5,
	GPIO_FN_LCD0_D6,	GPIO_FN_LCD0_D7,	GPIO_FN_LCD0_D8,
	GPIO_FN_LCD0_D9,	GPIO_FN_LCD0_D10,	GPIO_FN_LCD0_D11,
	GPIO_FN_LCD0_D12,	GPIO_FN_LCD0_D13,	GPIO_FN_LCD0_D14,
	GPIO_FN_LCD0_D15,	GPIO_FN_LCD0_D16,	GPIO_FN_LCD0_D17,
	GPIO_FN_LCD0_DON,	GPIO_FN_LCD0_VCPWC,	GPIO_FN_LCD0_VEPWC,

	GPIO_FN_LCD0_DCK,	GPIO_FN_LCD0_VSYN, /* for RGB */
	GPIO_FN_LCD0_HSYN,	GPIO_FN_LCD0_DISP, /* for RGB */

	GPIO_FN_LCD0_WR,	GPIO_FN_LCD0_RD, /* for SYS */
	GPIO_FN_LCD0_CS,	GPIO_FN_LCD0_RS, /* for SYS */

	GPIO_FN_LCD0_D18_PORT163,	GPIO_FN_LCD0_D19_PORT162,
	GPIO_FN_LCD0_D20_PORT161,	GPIO_FN_LCD0_D21_PORT158,
	GPIO_FN_LCD0_D22_PORT160,	GPIO_FN_LCD0_D23_PORT159,
	GPIO_FN_LCD0_LCLK_PORT165,	 /* MSEL5CR_6_1 */

	GPIO_FN_LCD0_D18_PORT40,	GPIO_FN_LCD0_D19_PORT4,
	GPIO_FN_LCD0_D20_PORT3,		GPIO_FN_LCD0_D21_PORT2,
	GPIO_FN_LCD0_D22_PORT0,		GPIO_FN_LCD0_D23_PORT1,
	GPIO_FN_LCD0_LCLK_PORT102,	/* MSEL5CR_6_0 */

	/* LCD1 */
	GPIO_FN_LCDC1_SELECT,
	GPIO_FN_LCD1_D0,	GPIO_FN_LCD1_D1,	GPIO_FN_LCD1_D2,
	GPIO_FN_LCD1_D3,	GPIO_FN_LCD1_D4,	GPIO_FN_LCD1_D5,
	GPIO_FN_LCD1_D6,	GPIO_FN_LCD1_D7,	GPIO_FN_LCD1_D8,
	GPIO_FN_LCD1_D9,	GPIO_FN_LCD1_D10,	GPIO_FN_LCD1_D11,
	GPIO_FN_LCD1_D12,	GPIO_FN_LCD1_D13,	GPIO_FN_LCD1_D14,
	GPIO_FN_LCD1_D15,	GPIO_FN_LCD1_D16,	GPIO_FN_LCD1_D17,
	GPIO_FN_LCD1_D18,	GPIO_FN_LCD1_D19,	GPIO_FN_LCD1_D20,
	GPIO_FN_LCD1_D21,	GPIO_FN_LCD1_D22,	GPIO_FN_LCD1_D23,
	GPIO_FN_LCD1_DON,	GPIO_FN_LCD1_VCPWC,
	GPIO_FN_LCD1_LCLK,	GPIO_FN_LCD1_VEPWC,

	GPIO_FN_LCD1_DCK,	GPIO_FN_LCD1_VSYN, /* for RGB */
	GPIO_FN_LCD1_HSYN,	GPIO_FN_LCD1_DISP, /* for RGB */

	GPIO_FN_LCD1_WR,	GPIO_FN_LCD1_RD, /* for SYS */
	GPIO_FN_LCD1_CS,	GPIO_FN_LCD1_RS, /* for SYS */

	/* RSPI */
	GPIO_FN_RSPI_SSL0_A,	GPIO_FN_RSPI_SSL1_A,
	GPIO_FN_RSPI_SSL2_A,	GPIO_FN_RSPI_SSL3_A,
	GPIO_FN_RSPI_MOSI_A,	GPIO_FN_RSPI_MISO_A,
	GPIO_FN_RSPI_CK_A,

	/* VIO CKO */
	GPIO_FN_VIO_CKO1,
	GPIO_FN_VIO_CKO2,
	GPIO_FN_VIO_CKO_1,
	GPIO_FN_VIO_CKO,

	/* VIO0 */
	GPIO_FN_VIO0_D0,	GPIO_FN_VIO0_D1,	GPIO_FN_VIO0_D2,
	GPIO_FN_VIO0_D3,	GPIO_FN_VIO0_D4,	GPIO_FN_VIO0_D5,
	GPIO_FN_VIO0_D6,	GPIO_FN_VIO0_D7,	GPIO_FN_VIO0_D8,
	GPIO_FN_VIO0_D9,	GPIO_FN_VIO0_D10,	GPIO_FN_VIO0_D11,
	GPIO_FN_VIO0_D12,	GPIO_FN_VIO0_VD,	GPIO_FN_VIO0_HD,
	GPIO_FN_VIO0_CLK,	GPIO_FN_VIO0_FIELD,

	GPIO_FN_VIO0_D13_PORT26, /* MSEL5CR_27_0 */
	GPIO_FN_VIO0_D14_PORT25,
	GPIO_FN_VIO0_D15_PORT24,

	GPIO_FN_VIO0_D13_PORT22, /* MSEL5CR_27_1 */
	GPIO_FN_VIO0_D14_PORT95,
	GPIO_FN_VIO0_D15_PORT96,

	/* VIO1 */
	GPIO_FN_VIO1_D0,	GPIO_FN_VIO1_D1,	GPIO_FN_VIO1_D2,
	GPIO_FN_VIO1_D3,	GPIO_FN_VIO1_D4,	GPIO_FN_VIO1_D5,
	GPIO_FN_VIO1_D6,	GPIO_FN_VIO1_D7,	GPIO_FN_VIO1_VD,
	GPIO_FN_VIO1_HD,	GPIO_FN_VIO1_CLK,	GPIO_FN_VIO1_FIELD,

	/* TPU0 */
	GPIO_FN_TPU0TO0,	GPIO_FN_TPU0TO1,
	GPIO_FN_TPU0TO3,
	GPIO_FN_TPU0TO2_PORT66, /* TPU0TO2 Port 66/202 */
	GPIO_FN_TPU0TO2_PORT202,

	/* SSP1 0 */
	GPIO_FN_STP0_IPD0,	GPIO_FN_STP0_IPD1,	GPIO_FN_STP0_IPD2,
	GPIO_FN_STP0_IPD3,	GPIO_FN_STP0_IPD4,	GPIO_FN_STP0_IPD5,
	GPIO_FN_STP0_IPD6,	GPIO_FN_STP0_IPD7,	GPIO_FN_STP0_IPEN,
	GPIO_FN_STP0_IPCLK,	GPIO_FN_STP0_IPSYNC,

	/* SSP1 1 */
	GPIO_FN_STP1_IPD1,	GPIO_FN_STP1_IPD2,	GPIO_FN_STP1_IPD3,
	GPIO_FN_STP1_IPD4,	GPIO_FN_STP1_IPD5,	GPIO_FN_STP1_IPD6,
	GPIO_FN_STP1_IPD7,	GPIO_FN_STP1_IPCLK,	GPIO_FN_STP1_IPSYNC,

	GPIO_FN_STP1_IPD0_PORT186, /* MSEL5CR_23_0 */
	GPIO_FN_STP1_IPEN_PORT187,

	GPIO_FN_STP1_IPD0_PORT194, /* MSEL5CR_23_1 */
	GPIO_FN_STP1_IPEN_PORT193,

	/* SIM */
	GPIO_FN_SIM_RST,	GPIO_FN_SIM_CLK,
	GPIO_FN_SIM_D_PORT22, /* SIM_D  Port 22/199 */
	GPIO_FN_SIM_D_PORT199,

	/* SDHI0 */
	GPIO_FN_SDHI0_D0,	GPIO_FN_SDHI0_D1,	GPIO_FN_SDHI0_D2,
	GPIO_FN_SDHI0_D3,	GPIO_FN_SDHI0_CD,	GPIO_FN_SDHI0_WP,
	GPIO_FN_SDHI0_CMD,	GPIO_FN_SDHI0_CLK,

	/* SDHI1 */
	GPIO_FN_SDHI1_D0,	GPIO_FN_SDHI1_D1,	GPIO_FN_SDHI1_D2,
	GPIO_FN_SDHI1_D3,	GPIO_FN_SDHI1_CD,	GPIO_FN_SDHI1_WP,
	GPIO_FN_SDHI1_CMD,	GPIO_FN_SDHI1_CLK,

	/* SDHI2 */
	GPIO_FN_SDHI2_D0,	GPIO_FN_SDHI2_D1,	GPIO_FN_SDHI2_D2,
	GPIO_FN_SDHI2_D3,	GPIO_FN_SDHI2_CLK,	GPIO_FN_SDHI2_CMD,

	GPIO_FN_SDHI2_CD_PORT24, /* MSEL5CR_19_0 */
	GPIO_FN_SDHI2_WP_PORT25,

	GPIO_FN_SDHI2_WP_PORT177, /* MSEL5CR_19_1 */
	GPIO_FN_SDHI2_CD_PORT202,

	/* MSIOF2 */
	GPIO_FN_MSIOF2_TXD,	GPIO_FN_MSIOF2_RXD,	GPIO_FN_MSIOF2_TSCK,
	GPIO_FN_MSIOF2_SS2,	GPIO_FN_MSIOF2_TSYNC,	GPIO_FN_MSIOF2_SS1,
	GPIO_FN_MSIOF2_MCK1,	GPIO_FN_MSIOF2_MCK0,	GPIO_FN_MSIOF2_RSYNC,
	GPIO_FN_MSIOF2_RSCK,

	/* KEYSC */
	GPIO_FN_KEYIN4,		GPIO_FN_KEYIN5,
	GPIO_FN_KEYIN6,		GPIO_FN_KEYIN7,
	GPIO_FN_KEYOUT0,	GPIO_FN_KEYOUT1,	GPIO_FN_KEYOUT2,
	GPIO_FN_KEYOUT3,	GPIO_FN_KEYOUT4,	GPIO_FN_KEYOUT5,
	GPIO_FN_KEYOUT6,	GPIO_FN_KEYOUT7,

	GPIO_FN_KEYIN0_PORT43, /* MSEL4CR_18_0 */
	GPIO_FN_KEYIN1_PORT44,
	GPIO_FN_KEYIN2_PORT45,
	GPIO_FN_KEYIN3_PORT46,

	GPIO_FN_KEYIN0_PORT58, /* MSEL4CR_18_1 */
	GPIO_FN_KEYIN1_PORT57,
	GPIO_FN_KEYIN2_PORT56,
	GPIO_FN_KEYIN3_PORT55,

	/* VOU */
	GPIO_FN_DV_D0,	GPIO_FN_DV_D1,	GPIO_FN_DV_D2,	GPIO_FN_DV_D3,
	GPIO_FN_DV_D4,	GPIO_FN_DV_D5,	GPIO_FN_DV_D6,	GPIO_FN_DV_D7,
	GPIO_FN_DV_D8,	GPIO_FN_DV_D9,	GPIO_FN_DV_D10,	GPIO_FN_DV_D11,
	GPIO_FN_DV_D12,	GPIO_FN_DV_D13,	GPIO_FN_DV_D14,	GPIO_FN_DV_D15,
	GPIO_FN_DV_CLK,
	GPIO_FN_DV_VSYNC,
	GPIO_FN_DV_HSYNC,

	/* MEMC */
	GPIO_FN_MEMC_AD0,	GPIO_FN_MEMC_AD1,	GPIO_FN_MEMC_AD2,
	GPIO_FN_MEMC_AD3,	GPIO_FN_MEMC_AD4,	GPIO_FN_MEMC_AD5,
	GPIO_FN_MEMC_AD6,	GPIO_FN_MEMC_AD7,	GPIO_FN_MEMC_AD8,
	GPIO_FN_MEMC_AD9,	GPIO_FN_MEMC_AD10,	GPIO_FN_MEMC_AD11,
	GPIO_FN_MEMC_AD12,	GPIO_FN_MEMC_AD13,	GPIO_FN_MEMC_AD14,
	GPIO_FN_MEMC_AD15,	GPIO_FN_MEMC_CS0,	GPIO_FN_MEMC_INT,
	GPIO_FN_MEMC_NWE,	GPIO_FN_MEMC_NOE,

	GPIO_FN_MEMC_CS1, /* MSEL4CR_6_0 */
	GPIO_FN_MEMC_ADV,
	GPIO_FN_MEMC_WAIT,
	GPIO_FN_MEMC_BUSCLK,

	GPIO_FN_MEMC_A1, /* MSEL4CR_6_1 */
	GPIO_FN_MEMC_DREQ0,
	GPIO_FN_MEMC_DREQ1,
	GPIO_FN_MEMC_A0,

	/* MMC */
	GPIO_FN_MMC0_D0_PORT68,		GPIO_FN_MMC0_D1_PORT69,
	GPIO_FN_MMC0_D2_PORT70,		GPIO_FN_MMC0_D3_PORT71,
	GPIO_FN_MMC0_D4_PORT72,		GPIO_FN_MMC0_D5_PORT73,
	GPIO_FN_MMC0_D6_PORT74,		GPIO_FN_MMC0_D7_PORT75,
	GPIO_FN_MMC0_CLK_PORT66,
	GPIO_FN_MMC0_CMD_PORT67,	/* MSEL4CR_15_0 */

	GPIO_FN_MMC1_D0_PORT149,	GPIO_FN_MMC1_D1_PORT148,
	GPIO_FN_MMC1_D2_PORT147,	GPIO_FN_MMC1_D3_PORT146,
	GPIO_FN_MMC1_D4_PORT145,	GPIO_FN_MMC1_D5_PORT144,
	GPIO_FN_MMC1_D6_PORT143,	GPIO_FN_MMC1_D7_PORT142,
	GPIO_FN_MMC1_CLK_PORT103,
	GPIO_FN_MMC1_CMD_PORT104,	/* MSEL4CR_15_1 */

	/* MSIOF0 */
	GPIO_FN_MSIOF0_SS1,	GPIO_FN_MSIOF0_SS2,
	GPIO_FN_MSIOF0_RXD,	GPIO_FN_MSIOF0_TXD,
	GPIO_FN_MSIOF0_MCK0,	GPIO_FN_MSIOF0_MCK1,
	GPIO_FN_MSIOF0_RSYNC,	GPIO_FN_MSIOF0_RSCK,
	GPIO_FN_MSIOF0_TSCK,	GPIO_FN_MSIOF0_TSYNC,

	/* MSIOF1 */
	GPIO_FN_MSIOF1_RSCK,	GPIO_FN_MSIOF1_RSYNC,
	GPIO_FN_MSIOF1_MCK0,	GPIO_FN_MSIOF1_MCK1,

	GPIO_FN_MSIOF1_SS2_PORT116,	GPIO_FN_MSIOF1_SS1_PORT117,
	GPIO_FN_MSIOF1_RXD_PORT118,	GPIO_FN_MSIOF1_TXD_PORT119,
	GPIO_FN_MSIOF1_TSYNC_PORT120,
	GPIO_FN_MSIOF1_TSCK_PORT121,	/* MSEL4CR_10_0 */

	GPIO_FN_MSIOF1_SS1_PORT67,	GPIO_FN_MSIOF1_TSCK_PORT72,
	GPIO_FN_MSIOF1_TSYNC_PORT73,	GPIO_FN_MSIOF1_TXD_PORT74,
	GPIO_FN_MSIOF1_RXD_PORT75,
	GPIO_FN_MSIOF1_SS2_PORT202,	/* MSEL4CR_10_1 */

	/* GPIO */
	GPIO_FN_GPO0,	GPIO_FN_GPI0,
	GPIO_FN_GPO1,	GPIO_FN_GPI1,

	/* USB0 */
	GPIO_FN_USB0_OCI,	GPIO_FN_USB0_PPON,	GPIO_FN_VBUS,

	/* USB1 */
	GPIO_FN_USB1_OCI,	GPIO_FN_USB1_PPON,

	/* BBIF1 */
	GPIO_FN_BBIF1_RXD,	GPIO_FN_BBIF1_TXD,	GPIO_FN_BBIF1_TSYNC,
	GPIO_FN_BBIF1_TSCK,	GPIO_FN_BBIF1_RSCK,	GPIO_FN_BBIF1_RSYNC,
	GPIO_FN_BBIF1_FLOW,	GPIO_FN_BBIF1_RX_FLOW_N,

	/* BBIF2 */
	GPIO_FN_BBIF2_TXD2_PORT5, /* MSEL5CR_0_0 */
	GPIO_FN_BBIF2_RXD2_PORT60,
	GPIO_FN_BBIF2_TSYNC2_PORT6,
	GPIO_FN_BBIF2_TSCK2_PORT59,

	GPIO_FN_BBIF2_RXD2_PORT90, /* MSEL5CR_0_1 */
	GPIO_FN_BBIF2_TXD2_PORT183,
	GPIO_FN_BBIF2_TSCK2_PORT89,
	GPIO_FN_BBIF2_TSYNC2_PORT184,

	/* BSC / FLCTL / PCMCIA */
	GPIO_FN_CS0,	GPIO_FN_CS2,	GPIO_FN_CS4,
	GPIO_FN_CS5B,	GPIO_FN_CS6A,
	GPIO_FN_CS5A_PORT105, /* CS5A PORT 19/105 */
	GPIO_FN_CS5A_PORT19,
	GPIO_FN_IOIS16, /* ? */

	GPIO_FN_A0,	GPIO_FN_A1,	GPIO_FN_A2,	GPIO_FN_A3,
	GPIO_FN_A4_FOE,		/* share with FLCTL */
	GPIO_FN_A5_FCDE,	/* share with FLCTL */
	GPIO_FN_A6,	GPIO_FN_A7,	GPIO_FN_A8,	GPIO_FN_A9,
	GPIO_FN_A10,	GPIO_FN_A11,	GPIO_FN_A12,	GPIO_FN_A13,
	GPIO_FN_A14,	GPIO_FN_A15,	GPIO_FN_A16,	GPIO_FN_A17,
	GPIO_FN_A18,	GPIO_FN_A19,	GPIO_FN_A20,	GPIO_FN_A21,
	GPIO_FN_A22,	GPIO_FN_A23,	GPIO_FN_A24,	GPIO_FN_A25,
	GPIO_FN_A26,

	GPIO_FN_D0_NAF0,	GPIO_FN_D1_NAF1,	/* share with FLCTL */
	GPIO_FN_D2_NAF2,	GPIO_FN_D3_NAF3,	/* share with FLCTL */
	GPIO_FN_D4_NAF4,	GPIO_FN_D5_NAF5,	/* share with FLCTL */
	GPIO_FN_D6_NAF6,	GPIO_FN_D7_NAF7,	/* share with FLCTL */
	GPIO_FN_D8_NAF8,	GPIO_FN_D9_NAF9,	/* share with FLCTL */
	GPIO_FN_D10_NAF10,	GPIO_FN_D11_NAF11,	/* share with FLCTL */
	GPIO_FN_D12_NAF12,	GPIO_FN_D13_NAF13,	/* share with FLCTL */
	GPIO_FN_D14_NAF14,	GPIO_FN_D15_NAF15,	/* share with FLCTL */

	GPIO_FN_D16,	GPIO_FN_D17,	GPIO_FN_D18,	GPIO_FN_D19,
	GPIO_FN_D20,	GPIO_FN_D21,	GPIO_FN_D22,	GPIO_FN_D23,
	GPIO_FN_D24,	GPIO_FN_D25,	GPIO_FN_D26,	GPIO_FN_D27,
	GPIO_FN_D28,	GPIO_FN_D29,	GPIO_FN_D30,	GPIO_FN_D31,

	GPIO_FN_WE0_FWE,	/* share with FLCTL */
	GPIO_FN_WE1,
	GPIO_FN_WE2_ICIORD,	/* share with PCMCIA */
	GPIO_FN_WE3_ICIOWR,	/* share with PCMCIA */
	GPIO_FN_CKO,	GPIO_FN_BS,	GPIO_FN_RDWR,
	GPIO_FN_RD_FSC,		/* share with FLCTL */
	GPIO_FN_WAIT_PORT177,	/* WAIT Port 90/177 */
	GPIO_FN_WAIT_PORT90,

	GPIO_FN_FCE0,	GPIO_FN_FCE1,	GPIO_FN_FRB, /* FLCTL */

	/* IRDA */
	GPIO_FN_IRDA_FIRSEL,	GPIO_FN_IRDA_IN,	GPIO_FN_IRDA_OUT,

	/* ATAPI */
	GPIO_FN_IDE_D0,		GPIO_FN_IDE_D1,		GPIO_FN_IDE_D2,
	GPIO_FN_IDE_D3,		GPIO_FN_IDE_D4,		GPIO_FN_IDE_D5,
	GPIO_FN_IDE_D6,		GPIO_FN_IDE_D7,		GPIO_FN_IDE_D8,
	GPIO_FN_IDE_D9,		GPIO_FN_IDE_D10,	GPIO_FN_IDE_D11,
	GPIO_FN_IDE_D12,	GPIO_FN_IDE_D13,	GPIO_FN_IDE_D14,
	GPIO_FN_IDE_D15,	GPIO_FN_IDE_A0,		GPIO_FN_IDE_A1,
	GPIO_FN_IDE_A2,		GPIO_FN_IDE_CS0,	GPIO_FN_IDE_CS1,
	GPIO_FN_IDE_IOWR,	GPIO_FN_IDE_IORD,	GPIO_FN_IDE_IORDY,
	GPIO_FN_IDE_INT,	GPIO_FN_IDE_RST,	GPIO_FN_IDE_DIRECTION,
	GPIO_FN_IDE_EXBUF_ENB,	GPIO_FN_IDE_IODACK,	GPIO_FN_IDE_IODREQ,

	/* RMII */
	GPIO_FN_RMII_CRS_DV,	GPIO_FN_RMII_RX_ER,	GPIO_FN_RMII_RXD0,
	GPIO_FN_RMII_RXD1,	GPIO_FN_RMII_TX_EN,	GPIO_FN_RMII_TXD0,
	GPIO_FN_RMII_MDC,	GPIO_FN_RMII_TXD1,	GPIO_FN_RMII_MDIO,
	GPIO_FN_RMII_REF50CK,	/* for RMII */
	GPIO_FN_RMII_REF125CK,	/* for GMII */

	/* GEther */
	GPIO_FN_ET_TX_CLK,	GPIO_FN_ET_TX_EN,	GPIO_FN_ET_ETXD0,
	GPIO_FN_ET_ETXD1,	GPIO_FN_ET_ETXD2,	GPIO_FN_ET_ETXD3,
	GPIO_FN_ET_ETXD4,	GPIO_FN_ET_ETXD5, /* for GEther */
	GPIO_FN_ET_ETXD6,	GPIO_FN_ET_ETXD7, /* for GEther */
	GPIO_FN_ET_COL,		GPIO_FN_ET_TX_ER,
	GPIO_FN_ET_RX_CLK,	GPIO_FN_ET_RX_DV,
	GPIO_FN_ET_ERXD0,	GPIO_FN_ET_ERXD1,
	GPIO_FN_ET_ERXD2,	GPIO_FN_ET_ERXD3,
	GPIO_FN_ET_ERXD4,	GPIO_FN_ET_ERXD5, /* for GEther */
	GPIO_FN_ET_ERXD6,	GPIO_FN_ET_ERXD7, /* for GEther */
	GPIO_FN_ET_RX_ER,	GPIO_FN_ET_CRS,
	GPIO_FN_ET_MDC,		GPIO_FN_ET_MDIO,
	GPIO_FN_ET_LINK,	GPIO_FN_ET_PHY_INT,
	GPIO_FN_ET_WOL,		GPIO_FN_ET_GTX_CLK,

	/* DMA0 */
	GPIO_FN_DREQ0,		GPIO_FN_DACK0,

	/* DMA1 */
	GPIO_FN_DREQ1,		GPIO_FN_DACK1,

	/* SYSC */
	GPIO_FN_RESETOUTS,
	GPIO_FN_RESETP_PULLUP,
	GPIO_FN_RESETP_PLAIN,

	/* SDENC */
	GPIO_FN_SDENC_CPG,
	GPIO_FN_SDENC_DV_CLKI,

	/* IRREM */
	GPIO_FN_IROUT,

	/* DEBUG */
	GPIO_FN_EDEBGREQ_PULLDOWN,
	GPIO_FN_EDEBGREQ_PULLUP,

	GPIO_FN_TRACEAUD_FROM_VIO,
	GPIO_FN_TRACEAUD_FROM_LCDC0,
	GPIO_FN_TRACEAUD_FROM_MEMC,
};

#endif /* __ASM_R8A7740_H__ */
