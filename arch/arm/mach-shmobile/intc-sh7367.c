/*
 * sh7367 processor support - INTC hardware block
 *
 * Copyright (C) 2010  Magnus Damm
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
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/sh_intc.h>
#include <mach/intc.h>
#include <mach/irqs.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>

enum {
	UNUSED_INTCA = 0,
	ENABLED,
	DISABLED,

	/* interrupt sources INTCA */
	DIRC,
	CRYPT1_ERR, CRYPT2_STD,
	IIC1_ALI1, IIC1_TACKI1, IIC1_WAITI1, IIC1_DTEI1,
	ARM11_IRQPMU, ARM11_COMMTX, ARM11_COMMRX,
	ETM11_ACQCMP, ETM11_FULL,
	MFI_MFIM, MFI_MFIS,
	BBIF1, BBIF2,
	USBDMAC_USHDMI,
	USBHS_USHI0, USBHS_USHI1,
	CMT1_CMT10, CMT1_CMT11, CMT1_CMT12, CMT1_CMT13, CMT2, CMT3,
	KEYSC_KEY,
	SCIFA0, SCIFA1, SCIFA2, SCIFA3,
	MSIOF2, MSIOF1,
	SCIFA4, SCIFA5, SCIFB,
	FLCTL_FLSTEI, FLCTL_FLTENDI, FLCTL_FLTREQ0I, FLCTL_FLTREQ1I,
	SDHI0,
	SDHI1,
	MSU_MSU, MSU_MSU2,
	IREM,
	SIU,
	SPU,
	IRDA,
	TPU0, TPU1, TPU2, TPU3, TPU4,
	LCRC,
	PINT1, PINT2,
	TTI20,
	MISTY,
	DDM,
	SDHI2,
	RWDT0, RWDT1,
	DMAC_1_DEI0, DMAC_1_DEI1, DMAC_1_DEI2, DMAC_1_DEI3,
	DMAC_2_DEI4, DMAC_2_DEI5, DMAC_2_DADERR,
	DMAC2_1_DEI0, DMAC2_1_DEI1, DMAC2_1_DEI2, DMAC2_1_DEI3,
	DMAC2_2_DEI4, DMAC2_2_DEI5, DMAC2_2_DADERR,
	DMAC3_1_DEI0, DMAC3_1_DEI1, DMAC3_1_DEI2, DMAC3_1_DEI3,
	DMAC3_2_DEI4, DMAC3_2_DEI5, DMAC3_2_DADERR,

	/* interrupt groups INTCA */
	DMAC_1, DMAC_2,	DMAC2_1, DMAC2_2, DMAC3_1, DMAC3_2,
	ETM11, ARM11, USBHS, FLCTL, IIC1
};

