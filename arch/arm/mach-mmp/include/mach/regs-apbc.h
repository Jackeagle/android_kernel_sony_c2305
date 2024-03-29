/*
 * linux/arch/arm/mach-mmp/include/mach/regs-apbc.h
 *
 *   Application Peripheral Bus Clock Unit
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_MACH_REGS_APBC_H
#define __ASM_MACH_REGS_APBC_H

#include <mach/addr-map.h>

#define APBC_VIRT_BASE	(APB_VIRT_BASE + 0x015000)
#define APBC_REG(x)	(APBC_VIRT_BASE + (x))

/*
 * APB clock register offsets for PXA168
 */
#define APBC_PXA168_UART1	APBC_REG(0x000)
#define APBC_PXA168_UART2	APBC_REG(0x004)
#define APBC_PXA168_GPIO	APBC_REG(0x008)
#define APBC_PXA168_PWM1	APBC_REG(0x00c)
#define APBC_PXA168_PWM2	APBC_REG(0x010)
#define APBC_PXA168_PWM3	APBC_REG(0x014)
#define APBC_PXA168_PWM4	APBC_REG(0x018)
#define APBC_PXA168_RTC		APBC_REG(0x028)
#define APBC_PXA168_TWSI0	APBC_REG(0x02c)
#define APBC_PXA168_KPC		APBC_REG(0x030)
#define APBC_PXA168_TIMERS	APBC_REG(0x034)
#define APBC_PXA168_AIB		APBC_REG(0x03c)
#define APBC_PXA168_SW_JTAG	APBC_REG(0x040)
#define APBC_PXA168_ONEWIRE	APBC_REG(0x048)
#define APBC_PXA168_ASFAR	APBC_REG(0x050)
#define APBC_PXA168_ASSAR	APBC_REG(0x054)
#define APBC_PXA168_TWSI1	APBC_REG(0x06c)
#define APBC_PXA168_UART3	APBC_REG(0x070)
#define APBC_PXA168_AC97	APBC_REG(0x084)
#define APBC_PXA168_SSP1	APBC_REG(0x81c)
#define APBC_PXA168_SSP2	APBC_REG(0x820)
#define APBC_PXA168_SSP3	APBC_REG(0x84c)
#define APBC_PXA168_SSP4	APBC_REG(0x858)
#define APBC_PXA168_SSP5	APBC_REG(0x85c)

/*
 * APB Clock register offsets for PXA910
 */
#define APBC_PXA910_UART0	APBC_REG(0x000)
#define APBC_PXA910_UART1	APBC_REG(0x004)
#define APBC_PXA910_GPIO	APBC_REG(0x008)
#define APBC_PXA910_PWM1	APBC_REG(0x00c)
#define APBC_PXA910_PWM2	APBC_REG(0x010)
#define APBC_PXA910_PWM3	APBC_REG(0x014)
#define APBC_PXA910_PWM4	APBC_REG(0x018)
#define APBC_PXA910_SSP1	APBC_REG(0x01c)
#define APBC_PXA910_SSP2	APBC_REG(0x020)
#define APBC_PXA910_IPC		APBC_REG(0x024)
#define APBC_PXA910_RTC		APBC_REG(0x028)
#define APBC_PXA910_TWSI0	APBC_REG(0x02c)
#define APBC_PXA910_KPC		APBC_REG(0x030)
#define APBC_PXA910_TIMERS	APBC_REG(0x034)
#define APBC_PXA910_TBROT	APBC_REG(0x038)
#define APBC_PXA910_AIB		APBC_REG(0x03c)
#define APBC_PXA910_SW_JTAG	APBC_REG(0x040)
#define APBC_PXA910_TIMERS1	APBC_REG(0x044)
#define APBC_PXA910_ONEWIRE	APBC_REG(0x048)
#define APBC_PXA910_SSP3	APBC_REG(0x04c)
#define APBC_PXA910_ASFAR	APBC_REG(0x050)
#define APBC_PXA910_ASSAR	APBC_REG(0x054)

/*
 * APB Clock register offsets for MMP2
 */
#define APBC_MMP2_RTC		APBC_REG(0x000)
#define APBC_MMP2_TWSI1		APBC_REG(0x004)
#define APBC_MMP2_TWSI2		APBC_REG(0x008)
#define APBC_MMP2_TWSI3		APBC_REG(0x00c)
#define APBC_MMP2_TWSI4		APBC_REG(0x010)
#define APBC_MMP2_ONEWIRE	APBC_REG(0x014)
#define APBC_MMP2_KPC		APBC_REG(0x018)
#define APBC_MMP2_TB_ROTARY	APBC_REG(0x01c)
#define APBC_MMP2_SW_JTAG	APBC_REG(0x020)
#define APBC_MMP2_TIMERS	APBC_REG(0x024)
#define APBC_MMP2_UART1		APBC_REG(0x02c)
#define APBC_MMP2_UART2		APBC_REG(0x030)
#define APBC_MMP2_UART3		APBC_REG(0x034)
#define APBC_MMP2_GPIO		APBC_REG(0x038)
#define APBC_MMP2_PWM0		APBC_REG(0x03c)
#define APBC_MMP2_PWM1		APBC_REG(0x040)
#define APBC_MMP2_PWM2		APBC_REG(0x044)
#define APBC_MMP2_PWM3		APBC_REG(0x048)
#define APBC_MMP2_SSP0		APBC_REG(0x04c)
#define APBC_MMP2_SSP1		APBC_REG(0x050)
#define APBC_MMP2_SSP2		APBC_REG(0x054)
#define APBC_MMP2_SSP3		APBC_REG(0x058)
#define APBC_MMP2_SSP4		APBC_REG(0x05c)
#define APBC_MMP2_SSP5		APBC_REG(0x060)
#define APBC_MMP2_AIB		APBC_REG(0x064)
#define APBC_MMP2_ASFAR		APBC_REG(0x068)
#define APBC_MMP2_ASSAR		APBC_REG(0x06c)
#define APBC_MMP2_USIM		APBC_REG(0x070)
#define APBC_MMP2_MPMU		APBC_REG(0x074)
#define APBC_MMP2_IPC		APBC_REG(0x078)
#define APBC_MMP2_TWSI5		APBC_REG(0x07c)
#define APBC_MMP2_TWSI6		APBC_REG(0x080)
#define APBC_MMP2_TWSI_INTSTS	APBC_REG(0x084)
#define APBC_MMP2_UART4		APBC_REG(0x088)
#define APBC_MMP2_RIPC		APBC_REG(0x08c)
#define APBC_MMP2_THSENS1	APBC_REG(0x090)	/* Thermal Sensor */
#define APBC_MMP2_THSENS_INTSTS	APBC_REG(0x0a4)

/* Common APB clock register bit definitions */
#define APBC_APBCLK	(1 << 0)  /* APB Bus Clock Enable */
#define APBC_FNCLK	(1 << 1)  /* Functional Clock Enable */
#define APBC_RST	(1 << 2)  /* Reset Generation */

/* Functional Clock Selection Mask */
#define APBC_FNCLKSEL(x)	(((x) & 0xf) << 4)

#endif /* __ASM_MACH_REGS_APBC_H */
