#ifndef __ASM_SH73A0_H__
#define __ASM_SH73A0_H__

/* Pin Function Controller:
 * GPIO_FN_xx - GPIO used to select pin function and MSEL switch
 * GPIO_PORTxx - GPIO mapped to real I/O pin on CPU
 */
enum {
	/* Hardware manual Table 25-1 (GPIO) */
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
	GPIO_PORT115, GPIO_PORT116, GPIO_PORT117, GPIO_PORT118,

	GPIO_PORT128, GPIO_PORT129,

	GPIO_PORT130, GPIO_PORT131, GPIO_PORT132, GPIO_PORT133, GPIO_PORT134,
	GPIO_PORT135, GPIO_PORT136, GPIO_PORT137, GPIO_PORT138, GPIO_PORT139,

	GPIO_PORT140, GPIO_PORT141, GPIO_PORT142, GPIO_PORT143, GPIO_PORT144,
	GPIO_PORT145, GPIO_PORT146, GPIO_PORT147, GPIO_PORT148, GPIO_PORT149,

	GPIO_PORT150, GPIO_PORT151, GPIO_PORT152, GPIO_PORT153, GPIO_PORT154,
	GPIO_PORT155, GPIO_PORT156, GPIO_PORT157, GPIO_PORT158, GPIO_PORT159,

	GPIO_PORT160, GPIO_PORT161, GPIO_PORT162, GPIO_PORT163, GPIO_PORT164,

	GPIO_PORT192, GPIO_PORT193, GPIO_PORT194,
	GPIO_PORT195, GPIO_PORT196, GPIO_PORT197, GPIO_PORT198, GPIO_PORT199,

	GPIO_PORT200, GPIO_PORT201, GPIO_PORT202, GPIO_PORT203, GPIO_PORT204,
	GPIO_PORT205, GPIO_PORT206, GPIO_PORT207, GPIO_PORT208, GPIO_PORT209,

	GPIO_PORT210, GPIO_PORT211, GPIO_PORT212, GPIO_PORT213, GPIO_PORT214,
	GPIO_PORT215, GPIO_PORT216, GPIO_PORT217, GPIO_PORT218, GPIO_PORT219,

	GPIO_PORT220, GPIO_PORT221, GPIO_PORT222, GPIO_PORT223, GPIO_PORT224,
	GPIO_PORT225, GPIO_PORT226, GPIO_PORT227, GPIO_PORT228, GPIO_PORT229,

	GPIO_PORT230, GPIO_PORT231, GPIO_PORT232, GPIO_PORT233, GPIO_PORT234,
	GPIO_PORT235, GPIO_PORT236, GPIO_PORT237, GPIO_PORT238, GPIO_PORT239,

	GPIO_PORT240, GPIO_PORT241, GPIO_PORT242, GPIO_PORT243, GPIO_PORT244,
	GPIO_PORT245, GPIO_PORT246, GPIO_PORT247, GPIO_PORT248, GPIO_PORT249,

	GPIO_PORT250, GPIO_PORT251, GPIO_PORT252, GPIO_PORT253, GPIO_PORT254,
	GPIO_PORT255, GPIO_PORT256, GPIO_PORT257, GPIO_PORT258, GPIO_PORT259,

	GPIO_PORT260, GPIO_PORT261, GPIO_PORT262, GPIO_PORT263, GPIO_PORT264,
	GPIO_PORT265, GPIO_PORT266, GPIO_PORT267, GPIO_PORT268, GPIO_PORT269,

	GPIO_PORT270, GPIO_PORT271, GPIO_PORT272, GPIO_PORT273, GPIO_PORT274,
	GPIO_PORT275, GPIO_PORT276, GPIO_PORT277, GPIO_PORT278, GPIO_PORT279,

	GPIO_PORT280, GPIO_PORT281, GPIO_PORT282,

	GPIO_PORT288, GPIO_PORT289,

	GPIO_PORT290, GPIO_PORT291, GPIO_PORT292, GPIO_PORT293, GPIO_PORT294,
	GPIO_PORT295, GPIO_PORT296, GPIO_PORT297, GPIO_PORT298, GPIO_PORT299,

	GPIO_PORT300, GPIO_PORT301, GPIO_PORT302, GPIO_PORT303, GPIO_PORT304,
	GPIO_PORT305, GPIO_PORT306, GPIO_PORT307, GPIO_PORT308, GPIO_PORT309,