static struct intc_vect intca_vectors[] __initdata = {
	INTC_VECT(DIRC, 0x0560),
	INTC_VECT(CRYPT1_ERR, 0x05e0),
	INTC_VECT(CRYPT2_STD, 0x0700),
	INTC_VECT(IIC1_ALI1, 0x0780), INTC_VECT(IIC1_TACKI1, 0x07a0),
	INTC_VECT(IIC1_WAITI1, 0x07c0), INTC_VECT(IIC1_DTEI1, 0x07e0),
	INTC_VECT(ARM11_IRQPMU, 0x0800), INTC_VECT(ARM11_COMMTX, 0x0840),
	INTC_VECT(ARM11_COMMRX, 0x0860),
	INTC_VECT(ETM11_ACQCMP, 0x0880), INTC_VECT(ETM11_FULL, 0x08a0),
	INTC_VECT(MFI_MFIM, 0x0900), INTC_VECT(MFI_MFIS, 0x0920),
	INTC_VECT(BBIF1, 0x0940), INTC_VECT(BBIF2, 0x0960),
	INTC_VECT(USBDMAC_USHDMI, 0x0a00),
	INTC_VECT(USBHS_USHI0, 0x0a20), INTC_VECT(USBHS_USHI1, 0x0a40),
	INTC_VECT(CMT1_CMT10, 0x0b00), INTC_VECT(CMT1_CMT11, 0x0b20),
	INTC_VECT(CMT1_CMT12, 0x0b40), INTC_VECT(CMT1_CMT13, 0x0b60),
	INTC_VECT(CMT2, 0x0b80), INTC_VECT(CMT3, 0x0ba0),
	INTC_VECT(KEYSC_KEY, 0x0be0),
	INTC_VECT(SCIFA0, 0x0c00), INTC_VECT(SCIFA1, 0x0c20),
	INTC_VECT(SCIFA2, 0x0c40), INTC_VECT(SCIFA3, 0x0c60),
	INTC_VECT(MSIOF2, 0x0c80), INTC_VECT(MSIOF1, 0x0d00),
	INTC_VECT(SCIFA4, 0x0d20), INTC_VECT(SCIFA5, 0x0d40),
	INTC_VECT(SCIFB, 0x0d60),
	INTC_VECT(FLCTL_FLSTEI, 0x0d80), INTC_VECT(FLCTL_FLTENDI, 0x0da0),
	INTC_VECT(FLCTL_FLTREQ0I, 0x0dc0), INTC_VECT(FLCTL_FLTREQ1I, 0x0de0),
	INTC_VECT(SDHI0, 0x0e00), INTC_VECT(SDHI0, 0x0e20),
	INTC_VECT(SDHI0, 0x0e40), INTC_VECT(SDHI0, 0x0e60),
	INTC_VECT(SDHI1, 0x0e80), INTC_VECT(SDHI1, 0x0ea0),
	INTC_VECT(SDHI1, 0x0ec0), INTC_VECT(SDHI1, 0x0ee0),
	INTC_VECT(MSU_MSU, 0x0f20), INTC_VECT(MSU_MSU2, 0x0f40),
	INTC_VECT(IREM, 0x0f60),
	INTC_VECT(SIU, 0x0fa0),
	INTC_VECT(SPU, 0x0fc0),
	INTC_VECT(IRDA, 0x0480),
	INTC_VECT(TPU0, 0x04a0), INTC_VECT(TPU1, 0x04c0),
	INTC_VECT(TPU2, 0x04e0), INTC_VECT(TPU3, 0x0500),
	INTC_VECT(TPU4, 0x0520),
	INTC_VECT(LCRC, 0x0540),
	INTC_VECT(PINT1, 0x1000), INTC_VECT(PINT2, 0x1020),
	INTC_VECT(TTI20, 0x1100),
	INTC_VECT(MISTY, 0x1120),
	INTC_VECT(DDM, 0x1140),
	INTC_VECT(SDHI2, 0x1200), INTC_VECT(SDHI2, 0x1220),
	INTC_VECT(SDHI2, 0x1240), INTC_VECT(SDHI2, 0x1260),
	INTC_VECT(RWDT0, 0x1280), INTC_VECT(RWDT1, 0x12a0),
	INTC_VECT(DMAC_1_DEI0, 0x2000), INTC_VECT(DMAC_1_DEI1, 0x2020),
	INTC_VECT(DMAC_1_DEI2, 0x2040), INTC_VECT(DMAC_1_DEI3, 0x2060),
	INTC_VECT(DMAC_2_DEI4, 0x2080), INTC_VECT(DMAC_2_DEI5, 0x20a0),
	INTC_VECT(DMAC_2_DADERR, 0x20c0),
	INTC_VECT(DMAC2_1_DEI0, 0x2100), INTC_VECT(DMAC2_1_DEI1, 0x2120),
	INTC_VECT(DMAC2_1_DEI2, 0x2140), INTC_VECT(DMAC2_1_DEI3, 0x2160),
	INTC_VECT(DMAC2_2_DEI4, 0x2180), INTC_VECT(DMAC2_2_DEI5, 0x21a0),
	INTC_VECT(DMAC2_2_DADERR, 0x21c0),
	INTC_VECT(DMAC3_1_DEI0, 0x2200), INTC_VECT(DMAC3_1_DEI1, 0x2220),
	INTC_VECT(DMAC3_1_DEI2, 0x2240), INTC_VECT(DMAC3_1_DEI3, 0x2260),
	INTC_VECT(DMAC3_2_DEI4, 0x2280), INTC_VECT(DMAC3_2_DEI5, 0x22a0),
	INTC_VECT(DMAC3_2_DADERR, 0x22c0),
};

