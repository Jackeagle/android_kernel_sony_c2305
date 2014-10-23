/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2004-2008 Cavium Networks
 */
#ifndef __OCTEON_IRQ_H__
#define __OCTEON_IRQ_H__

#define NR_IRQS OCTEON_IRQ_LAST
#define MIPS_CPU_IRQ_BASE OCTEON_IRQ_SW0

enum octeon_irq {
/* 1 - 8 represent the 8 MIPS standard interrupt sources */
	OCTEON_IRQ_SW0 = 1,
	OCTEON_IRQ_SW1,
/* CIU0, CUI2, CIU4 are 3, 4, 5 */
	OCTEON_IRQ_5 = 6,
	OCTEON_IRQ_PERF,
	OCTEON_IRQ_TIMER,
/* sources in CIU_INTX_EN0 */
	OCTEON_IRQ_WORKQ0,
	OCTEON_IRQ_GPIO0 = OCTEON_IRQ_WORKQ0 + 16,
	OCTEON_IRQ_WDOG0 = OCTEON_IRQ_GPIO0 + 16,
	OCTEON_IRQ_WDOG15 = OCTEON_IRQ_WDOG0 + 15,
	OCTEON_IRQ_MBOX0 = OCTEON_IRQ_WDOG0 + 16,
	OCTEON_IRQ_MBOX1,
	OCTEON_IRQ_UART0,
	OCTEON_IRQ_UART1,
	OCTEON_IRQ_UART2,
	OCTEON_IRQ_PCI_INT0,
	OCTEON_IRQ_PCI_INT1,
	OCTEON_IRQ_PCI_INT2,
	OCTEON_IRQ_PCI_INT3,
	OCTEON_IRQ_PCI_MSI0,
	OCTEON_IRQ_PCI_MSI1,
	OCTEON_IRQ_PCI_MSI2,
	OCTEON_IRQ_PCI_MSI3,

	OCTEON_IRQ_TWSI,
	OCTEON_IRQ_TWSI2,
	OCTEON_IRQ_RML,
	OCTEON_IRQ_TRACE0,
	OCTEON_IRQ_GMX_DRP0 = OCTEON_IRQ_TRACE0 + 4,
	OCTEON_IRQ_IPD_DRP = OCTEON_IRQ_GMX_DRP0 + 5,
	OCTEON_IRQ_KEY_ZERO,
	OCTEON_IRQ_TIMER0,
	OCTEON_IRQ_TIMER1,
	OCTEON_IRQ_TIMER2,
	OCTEON_IRQ_TIMER3,
	OCTEON_IRQ_USB0,
	OCTEON_IRQ_USB1,
	OCTEON_IRQ_PCM,
	OCTEON_IRQ_MPI,
	OCTEON_IRQ_POWIQ,
	OCTEON_IRQ_IPDPPTHR,
	OCTEON_IRQ_MII0,
	OCTEON_IRQ_MII1,
	OCTEON_IRQ_BOOTDMA,

	OCTEON_IRQ_NAND,
	OCTEON_IRQ_MIO,		/* Summary of MIO_BOOT_ERR */
	OCTEON_IRQ_IOB,		/* Summary of IOB_INT_SUM */
	OCTEON_IRQ_FPA,		/* Summary of FPA_INT_SUM */
	OCTEON_IRQ_POW,		/* Summary of POW_ECC_ERR */
	OCTEON_IRQ_L2C,		/* Summary of L2C_INT_STAT */
	OCTEON_IRQ_IPD,		/* Summary of IPD_INT_SUM */
	OCTEON_IRQ_PIP,		/* Summary of PIP_INT_REG */
	OCTEON_IRQ_PKO,		/* Summary of PKO_REG_ERROR */
	OCTEON_IRQ_ZIP,		/* Summary of ZIP_ERROR */
	OCTEON_IRQ_TIM,		/* Summary of TIM_REG_ERROR */
	OCTEON_IRQ_RAD,		/* Summary of RAD_REG_ERROR */
	OCTEON_IRQ_KEY,		/* Summary of KEY_INT_SUM */
	OCTEON_IRQ_DFA,		/* Summary of DFA */
	OCTEON_IRQ_USBCTL,	/* Summary of USBN0_INT_SUM */
	OCTEON_IRQ_SLI,		/* Summary of SLI_INT_SUM */
	OCTEON_IRQ_DPI,		/* Summary of DPI_INT_SUM */
	OCTEON_IRQ_AGX0,	/* Summary of GMX0*+PCS0_INT*_REG */
	OCTEON_IRQ_AGL  = OCTEON_IRQ_AGX0 + 5,
	OCTEON_IRQ_PTP,
	OCTEON_IRQ_PEM0,
	OCTEON_IRQ_PEM1,
	OCTEON_IRQ_SRIO0,
	OCTEON_IRQ_SRIO1,
	OCTEON_IRQ_LMC0,
	OCTEON_IRQ_DFM = OCTEON_IRQ_LMC0 + 4,		/* Summary of DFM */
	OCTEON_IRQ_RST,
};

#ifdef CONFIG_PCI_MSI
/* 152 - 407 represent the MSI interrupts 0-255 */
#define OCTEON_IRQ_MSI_BIT0	(OCTEON_IRQ_RST + 1)

#define OCTEON_IRQ_MSI_LAST      (OCTEON_IRQ_MSI_BIT0 + 255)
#define OCTEON_IRQ_LAST          (OCTEON_IRQ_MSI_LAST + 1)
#else
#define OCTEON_IRQ_LAST         (OCTEON_IRQ_RST + 1)
#endif

#endif