	/* Table 25-1 (Function 0-7) */
	GPIO_FN_VBUS_0,
	GPIO_FN_GPI0,
	GPIO_FN_GPI1,
	GPIO_FN_GPI2,
	GPIO_FN_GPI3,
	GPIO_FN_GPI4,
	GPIO_FN_GPI5,
	GPIO_FN_GPI6,
	GPIO_FN_GPI7,
	GPIO_FN_SCIFA7_RXD,
	GPIO_FN_SCIFA7_CTS_,
	GPIO_FN_GPO7, GPIO_FN_MFG0_OUT2,
	GPIO_FN_GPO6, GPIO_FN_MFG1_OUT2,
	GPIO_FN_GPO5, GPIO_FN_SCIFA0_SCK, GPIO_FN_FSICOSLDT3, \
	GPIO_FN_PORT16_VIO_CKOR,
	GPIO_FN_SCIFA0_TXD,
	GPIO_FN_SCIFA7_TXD,
	GPIO_FN_SCIFA7_RTS_, GPIO_FN_PORT19_VIO_CKO2,
	GPIO_FN_GPO0,
	GPIO_FN_GPO1,
	GPIO_FN_GPO2, GPIO_FN_STATUS0,
	GPIO_FN_GPO3, GPIO_FN_STATUS1,
	GPIO_FN_GPO4, GPIO_FN_STATUS2,
	GPIO_FN_VINT,
	GPIO_FN_TCKON,
	GPIO_FN_XDVFS1, GPIO_FN_PORT27_I2C_SCL2, GPIO_FN_PORT27_I2C_SCL3, \
	GPIO_FN_MFG0_OUT1, GPIO_FN_PORT27_IROUT,
	GPIO_FN_XDVFS2, GPIO_FN_PORT28_I2C_SDA2, GPIO_FN_PORT28_I2C_SDA3, \
	GPIO_FN_PORT28_TPU1TO1,
	GPIO_FN_SIM_RST, GPIO_FN_PORT29_TPU1TO1,
	GPIO_FN_SIM_CLK, GPIO_FN_PORT30_VIO_CKOR,
	GPIO_FN_SIM_D, GPIO_FN_PORT31_IROUT,
	GPIO_FN_SCIFA4_TXD,
	GPIO_FN_SCIFA4_RXD, GPIO_FN_XWUP,
	GPIO_FN_SCIFA4_RTS_,
	GPIO_FN_SCIFA4_CTS_,
	GPIO_FN_FSIBOBT, GPIO_FN_FSIBIBT,
	GPIO_FN_FSIBOLR, GPIO_FN_FSIBILR,
	GPIO_FN_FSIBOSLD,
	GPIO_FN_FSIBISLD,
	GPIO_FN_VACK,
	GPIO_FN_XTAL1L,
	GPIO_FN_SCIFA0_RTS_, GPIO_FN_FSICOSLDT2,
	GPIO_FN_SCIFA0_RXD,
	GPIO_FN_SCIFA0_CTS_, GPIO_FN_FSICOSLDT1,
	GPIO_FN_FSICOBT, GPIO_FN_FSICIBT, GPIO_FN_FSIDOBT, GPIO_FN_FSIDIBT,
	GPIO_FN_FSICOLR, GPIO_FN_FSICILR, GPIO_FN_FSIDOLR, GPIO_FN_FSIDILR,
	GPIO_FN_FSICOSLD, GPIO_FN_PORT47_FSICSPDIF,
	GPIO_FN_FSICISLD, GPIO_FN_FSIDISLD,
	GPIO_FN_FSIACK, GPIO_FN_PORT49_IRDA_OUT, GPIO_FN_PORT49_IROUT, \
	GPIO_FN_FSIAOMC,
	GPIO_FN_FSIAOLR, GPIO_FN_BBIF2_TSYNC2, GPIO_FN_TPU2TO2, GPIO_FN_FSIAILR,