static struct intc_group intca_groups[] __initdata = {
	INTC_GROUP(DMAC_1, DMAC_1_DEI0,
		   DMAC_1_DEI1, DMAC_1_DEI2, DMAC_1_DEI3),
	INTC_GROUP(DMAC_2, DMAC_2_DEI4,
		   DMAC_2_DEI5, DMAC_2_DADERR),
	INTC_GROUP(DMAC2_1, DMAC2_1_DEI0,
		   DMAC2_1_DEI1, DMAC2_1_DEI2, DMAC2_1_DEI3),
	INTC_GROUP(DMAC2_2, DMAC2_2_DEI4,
		   DMAC2_2_DEI5, DMAC2_2_DADERR),
	INTC_GROUP(DMAC3_1, DMAC3_1_DEI0,
		   DMAC3_1_DEI1, DMAC3_1_DEI2, DMAC3_1_DEI3),
	INTC_GROUP(DMAC3_2, DMAC3_2_DEI4,
		   DMAC3_2_DEI5, DMAC3_2_DADERR),
	INTC_GROUP(ETM11, ETM11_ACQCMP, ETM11_FULL),
	INTC_GROUP(ARM11, ARM11_IRQPMU, ARM11_COMMTX, ARM11_COMMTX),
	INTC_GROUP(USBHS, USBHS_USHI0, USBHS_USHI1),
	INTC_GROUP(FLCTL, FLCTL_FLSTEI, FLCTL_FLTENDI,
		   FLCTL_FLTREQ0I, FLCTL_FLTREQ1I),
	INTC_GROUP(IIC1, IIC1_ALI1, IIC1_TACKI1, IIC1_WAITI1, IIC1_DTEI1),
};

static struct intc_mask_reg intca_mask_registers[] __initdata = {
	{ 0xe6940080, 0xe69400c0, 8, /* IMR0A / IMCR0A */
	  { DMAC2_1_DEI3, DMAC2_1_DEI2, DMAC2_1_DEI1, DMAC2_1_DEI0,
	    ARM11_IRQPMU, 0, ARM11_COMMTX, ARM11_COMMRX } },
	{ 0xe6940084, 0xe69400c4, 8, /* IMR1A / IMCR1A */
	  { CRYPT1_ERR, CRYPT2_STD, DIRC, 0,
	    DMAC_1_DEI3, DMAC_1_DEI2, DMAC_1_DEI1, DMAC_1_DEI0 } },
	{ 0xe6940088, 0xe69400c8, 8, /* IMR2A / IMCR2A */
	  { PINT1, PINT2, 0, 0,
	    BBIF1, BBIF2, MFI_MFIS, MFI_MFIM } },
	{ 0xe694008c, 0xe69400cc, 8, /* IMR3A / IMCR3A */
	  { DMAC3_1_DEI3, DMAC3_1_DEI2, DMAC3_1_DEI1, DMAC3_1_DEI0,
	    DMAC3_2_DADERR, DMAC3_2_DEI5, DMAC3_2_DEI4, IRDA } },
	{ 0xe6940090, 0xe69400d0, 8, /* IMR4A / IMCR4A */
	  { DDM, 0, 0, 0,
	    0, 0, ETM11_FULL, ETM11_ACQCMP } },
	{ 0xe6940094, 0xe69400d4, 8, /* IMR5A / IMCR5A */
	  { KEYSC_KEY, DMAC_2_DADERR, DMAC_2_DEI5, DMAC_2_DEI4,
	    SCIFA3, SCIFA2, SCIFA1, SCIFA0 } },
	{ 0xe6940098, 0xe69400d8, 8, /* IMR6A / IMCR6A */
	  { SCIFB, SCIFA5, SCIFA4, MSIOF1,
	    0, 0, MSIOF2, 0 } },
	{ 0xe694009c, 0xe69400dc, 8, /* IMR7A / IMCR7A */
	  { DISABLED, ENABLED, ENABLED, ENABLED,
	    FLCTL_FLTREQ1I, FLCTL_FLTREQ0I, FLCTL_FLTENDI, FLCTL_FLSTEI } },
	{ 0xe69400a0, 0xe69400e0, 8, /* IMR8A / IMCR8A */
	  { DISABLED, ENABLED, ENABLED, ENABLED,
	    TTI20, USBDMAC_USHDMI, SPU, SIU } },
	{ 0xe69400a4, 0xe69400e4, 8, /* IMR9A / IMCR9A */
	  { CMT1_CMT13, CMT1_CMT12, CMT1_CMT11, CMT1_CMT10,
	    CMT2, USBHS_USHI1, USBHS_USHI0, 0 } },
	{ 0xe69400a8, 0xe69400e8, 8, /* IMR10A / IMCR10A */
	  { 0, DMAC2_2_DADERR, DMAC2_2_DEI5, DMAC2_2_DEI4,
	    0, 0, 0, 0 } },
	{ 0xe69400ac, 0xe69400ec, 8, /* IMR11A / IMCR11A */
	  { IIC1_DTEI1, IIC1_WAITI1, IIC1_TACKI1, IIC1_ALI1,
	    LCRC, MSU_MSU2, IREM, MSU_MSU } },
	{ 0xe69400b0, 0xe69400f0, 8, /* IMR12A / IMCR12A */
	  { 0, 0, TPU0, TPU1,
	    TPU2, TPU3, TPU4, 0 } },
	{ 0xe69400b4, 0xe69400f4, 8, /* IMR13A / IMCR13A */
	  { DISABLED, ENABLED, ENABLED, ENABLED,
	    MISTY, CMT3, RWDT1, RWDT0 } },
};

