#ifndef __MACH_MX25_H__
#define __MACH_MX25_H__

#define MX25_AIPS1_BASE_ADDR		0x43f00000
#define MX25_AIPS1_SIZE			SZ_1M
#define MX25_AIPS2_BASE_ADDR		0x53f00000
#define MX25_AIPS2_SIZE			SZ_1M
#define MX25_AVIC_BASE_ADDR		0x68000000
#define MX25_AVIC_SIZE			SZ_1M

#define MX25_I2C1_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0x80000)
#define MX25_I2C3_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0x84000)
#define MX25_CAN1_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0x88000)
#define MX25_CAN2_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0x8c000)
#define MX25_I2C2_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0x98000)
#define MX25_CSPI1_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0xa4000)
#define MX25_IOMUXC_BASE_ADDR		(MX25_AIPS1_BASE_ADDR + 0xac000)

#define MX25_CRM_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0x80000)
#define MX25_GPT1_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0x90000)
#define MX25_GPIO4_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0x9c000)
#define MX25_PWM2_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xa0000)
#define MX25_GPIO3_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xa4000)
#define MX25_PWM3_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xa8000)
#define MX25_PWM4_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xc8000)
#define MX25_GPIO1_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xcc000)
#define MX25_GPIO2_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xd0000)
#define MX25_WDOG_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xdc000)
#define MX25_PWM1_BASE_ADDR		(MX25_AIPS2_BASE_ADDR + 0xe0000)

#define MX25_UART1_BASE_ADDR		0x43f90000
#define MX25_UART2_BASE_ADDR		0x43f94000
#define MX25_AUDMUX_BASE_ADDR		0x43fb0000
#define MX25_UART3_BASE_ADDR		0x5000c000
#define MX25_UART4_BASE_ADDR		0x50008000
#define MX25_UART5_BASE_ADDR		0x5002c000

#define MX25_CSPI3_BASE_ADDR		0x50004000
#define MX25_CSPI2_BASE_ADDR		0x50010000
#define MX25_FEC_BASE_ADDR		0x50038000
#define MX25_SSI2_BASE_ADDR		0x50014000
#define MX25_SSI1_BASE_ADDR		0x50034000
#define MX25_NFC_BASE_ADDR		0xbb000000
#define MX25_IIM_BASE_ADDR		0x53ff0000
#define MX25_DRYICE_BASE_ADDR		0x53ffc000
#define MX25_ESDHC1_BASE_ADDR		0x53fb4000
#define MX25_ESDHC2_BASE_ADDR		0x53fb8000
#define MX25_LCDC_BASE_ADDR		0x53fbc000
#define MX25_KPP_BASE_ADDR		0x43fa8000
#define MX25_SDMA_BASE_ADDR		0x53fd4000
#define MX25_USB_BASE_ADDR		0x53ff4000
#define MX25_USB_OTG_BASE_ADDR			(MX25_USB_BASE_ADDR + 0x0000)
/*
 * The reference manual (IMX25RM, Rev. 1, 06/2009) specifies an offset of 0x200
 * for the host controller.  Early documentation drafts specified 0x400 and
 * Freescale internal sources confirm only the latter value to work.
 */
#define MX25_USB_HS_BASE_ADDR			(MX25_USB_BASE_ADDR + 0x0400)
#define MX25_CSI_BASE_ADDR		0x53ff8000

#define MX25_IO_P2V(x)			IMX_IO_P2V(x)
#define MX25_IO_ADDRESS(x)		IOMEM(MX25_IO_P2V(x))

#define MX25_INT_CSPI3		0
#define MX25_INT_I2C1		3
#define MX25_INT_I2C2		4
#define MX25_INT_UART4		5
#define MX25_INT_ESDHC2		8
#define MX25_INT_ESDHC1		9
#define MX25_INT_I2C3		10
#define MX25_INT_SSI2		11
#define MX25_INT_SSI1		12
#define MX25_INT_CSPI2		13
#define MX25_INT_CSPI1		14
#define MX25_INT_GPIO3		16
#define MX25_INT_CSI		17
#define MX25_INT_UART3		18
#define MX25_INT_GPIO4		23
#define MX25_INT_KPP		24
#define MX25_INT_DRYICE		25
#define MX25_INT_PWM1		26
#define MX25_INT_UART2		32
#define MX25_INT_NFC		33
#define MX25_INT_SDMA		34
#define MX25_INT_USB_HS		35
#define MX25_INT_PWM2		36
#define MX25_INT_USB_OTG	37
#define MX25_INT_LCDC		39
#define MX25_INT_UART5		40
#define MX25_INT_PWM3		41
#define MX25_INT_PWM4		42
#define MX25_INT_CAN1		43
#define MX25_INT_CAN2		44
#define MX25_INT_UART1		45
#define MX25_INT_GPIO2		51
#define MX25_INT_GPIO1		52
#define MX25_INT_FEC		57

#define MX25_DMA_REQ_SSI2_RX1	22
#define MX25_DMA_REQ_SSI2_TX1	23
#define MX25_DMA_REQ_SSI2_RX0	24
#define MX25_DMA_REQ_SSI2_TX0	25
#define MX25_DMA_REQ_SSI1_RX1	26
#define MX25_DMA_REQ_SSI1_TX1	27
#define MX25_DMA_REQ_SSI1_RX0	28
#define MX25_DMA_REQ_SSI1_TX0	29

#ifndef __ASSEMBLY__
extern int mx25_revision(void);
#endif

#endif /* ifndef __MACH_MX25_H__ */