	GPIO_FN_FSIAOBT, GPIO_FN_BBIF2_TSCK2, GPIO_FN_TPU2TO3, GPIO_FN_FSIAIBT,
	GPIO_FN_FSIAOSLD, GPIO_FN_BBIF2_TXD2,
	GPIO_FN_FSIASPDIF, GPIO_FN_PORT53_IRDA_IN, GPIO_FN_TPU3TO3, \
	GPIO_FN_FSIBSPDIF, GPIO_FN_PORT53_FSICSPDIF,
	GPIO_FN_FSIBCK, GPIO_FN_PORT54_IRDA_FIRSEL, GPIO_FN_TPU3TO2, \
	GPIO_FN_FSIBOMC, GPIO_FN_FSICCK, GPIO_FN_FSICOMC,
	GPIO_FN_FSIAISLD, GPIO_FN_TPU0TO0,
	GPIO_FN_A0, GPIO_FN_BS_,
	GPIO_FN_A12, GPIO_FN_PORT58_KEYOUT7, GPIO_FN_TPU4TO2,
	GPIO_FN_A13, GPIO_FN_PORT59_KEYOUT6, GPIO_FN_TPU0TO1,
	GPIO_FN_A14, GPIO_FN_KEYOUT5,
	GPIO_FN_A15, GPIO_FN_KEYOUT4,
	GPIO_FN_A16, GPIO_FN_KEYOUT3, GPIO_FN_MSIOF0_SS1,
	GPIO_FN_A17, GPIO_FN_KEYOUT2, GPIO_FN_MSIOF0_TSYNC,
	GPIO_FN_A18, GPIO_FN_KEYOUT1, GPIO_FN_MSIOF0_TSCK,
	GPIO_FN_A19, GPIO_FN_KEYOUT0, GPIO_FN_MSIOF0_TXD,
	GPIO_FN_A20, GPIO_FN_KEYIN0, GPIO_FN_MSIOF0_RSCK,
	GPIO_FN_A21, GPIO_FN_KEYIN1, GPIO_FN_MSIOF0_RSYNC,
	GPIO_FN_A22, GPIO_FN_KEYIN2, GPIO_FN_MSIOF0_MCK0,
	GPIO_FN_A23, GPIO_FN_KEYIN3, GPIO_FN_MSIOF0_MCK1,
	GPIO_FN_A24, GPIO_FN_KEYIN4, GPIO_FN_MSIOF0_RXD,
	GPIO_FN_A25, GPIO_FN_KEYIN5, GPIO_FN_MSIOF0_SS2,
	GPIO_FN_A26, GPIO_FN_KEYIN6,
	GPIO_FN_KEYIN7,
	GPIO_FN_D0_NAF0,
	GPIO_FN_D1_NAF1,
	GPIO_FN_D2_NAF2,
	GPIO_FN_D3_NAF3,
	GPIO_FN_D4_NAF4,
	GPIO_FN_D5_NAF5,
	GPIO_FN_D6_NAF6,
	GPIO_FN_D7_NAF7,
	GPIO_FN_D8_NAF8,
	GPIO_FN_D9_NAF9,
	GPIO_FN_D10_NAF10,
	GPIO_FN_D11_NAF11,
	GPIO_FN_D12_NAF12,
	GPIO_FN_D13_NAF13,
	GPIO_FN_D14_NAF14,
	GPIO_FN_D15_NAF15,
	GPIO_FN_CS4_,
	GPIO_FN_CS5A_, GPIO_FN_PORT91_RDWR,
	GPIO_FN_CS5B_, GPIO_FN_FCE1_,
	GPIO_FN_CS6B_, GPIO_FN_DACK0,
	GPIO_FN_FCE0_, GPIO_FN_CS6A_,
	GPIO_FN_WAIT_, GPIO_FN_DREQ0,
	GPIO_FN_RD__FSC,
	GPIO_FN_WE0__FWE, GPIO_FN_RDWR_FWE,
	GPIO_FN_WE1_,
	GPIO_FN_FRB,
	GPIO_FN_CKO,
	GPIO_FN_NBRSTOUT_,
	GPIO_FN_NBRST_,
	GPIO_FN_BBIF2_TXD,
	GPIO_FN_BBIF2_RXD,
	GPIO_FN_BBIF2_SYNC,
	GPIO_FN_BBIF2_SCK,
	GPIO_FN_SCIFA3_CTS_, GPIO_FN_MFG3_IN2,
	GPIO_FN_SCIFA3_RXD, GPIO_FN_MFG3_IN1,
	GPIO_FN_BBIF1_SS2, GPIO_FN_SCIFA3_RTS_, GPIO_FN_MFG3_OUT1,
	GPIO_FN_SCIFA3_TXD,
	GPIO_FN_HSI_RX_DATA, GPIO_FN_BBIF1_RXD,
	GPIO_FN_HSI_TX_WAKE, GPIO_FN_BBIF1_TSCK,
	GPIO_FN_HSI_TX_DATA, GPIO_FN_BBIF1_TSYNC,
	GPIO_FN_HSI_TX_READY, GPIO_FN_BBIF1_TXD,
	GPIO_FN_HSI_RX_READY, GPIO_FN_BBIF1_RSCK, GPIO_FN_PORT115_I2C_SCL2, \
	GPIO_FN_PORT115_I2C_SCL3,
	GPIO_FN_HSI_RX_WAKE, GPIO_FN_BBIF1_RSYNC, GPIO_FN_PORT116_I2C_SDA2, \
	GPIO_FN_PORT116_I2C_SDA3,
	GPIO_FN_HSI_RX_FLAG, GPIO_FN_BBIF1_SS1, GPIO_FN_BBIF1_FLOW,
	GPIO_FN_HSI_TX_FLAG,
	GPIO_FN_VIO_VD, GPIO_FN_PORT128_LCD2VSYN, GPIO_FN_VIO2_VD, \
	GPIO_FN_LCD2D0,