static struct intc_prio_reg intca_prio_registers[] __initdata = {
	{ 0xe6940000, 0, 16, 4, /* IPRAA */ { DMAC3_1, DMAC3_2, CMT2, LCRC } },
	{ 0xe6940004, 0, 16, 4, /* IPRBA */ { IRDA, ETM11, BBIF1, BBIF2 } },
	{ 0xe6940008, 0, 16, 4, /* IPRCA */ { CRYPT1_ERR, CRYPT2_STD,
					      CMT1_CMT11, ARM11 } },
	{ 0xe694000c, 0, 16, 4, /* IPRDA */ { PINT1, PINT2,
					      CMT1_CMT12, TPU4 } },
	{ 0xe6940010, 0, 16, 4, /* IPREA */ { DMAC_1, MFI_MFIS,
					      MFI_MFIM, USBHS } },
	{ 0xe6940014, 0, 16, 4, /* IPRFA */ { KEYSC_KEY, DMAC_2,
					      0, CMT1_CMT10 } },
	{ 0xe6940018, 0, 16, 4, /* IPRGA */ { SCIFA0, SCIFA1,
					      SCIFA2, SCIFA3 } },
	{ 0xe694001c, 0, 16, 4, /* IPRGH */ { MSIOF2, USBDMAC_USHDMI,
					      FLCTL, SDHI0 } },
	{ 0xe6940020, 0, 16, 4, /* IPRIA */ { MSIOF1, SCIFA4, MSU_MSU, IIC1 } },
	{ 0xe6940024, 0, 16, 4, /* IPRJA */ { DMAC2_1, DMAC2_2, SIU, TTI20 } },
	{ 0xe6940028, 0, 16, 4, /* IPRKA */ { 0, CMT1_CMT13, IREM, SDHI1 } },
	{ 0xe694002c, 0, 16, 4, /* IPRLA */ { TPU0, TPU1, TPU2, TPU3 } },
	{ 0xe6940030, 0, 16, 4, /* IPRMA */ { MISTY, CMT3, RWDT1, RWDT0 } },
	{ 0xe6940034, 0, 16, 4, /* IPRNA */ { SCIFB, SCIFA5, SPU, DDM } },
	{ 0xe6940038, 0, 16, 4, /* IPROA */ { 0, 0, DIRC, SDHI2 } },
};