	GPIO_FN_VIO_HD, GPIO_FN_PORT129_LCD2HSYN, GPIO_FN_PORT129_LCD2CS_, \
	GPIO_FN_VIO2_HD, GPIO_FN_LCD2D1,
	GPIO_FN_VIO_D0, GPIO_FN_PORT130_MSIOF2_RXD, GPIO_FN_LCD2D10,
	GPIO_FN_VIO_D1, GPIO_FN_PORT131_KEYOUT6, GPIO_FN_PORT131_MSIOF2_SS1, \
	GPIO_FN_PORT131_KEYOUT11, GPIO_FN_LCD2D11,
	GPIO_FN_VIO_D2, GPIO_FN_PORT132_KEYOUT7, GPIO_FN_PORT132_MSIOF2_SS2, \
	GPIO_FN_PORT132_KEYOUT10, GPIO_FN_LCD2D12,
	GPIO_FN_VIO_D3, GPIO_FN_MSIOF2_TSYNC, GPIO_FN_LCD2D13,
	GPIO_FN_VIO_D4, GPIO_FN_MSIOF2_TXD, GPIO_FN_LCD2D14,
	GPIO_FN_VIO_D5, GPIO_FN_MSIOF2_TSCK, GPIO_FN_LCD2D15,
	GPIO_FN_VIO_D6, GPIO_FN_PORT136_KEYOUT8, GPIO_FN_LCD2D16,
	GPIO_FN_VIO_D7, GPIO_FN_PORT137_KEYOUT9, GPIO_FN_LCD2D17,
	GPIO_FN_VIO_D8, GPIO_FN_PORT138_KEYOUT8, GPIO_FN_VIO2_D0, \
	GPIO_FN_LCD2D6,
	GPIO_FN_VIO_D9, GPIO_FN_PORT139_KEYOUT9, GPIO_FN_VIO2_D1, \
	GPIO_FN_LCD2D7,
	GPIO_FN_VIO_D10, GPIO_FN_TPU0TO2, GPIO_FN_VIO2_D2, GPIO_FN_LCD2D8,
	GPIO_FN_VIO_D11, GPIO_FN_TPU0TO3, GPIO_FN_VIO2_D3, GPIO_FN_LCD2D9,
	GPIO_FN_VIO_D12, GPIO_FN_PORT142_KEYOUT10, GPIO_FN_VIO2_D4, \
	GPIO_FN_LCD2D2,
	GPIO_FN_VIO_D13, GPIO_FN_PORT143_KEYOUT11, GPIO_FN_PORT143_KEYOUT6, \
	GPIO_FN_VIO2_D5, GPIO_FN_LCD2D3,
	GPIO_FN_VIO_D14, GPIO_FN_PORT144_KEYOUT7, GPIO_FN_VIO2_D6, \
	GPIO_FN_LCD2D4,
	GPIO_FN_VIO_D15, GPIO_FN_TPU1TO3, GPIO_FN_PORT145_LCD2DISP, \
	GPIO_FN_PORT145_LCD2RS, GPIO_FN_VIO2_D7, GPIO_FN_LCD2D5,
	GPIO_FN_VIO_CLK, GPIO_FN_LCD2DCK, GPIO_FN_PORT146_LCD2WR_, \
	GPIO_FN_VIO2_CLK, GPIO_FN_LCD2D18,
	GPIO_FN_VIO_FIELD, GPIO_FN_LCD2RD_, GPIO_FN_VIO2_FIELD, GPIO_FN_LCD2D19,
	GPIO_FN_VIO_CKO,
	GPIO_FN_A27, GPIO_FN_PORT149_RDWR, GPIO_FN_MFG0_IN1, \
	GPIO_FN_PORT149_KEYOUT9,
	GPIO_FN_MFG0_IN2,
	GPIO_FN_TS_SPSYNC3, GPIO_FN_MSIOF2_RSCK,
	GPIO_FN_TS_SDAT3, GPIO_FN_MSIOF2_RSYNC,
	GPIO_FN_TPU1TO2, GPIO_FN_TS_SDEN3, GPIO_FN_PORT153_MSIOF2_SS1,
	GPIO_FN_SCIFA2_TXD1, GPIO_FN_MSIOF2_MCK0,
	GPIO_FN_SCIFA2_RXD1, GPIO_FN_MSIOF2_MCK1,
	GPIO_FN_SCIFA2_RTS1_, GPIO_FN_PORT156_MSIOF2_SS2,
	GPIO_FN_SCIFA2_CTS1_, GPIO_FN_PORT157_MSIOF2_RXD,
	GPIO_FN_DINT_, GPIO_FN_SCIFA2_SCK1, GPIO_FN_TS_SCK3,
	GPIO_FN_PORT159_SCIFB_SCK, GPIO_FN_PORT159_SCIFA5_SCK, GPIO_FN_NMI,
	GPIO_FN_PORT160_SCIFB_TXD, GPIO_FN_PORT160_SCIFA5_TXD,
	GPIO_FN_PORT161_SCIFB_CTS_, GPIO_FN_PORT161_SCIFA5_CTS_,
	GPIO_FN_PORT162_SCIFB_RXD, GPIO_FN_PORT162_SCIFA5_RXD,
	GPIO_FN_PORT163_SCIFB_RTS_, GPIO_FN_PORT163_SCIFA5_RTS_, \
	GPIO_FN_TPU3TO0,
	GPIO_FN_LCDD0,
	GPIO_FN_LCDD1, GPIO_FN_PORT193_SCIFA5_CTS_, GPIO_FN_BBIF2_TSYNC1,
	GPIO_FN_LCDD2, GPIO_FN_PORT194_SCIFA5_RTS_, GPIO_FN_BBIF2_TSCK1,
	GPIO_FN_LCDD3, GPIO_FN_PORT195_SCIFA5_RXD, GPIO_FN_BBIF2_TXD1,
	GPIO_FN_LCDD4, GPIO_FN_PORT196_SCIFA5_TXD,
	GPIO_FN_LCDD5, GPIO_FN_PORT197_SCIFA5_SCK, GPIO_FN_MFG2_OUT2, \
	GPIO_FN_TPU2TO1,
	GPIO_FN_LCDD6,
	GPIO_FN_LCDD7, GPIO_FN_TPU4TO1, GPIO_FN_MFG4_OUT2,
	GPIO_FN_LCDD8, GPIO_FN_D16,
	GPIO_FN_LCDD9, GPIO_FN_D17,
	GPIO_FN_LCDD10, GPIO_FN_D18,
	GPIO_FN_LCDD11, GPIO_FN_D19,
	GPIO_FN_LCDD12, GPIO_FN_D20,
	GPIO_FN_LCDD13, GPIO_FN_D21,
	GPIO_FN_LCDD14, GPIO_FN_D22,
	GPIO_FN_LCDD15, GPIO_FN_PORT207_MSIOF0L_SS1, GPIO_FN_D23,
	GPIO_FN_LCDD16, GPIO_FN_PORT208_MSIOF0L_SS2, GPIO_FN_D24,
	GPIO_FN_LCDD17, GPIO_FN_D25,
	GPIO_FN_LCDD18, GPIO_FN_DREQ2, GPIO_FN_PORT210_MSIOF0L_SS1, GPIO_FN_D26,
	GPIO_FN_LCDD19, GPIO_FN_PORT211_MSIOF0L_SS2, GPIO_FN_D27,
	GPIO_FN_LCDD20, GPIO_FN_TS_SPSYNC1, GPIO_FN_MSIOF0L_MCK0, GPIO_FN_D28,
	GPIO_FN_LCDD21, GPIO_FN_TS_SDAT1, GPIO_FN_MSIOF0L_MCK1, GPIO_FN_D29,
	GPIO_FN_LCDD22, GPIO_FN_TS_SDEN1, GPIO_FN_MSIOF0L_RSCK, GPIO_FN_D30,
	GPIO_FN_LCDD23, GPIO_FN_TS_SCK1, GPIO_FN_MSIOF0L_RSYNC, GPIO_FN_D31,
	GPIO_FN_LCDDCK, GPIO_FN_LCDWR_,
	GPIO_FN_LCDRD_, GPIO_FN_DACK2, GPIO_FN_PORT217_LCD2RS, \
	GPIO_FN_MSIOF0L_TSYNC, GPIO_FN_VIO2_FIELD3, GPIO_FN_PORT217_LCD2DISP,
	GPIO_FN_LCDHSYN, GPIO_FN_LCDCS_, GPIO_FN_LCDCS2_, GPIO_FN_DACK3, \
	GPIO_FN_PORT218_VIO_CKOR,
	GPIO_FN_LCDDISP, GPIO_FN_LCDRS, GPIO_FN_PORT219_LCD2WR_, \
	GPIO_FN_DREQ3, GPIO_FN_MSIOF0L_TSCK, GPIO_FN_VIO2_CLK3, \
	GPIO_FN_LCD2DCK_2,
	GPIO_FN_LCDVSYN, GPIO_FN_LCDVSYN2,
	GPIO_FN_LCDLCLK, GPIO_FN_DREQ1, GPIO_FN_PORT221_LCD2CS_, \
	GPIO_FN_PWEN, GPIO_FN_MSIOF0L_RXD, GPIO_FN_VIO2_HD3, \
	GPIO_FN_PORT221_LCD2HSYN,
	GPIO_FN_LCDDON, GPIO_FN_LCDDON2, GPIO_FN_DACK1, GPIO_FN_OVCN, \
	GPIO_FN_MSIOF0L_TXD, GPIO_FN_VIO2_VD3, GPIO_FN_PORT222_LCD2VSYN,