static struct intc_desc intca_desc __initdata = {
	.name = "sh7367-intca",
	.force_enable = ENABLED,
	.force_disable = DISABLED,
	.hw = INTC_HW_DESC(intca_vectors, intca_groups,
			   intca_mask_registers, intca_prio_registers,
			   NULL, NULL),
};

INTC_IRQ_PINS_16(intca_irq_pins, 0xe6900000,
		 INTC_VECT, "sh7367-intca-irq-pins");

enum {
	UNUSED_INTCS = 0,

	INTCS,

	/* interrupt sources INTCS */
	VIO2_VEU0, VIO2_VEU1, VIO2_VEU2, VIO2_VEU3,
	VIO3_VOU,
	RTDMAC_1_DEI0, RTDMAC_1_DEI1, RTDMAC_1_DEI2, RTDMAC_1_DEI3,
	VIO1_CEU, VIO1_BEU0, VIO1_BEU1, VIO1_BEU2,
	VPU,
	SGX530,
	_2DDMAC_2DDM0, _2DDMAC_2DDM1, _2DDMAC_2DDM2, _2DDMAC_2DDM3,
	IIC2_ALI2, IIC2_TACKI2, IIC2_WAITI2, IIC2_DTEI2,
	IPMMU_IPMMUB, IPMMU_IPMMUS,
	RTDMAC_2_DEI4, RTDMAC_2_DEI5, RTDMAC_2_DADERR,
	MSIOF,
	IIC0_ALI0, IIC0_TACKI0, IIC0_WAITI0, IIC0_DTEI0,
	TMU_TUNI0, TMU_TUNI1, TMU_TUNI2,
	CMT,
	TSIF,
	IPMMUI,
	MVI3,
	ICB,
	PEP,
	ASA,
	BEM,
	VE2HO,
	HQE,
	JPEG,
	LCDC,

	/* interrupt groups INTCS */
	_2DDMAC, RTDMAC_1, RTDMAC_2, VEU, BEU, IIC0, IPMMU, IIC2,
};

static struct intc_vect intcs_vectors[] = {
	INTCS_VECT(VIO2_VEU0, 0x700), INTCS_VECT(VIO2_VEU1, 0x720),
	INTCS_VECT(VIO2_VEU2, 0x740), INTCS_VECT(VIO2_VEU3, 0x760),
	INTCS_VECT(VIO3_VOU, 0x780),
	INTCS_VECT(RTDMAC_1_DEI0, 0x800), INTCS_VECT(RTDMAC_1_DEI1, 0x820),
	INTCS_VECT(RTDMAC_1_DEI2, 0x840), INTCS_VECT(RTDMAC_1_DEI3, 0x860),
	INTCS_VECT(VIO1_CEU, 0x880), INTCS_VECT(VIO1_BEU0, 0x8a0),
	INTCS_VECT(VIO1_BEU1, 0x8c0), INTCS_VECT(VIO1_BEU2, 0x8e0),
	INTCS_VECT(VPU, 0x980),
	INTCS_VECT(SGX530, 0x9e0),
	INTCS_VECT(_2DDMAC_2DDM0, 0xa00), INTCS_VECT(_2DDMAC_2DDM1, 0xa20),
	INTCS_VECT(_2DDMAC_2DDM2, 0xa40), INTCS_VECT(_2DDMAC_2DDM3, 0xa60),
	INTCS_VECT(IIC2_ALI2, 0xa80), INTCS_VECT(IIC2_TACKI2, 0xaa0),
	INTCS_VECT(IIC2_WAITI2, 0xac0), INTCS_VECT(IIC2_DTEI2, 0xae0),
	INTCS_VECT(IPMMU_IPMMUB, 0xb20), INTCS_VECT(IPMMU_IPMMUS, 0xb60),
	INTCS_VECT(RTDMAC_2_DEI4, 0xb80), INTCS_VECT(RTDMAC_2_DEI5, 0xba0),
	INTCS_VECT(RTDMAC_2_DADERR, 0xbc0),
	INTCS_VECT(MSIOF, 0xd20),
	INTCS_VECT(IIC0_ALI0, 0xe00), INTCS_VECT(IIC0_TACKI0, 0xe20),
	INTCS_VECT(IIC0_WAITI0, 0xe40), INTCS_VECT(IIC0_DTEI0, 0xe60),
	INTCS_VECT(TMU_TUNI0, 0xe80), INTCS_VECT(TMU_TUNI1, 0xea0),
	INTCS_VECT(TMU_TUNI2, 0xec0),
	INTCS_VECT(CMT, 0xf00),
	INTCS_VECT(TSIF, 0xf20),
	INTCS_VECT(IPMMUI, 0xf60),
	INTCS_VECT(MVI3, 0x420),
	INTCS_VECT(ICB, 0x480),
	INTCS_VECT(PEP, 0x4a0),
	INTCS_VECT(ASA, 0x4c0),
	INTCS_VECT(BEM, 0x4e0),
	INTCS_VECT(VE2HO, 0x520),
	INTCS_VECT(HQE, 0x540),
	INTCS_VECT(JPEG, 0x560),
	INTCS_VECT(LCDC, 0x580),

	INTC_VECT(INTCS, 0xf80),
};

static struct intc_group intcs_groups[] __initdata = {
	INTC_GROUP(_2DDMAC, _2DDMAC_2DDM0, _2DDMAC_2DDM1,
		   _2DDMAC_2DDM2, _2DDMAC_2DDM3),
	INTC_GROUP(RTDMAC_1, RTDMAC_1_DEI0, RTDMAC_1_DEI1,
		   RTDMAC_1_DEI2, RTDMAC_1_DEI3),
	INTC_GROUP(RTDMAC_2, RTDMAC_2_DEI4, RTDMAC_2_DEI5, RTDMAC_2_DADERR),
	INTC_GROUP(VEU, VIO2_VEU0, VIO2_VEU1, VIO2_VEU2, VIO2_VEU3),
	INTC_GROUP(BEU, VIO1_BEU0, VIO1_BEU1, VIO1_BEU2),
	INTC_GROUP(IIC0, IIC0_ALI0, IIC0_TACKI0, IIC0_WAITI0, IIC0_DTEI0),
	INTC_GROUP(IPMMU, IPMMU_IPMMUS, IPMMU_IPMMUB),
	INTC_GROUP(IIC2, IIC2_ALI2, IIC2_TACKI2, IIC2_WAITI2, IIC2_DTEI2),
};

static struct intc_mask_reg intcs_mask_registers[] = {
	{ 0xffd20184, 0xffd201c4, 8, /* IMR1SA / IMCR1SA */
	  { VIO1_BEU2, VIO1_BEU1, VIO1_BEU0, VIO1_CEU,
	    VIO2_VEU3, VIO2_VEU2, VIO2_VEU1, VIO2_VEU0 } },
	{ 0xffd20188, 0xffd201c8, 8, /* IMR2SA / IMCR2SA */
	  { VIO3_VOU, 0, VE2HO, VPU,
	    0, 0, 0, 0 } },
	{ 0xffd2018c, 0xffd201cc, 8, /* IMR3SA / IMCR3SA */
	  { _2DDMAC_2DDM3, _2DDMAC_2DDM2, _2DDMAC_2DDM1, _2DDMAC_2DDM0,
	    BEM, ASA, PEP, ICB } },
	{ 0xffd20190, 0xffd201d0, 8, /* IMR4SA / IMCR4SA */
	  { 0, 0, MVI3, 0,
	    JPEG, HQE, 0, LCDC } },
	{ 0xffd20194, 0xffd201d4, 8, /* IMR5SA / IMCR5SA */
	  { 0, RTDMAC_2_DADERR, RTDMAC_2_DEI5, RTDMAC_2_DEI4,
	    RTDMAC_1_DEI3, RTDMAC_1_DEI2, RTDMAC_1_DEI1, RTDMAC_1_DEI0 } },
	{ 0xffd20198, 0xffd201d8, 8, /* IMR6SA / IMCR6SA */
	  { 0, 0, MSIOF, 0,
	    SGX530, 0, 0, 0 } },
	{ 0xffd2019c, 0xffd201dc, 8, /* IMR7SA / IMCR7SA */
	  { 0, TMU_TUNI2, TMU_TUNI1, TMU_TUNI0,
	    0, 0, 0, 0 } },
	{ 0xffd201a4, 0xffd201e4, 8, /* IMR9SA / IMCR9SA */
	  { 0, 0, 0, CMT,
	    IIC2_DTEI2, IIC2_WAITI2, IIC2_TACKI2, IIC2_ALI2 } },
	{ 0xffd201a8, 0xffd201e8, 8, /* IMR10SA / IMCR10SA */
	  { IPMMU_IPMMUS, 0, IPMMU_IPMMUB, 0,
	    0, 0, 0, 0 } },
	{ 0xffd201ac, 0xffd201ec, 8, /* IMR11SA / IMCR11SA */
	  { IIC0_DTEI0, IIC0_WAITI0, IIC0_TACKI0, IIC0_ALI0,
	    0, 0, IPMMUI, TSIF } },
	{ 0xffd20104, 0, 16, /* INTAMASK */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, INTCS } },
};