	GPIO_FN_SCIFA1_TXD, GPIO_FN_OVCN2,
	GPIO_FN_EXTLP, GPIO_FN_SCIFA1_SCK, GPIO_FN_PORT226_VIO_CKO2,
	GPIO_FN_SCIFA1_RTS_, GPIO_FN_IDIN,
	GPIO_FN_SCIFA1_RXD,
	GPIO_FN_SCIFA1_CTS_, GPIO_FN_MFG1_IN1,
	GPIO_FN_MSIOF1_TXD, GPIO_FN_SCIFA2_TXD2,
	GPIO_FN_MSIOF1_TSYNC, GPIO_FN_SCIFA2_CTS2_,
	GPIO_FN_MSIOF1_TSCK, GPIO_FN_SCIFA2_SCK2,
	GPIO_FN_MSIOF1_RXD, GPIO_FN_SCIFA2_RXD2,
	GPIO_FN_MSIOF1_RSCK, GPIO_FN_SCIFA2_RTS2_, GPIO_FN_VIO2_CLK2, \
	GPIO_FN_LCD2D20,
	GPIO_FN_MSIOF1_RSYNC, GPIO_FN_MFG1_IN2, GPIO_FN_VIO2_VD2, \
	GPIO_FN_LCD2D21,
	GPIO_FN_MSIOF1_MCK0, GPIO_FN_PORT236_I2C_SDA2,
	GPIO_FN_MSIOF1_MCK1, GPIO_FN_PORT237_I2C_SCL2,
	GPIO_FN_MSIOF1_SS1, GPIO_FN_VIO2_FIELD2, GPIO_FN_LCD2D22,
	GPIO_FN_MSIOF1_SS2, GPIO_FN_VIO2_HD2, GPIO_FN_LCD2D23,
	GPIO_FN_SCIFA6_TXD,
	GPIO_FN_PORT241_IRDA_OUT, GPIO_FN_PORT241_IROUT, GPIO_FN_MFG4_OUT1, \
	GPIO_FN_TPU4TO0,
	GPIO_FN_PORT242_IRDA_IN, GPIO_FN_MFG4_IN2,
	GPIO_FN_PORT243_IRDA_FIRSEL, GPIO_FN_PORT243_VIO_CKO2,
	GPIO_FN_PORT244_SCIFA5_CTS_, GPIO_FN_MFG2_IN1, \
	GPIO_FN_PORT244_SCIFB_CTS_, GPIO_FN_MSIOF2R_RXD,
	GPIO_FN_PORT245_SCIFA5_RTS_, GPIO_FN_MFG2_IN2, \
	GPIO_FN_PORT245_SCIFB_RTS_, GPIO_FN_MSIOF2R_TXD,
	GPIO_FN_PORT246_SCIFA5_RXD, GPIO_FN_MFG1_OUT1, \
	GPIO_FN_PORT246_SCIFB_RXD, GPIO_FN_TPU1TO0,
	GPIO_FN_PORT247_SCIFA5_TXD, GPIO_FN_MFG3_OUT2, \
	GPIO_FN_PORT247_SCIFB_TXD, GPIO_FN_TPU3TO1,
	GPIO_FN_PORT248_SCIFA5_SCK, GPIO_FN_MFG2_OUT1, \
	GPIO_FN_PORT248_SCIFB_SCK, GPIO_FN_TPU2TO0, \
	GPIO_FN_PORT248_I2C_SCL3, GPIO_FN_MSIOF2R_TSCK,
	GPIO_FN_PORT249_IROUT, GPIO_FN_MFG4_IN1, \
	GPIO_FN_PORT249_I2C_SDA3, GPIO_FN_MSIOF2R_TSYNC,
	GPIO_FN_SDHICLK0,
	GPIO_FN_SDHICD0,
	GPIO_FN_SDHID0_0,
	GPIO_FN_SDHID0_1,
	GPIO_FN_SDHID0_2,
	GPIO_FN_SDHID0_3,
	GPIO_FN_SDHICMD0,
	GPIO_FN_SDHIWP0,
	GPIO_FN_SDHICLK1,
	GPIO_FN_SDHID1_0, GPIO_FN_TS_SPSYNC2,
	GPIO_FN_SDHID1_1, GPIO_FN_TS_SDAT2,
	GPIO_FN_SDHID1_2, GPIO_FN_TS_SDEN2,
	GPIO_FN_SDHID1_3, GPIO_FN_TS_SCK2,
	GPIO_FN_SDHICMD1,
	GPIO_FN_SDHICLK2,
	GPIO_FN_SDHID2_0, GPIO_FN_TS_SPSYNC4,
	GPIO_FN_SDHID2_1, GPIO_FN_TS_SDAT4,
	GPIO_FN_SDHID2_2, GPIO_FN_TS_SDEN4,
	GPIO_FN_SDHID2_3, GPIO_FN_TS_SCK4,
	GPIO_FN_SDHICMD2,
	GPIO_FN_MMCCLK0,
	GPIO_FN_MMCD0_0,
	GPIO_FN_MMCD0_1,
	GPIO_FN_MMCD0_2,
	GPIO_FN_MMCD0_3,
	GPIO_FN_MMCD0_4, GPIO_FN_TS_SPSYNC5,
	GPIO_FN_MMCD0_5, GPIO_FN_TS_SDAT5,
	GPIO_FN_MMCD0_6, GPIO_FN_TS_SDEN5,
	GPIO_FN_MMCD0_7, GPIO_FN_TS_SCK5,
	GPIO_FN_MMCCMD0,
	GPIO_FN_RESETOUTS_, GPIO_FN_EXTAL2OUT,
	GPIO_FN_MCP_WAIT__MCP_FRB,
	GPIO_FN_MCP_CKO, GPIO_FN_MMCCLK1,
	GPIO_FN_MCP_D15_MCP_NAF15,
	GPIO_FN_MCP_D14_MCP_NAF14,
	GPIO_FN_MCP_D13_MCP_NAF13,
	GPIO_FN_MCP_D12_MCP_NAF12,
	GPIO_FN_MCP_D11_MCP_NAF11,
	GPIO_FN_MCP_D10_MCP_NAF10,
	GPIO_FN_MCP_D9_MCP_NAF9,
	GPIO_FN_MCP_D8_MCP_NAF8, GPIO_FN_MMCCMD1,
	GPIO_FN_MCP_D7_MCP_NAF7, GPIO_FN_MMCD1_7,

	GPIO_FN_MCP_D6_MCP_NAF6, GPIO_FN_MMCD1_6,
	GPIO_FN_MCP_D5_MCP_NAF5, GPIO_FN_MMCD1_5,
	GPIO_FN_MCP_D4_MCP_NAF4, GPIO_FN_MMCD1_4,
	GPIO_FN_MCP_D3_MCP_NAF3, GPIO_FN_MMCD1_3,
	GPIO_FN_MCP_D2_MCP_NAF2, GPIO_FN_MMCD1_2,
	GPIO_FN_MCP_D1_MCP_NAF1, GPIO_FN_MMCD1_1,
	GPIO_FN_MCP_D0_MCP_NAF0, GPIO_FN_MMCD1_0,
	GPIO_FN_MCP_NBRSTOUT_,
	GPIO_FN_MCP_WE0__MCP_FWE, GPIO_FN_MCP_RDWR_MCP_FWE,

	/* MSEL2 special case */
	GPIO_FN_TSIF2_TS_XX1,
	GPIO_FN_TSIF2_TS_XX2,
	GPIO_FN_TSIF2_TS_XX3,
	GPIO_FN_TSIF2_TS_XX4,
	GPIO_FN_TSIF2_TS_XX5,
	GPIO_FN_TSIF1_TS_XX1,
	GPIO_FN_TSIF1_TS_XX2,
	GPIO_FN_TSIF1_TS_XX3,
	GPIO_FN_TSIF1_TS_XX4,
	GPIO_FN_TSIF1_TS_XX5,
	GPIO_FN_TSIF0_TS_XX1,
	GPIO_FN_TSIF0_TS_XX2,
	GPIO_FN_TSIF0_TS_XX3,
	GPIO_FN_TSIF0_TS_XX4,
	GPIO_FN_TSIF0_TS_XX5,
	GPIO_FN_MST1_TS_XX1,
	GPIO_FN_MST1_TS_XX2,
	GPIO_FN_MST1_TS_XX3,
	GPIO_FN_MST1_TS_XX4,
	GPIO_FN_MST1_TS_XX5,
	GPIO_FN_MST0_TS_XX1,
	GPIO_FN_MST0_TS_XX2,
	GPIO_FN_MST0_TS_XX3,
	GPIO_FN_MST0_TS_XX4,
	GPIO_FN_MST0_TS_XX5,