/* Priority is needed for INTCA to receive the INTCS interrupt */
static struct intc_prio_reg intcs_prio_registers[] = {
	{ 0xffd20000, 0, 16, 4, /* IPRAS */ { 0, MVI3, _2DDMAC, ICB } },
	{ 0xffd20004, 0, 16, 4, /* IPRBS */ { JPEG, LCDC, 0, 0 } },
	{ 0xffd20008, 0, 16, 4, /* IPRCS */ { BBIF2, 0, 0, 0 } },
	{ 0xffd20010, 0, 16, 4, /* IPRES */ { RTDMAC_1, VIO1_CEU, 0, VPU } },
	{ 0xffd20014, 0, 16, 4, /* IPRFS */ { 0, RTDMAC_2, 0, CMT } },
	{ 0xffd20018, 0, 16, 4, /* IPRGS */ { TMU_TUNI0, TMU_TUNI1,
					      TMU_TUNI2, 0 } },
	{ 0xffd2001c, 0, 16, 4, /* IPRHS */ { 0, VIO3_VOU, VEU, BEU } },
	{ 0xffd20020, 0, 16, 4, /* IPRIS */ { 0, MSIOF, TSIF, IIC0 } },
	{ 0xffd20024, 0, 16, 4, /* IPRJS */ { 0, SGX530, 0, 0 } },
	{ 0xffd20028, 0, 16, 4, /* IPRKS */ { BEM, ASA, IPMMUI, PEP } },
	{ 0xffd2002c, 0, 16, 4, /* IPRLS */ { IPMMU, 0, VE2HO, HQE } },
	{ 0xffd20030, 0, 16, 4, /* IPRMS */ { IIC2, 0, 0, 0 } },
};

static struct resource intcs_resources[] __initdata = {
	[0] = {
		.start	= 0xffd20000,
		.end	= 0xffd2ffff,
		.flags	= IORESOURCE_MEM,
	}
};

static struct intc_desc intcs_desc __initdata = {
	.name = "sh7367-intcs",
	.resource = intcs_resources,
	.num_resources = ARRAY_SIZE(intcs_resources),
	.hw = INTC_HW_DESC(intcs_vectors, intcs_groups, intcs_mask_registers,
			   intcs_prio_registers, NULL, NULL),
};

static void intcs_demux(unsigned int irq, struct irq_desc *desc)
{
	void __iomem *reg = (void *)irq_get_handler_data(irq);
	unsigned int evtcodeas = ioread32(reg);

	generic_handle_irq(intcs_evt2irq(evtcodeas));
}

void __init sh7367_init_irq(void)
{
	void __iomem *intevtsa = ioremap_nocache(0xffd20100, PAGE_SIZE);

	register_intc_controller(&intca_desc);
	register_intc_controller(&intca_irq_pins_desc);
	register_intc_controller(&intcs_desc);

	/* demux using INTEVTSA */
	irq_set_handler_data(evt2irq(0xf80), (void *)intevtsa);
	irq_set_chained_handler(evt2irq(0xf80), intcs_demux);
}