	/* MSEL3 special cases */
	GPIO_FN_SDHI0_VCCQ_MC0_ON,
	GPIO_FN_SDHI0_VCCQ_MC0_OFF,
	GPIO_FN_DEBUG_MON_VIO,
	GPIO_FN_DEBUG_MON_LCDD,
	GPIO_FN_LCDC_LCDC0,
	GPIO_FN_LCDC_LCDC1,

	/* MSEL4 special cases */
	GPIO_FN_IRQ9_MEM_INT,
	GPIO_FN_IRQ9_MCP_INT,
	GPIO_FN_A11,
	GPIO_FN_KEYOUT8,
	GPIO_FN_TPU4TO3,
	GPIO_FN_RESETA_N_PU_ON,
	GPIO_FN_RESETA_N_PU_OFF,
	GPIO_FN_EDBGREQ_PD,
	GPIO_FN_EDBGREQ_PU,

	/* Functions with pull-ups */
	GPIO_FN_KEYIN0_PU,
	GPIO_FN_KEYIN1_PU,
	GPIO_FN_KEYIN2_PU,
	GPIO_FN_KEYIN3_PU,
	GPIO_FN_KEYIN4_PU,
	GPIO_FN_KEYIN5_PU,
	GPIO_FN_KEYIN6_PU,
	GPIO_FN_KEYIN7_PU,
	GPIO_FN_SDHICD0_PU,
	GPIO_FN_SDHID0_0_PU,
	GPIO_FN_SDHID0_1_PU,
	GPIO_FN_SDHID0_2_PU,
	GPIO_FN_SDHID0_3_PU,
	GPIO_FN_SDHICMD0_PU,
	GPIO_FN_SDHIWP0_PU,
	GPIO_FN_SDHID1_0_PU,
	GPIO_FN_SDHID1_1_PU,
	GPIO_FN_SDHID1_2_PU,
	GPIO_FN_SDHID1_3_PU,
	GPIO_FN_SDHICMD1_PU,
	GPIO_FN_SDHID2_0_PU,
	GPIO_FN_SDHID2_1_PU,
	GPIO_FN_SDHID2_2_PU,
	GPIO_FN_SDHID2_3_PU,
	GPIO_FN_SDHICMD2_PU,
	GPIO_FN_MMCCMD0_PU,
	GPIO_FN_MMCCMD1_PU,
	GPIO_FN_MMCD0_0_PU,
	GPIO_FN_MMCD0_1_PU,
	GPIO_FN_MMCD0_2_PU,
	GPIO_FN_MMCD0_3_PU,
	GPIO_FN_MMCD0_4_PU,
	GPIO_FN_MMCD0_5_PU,
	GPIO_FN_MMCD0_6_PU,
	GPIO_FN_MMCD0_7_PU,
	GPIO_FN_FSIACK_PU,
	GPIO_FN_FSIAILR_PU,
	GPIO_FN_FSIAIBT_PU,
	GPIO_FN_FSIAISLD_PU,
};

/* DMA slave IDs */
enum {
	SHDMA_SLAVE_INVALID,
	SHDMA_SLAVE_SCIF0_TX,
	SHDMA_SLAVE_SCIF0_RX,
	SHDMA_SLAVE_SCIF1_TX,
	SHDMA_SLAVE_SCIF1_RX,
	SHDMA_SLAVE_SCIF2_TX,
	SHDMA_SLAVE_SCIF2_RX,
	SHDMA_SLAVE_SCIF3_TX,
	SHDMA_SLAVE_SCIF3_RX,
	SHDMA_SLAVE_SCIF4_TX,
	SHDMA_SLAVE_SCIF4_RX,
	SHDMA_SLAVE_SCIF5_TX,
	SHDMA_SLAVE_SCIF5_RX,
	SHDMA_SLAVE_SCIF6_TX,
	SHDMA_SLAVE_SCIF6_RX,
	SHDMA_SLAVE_SCIF7_TX,
	SHDMA_SLAVE_SCIF7_RX,
	SHDMA_SLAVE_SCIF8_TX,
	SHDMA_SLAVE_SCIF8_RX,
	SHDMA_SLAVE_SDHI0_TX,
	SHDMA_SLAVE_SDHI0_RX,
	SHDMA_SLAVE_SDHI1_TX,
	SHDMA_SLAVE_SDHI1_RX,
	SHDMA_SLAVE_SDHI2_TX,
	SHDMA_SLAVE_SDHI2_RX,
	SHDMA_SLAVE_MMCIF_TX,
	SHDMA_SLAVE_MMCIF_RX,
};

/* PINT interrupts are located at Linux IRQ 800 and up */
#define SH73A0_PINT0_IRQ(irq) ((irq) + 800)
#define SH73A0_PINT1_IRQ(irq) ((irq) + 832)

#endif /* __ASM_SH73A0_H__ */
