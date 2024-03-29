/*
 * Broadcom device-specific manifest constants.
 *
 * Copyright (C) 1999-2012, Broadcom Corporation
 * 
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 * $Id: bcmdevs.h 329854 2012-04-27 01:42:28Z $
 */

#ifndef	_BCMDEVS_H
#define	_BCMDEVS_H


#define	VENDOR_EPIGRAM		0xfeda
#define	VENDOR_BROADCOM		0x14e4
#define	VENDOR_3COM		0x10b7
#define	VENDOR_NETGEAR		0x1385
#define	VENDOR_DIAMOND		0x1092
#define	VENDOR_INTEL		0x8086
#define	VENDOR_DELL		0x1028
#define	VENDOR_HP		0x103c
#define	VENDOR_HP_COMPAQ	0x0e11
#define	VENDOR_APPLE		0x106b
#define VENDOR_SI_IMAGE		0x1095		
#define VENDOR_BUFFALO		0x1154		
#define VENDOR_TI		0x104c		
#define VENDOR_RICOH		0x1180		
#define VENDOR_JMICRON		0x197b



#define	VENDOR_BROADCOM_PCMCIA	0x02d0


#define	VENDOR_BROADCOM_SDIO	0x00BF


#define BCM_DNGL_VID		0x0a5c
#define BCM_DNGL_BL_PID_4328	0xbd12
#define BCM_DNGL_BL_PID_4322	0xbd13
#define BCM_DNGL_BL_PID_4319    0xbd16
#define BCM_DNGL_BL_PID_43236   0xbd17
#define BCM_DNGL_BL_PID_4332	0xbd18
#define BCM_DNGL_BL_PID_4330	0xbd19
#define BCM_DNGL_BL_PID_4334	0xbd1a
#define BCM_DNGL_BL_PID_43239   0xbd1b
#define BCM_DNGL_BL_PID_4324	0xbd1c
#define BCM_DNGL_BL_PID_4360	0xbd1d

#define BCM_DNGL_BDC_PID	0x0bdc
#define BCM_DNGL_JTAG_PID	0x4a44


#define BCM_HWUSB_PID_43239     43239


#define	BCM4210_DEVICE_ID	0x1072		
#define	BCM4230_DEVICE_ID	0x1086		
#define	BCM4401_ENET_ID		0x170c		
#define	BCM3352_DEVICE_ID	0x3352		
#define	BCM3360_DEVICE_ID	0x3360		
#define	BCM4211_DEVICE_ID	0x4211
#define	BCM4231_DEVICE_ID	0x4231
#define	BCM4303_D11B_ID		0x4303		
#define	BCM4311_D11G_ID		0x4311		
#define	BCM4311_D11DUAL_ID	0x4312		
#define	BCM4311_D11A_ID		0x4313		
#define	BCM4328_D11DUAL_ID	0x4314		
#define	BCM4328_D11G_ID		0x4315		
#define	BCM4328_D11A_ID		0x4316		
#define	BCM4318_D11G_ID		0x4318		
#define	BCM4318_D11DUAL_ID	0x4319		
#define	BCM4318_D11A_ID		0x431a		
#define	BCM4325_D11DUAL_ID	0x431b		
#define	BCM4325_D11G_ID		0x431c		
#define	BCM4325_D11A_ID		0x431d		
#define	BCM4306_D11G_ID		0x4320		
#define	BCM4306_D11A_ID		0x4321		
#define	BCM4306_UART_ID		0x4322		
#define	BCM4306_V90_ID		0x4323		
#define	BCM4306_D11DUAL_ID	0x4324		
#define	BCM4306_D11G_ID2	0x4325		
#define	BCM4321_D11N_ID		0x4328		
#define	BCM4321_D11N2G_ID	0x4329		
#define	BCM4321_D11N5G_ID	0x432a		
#define BCM4322_D11N_ID		0x432b		
#define BCM4322_D11N2G_ID	0x432c		
#define BCM4322_D11N5G_ID	0x432d		
#define BCM4329_D11N_ID		0x432e		
#define BCM4329_D11N2G_ID	0x432f		
#define BCM4329_D11N5G_ID	0x4330		
#define	BCM4315_D11DUAL_ID	0x4334		
#define	BCM4315_D11G_ID		0x4335		
#define	BCM4315_D11A_ID		0x4336		
#define BCM4319_D11N_ID		0x4337		
#define BCM4319_D11N2G_ID	0x4338		
#define BCM4319_D11N5G_ID	0x4339		
#define BCM43231_D11N2G_ID	0x4340		
#define BCM43221_D11N2G_ID	0x4341		
#define BCM43222_D11N_ID	0x4350		
#define BCM43222_D11N2G_ID	0x4351		
#define BCM43222_D11N5G_ID	0x4352		
#define BCM43224_D11N_ID	0x4353		
#define BCM43224_D11N_ID_VEN1	0x0576		
#define BCM43226_D11N_ID	0x4354		
#define BCM43236_D11N_ID	0x4346		
#define BCM43236_D11N2G_ID	0x4347		
#define BCM43236_D11N5G_ID	0x4348		
#define BCM43225_D11N2G_ID	0x4357		
#define BCM43421_D11N_ID	0xA99D		
#define BCM4313_D11N2G_ID	0x4727		
#define BCM4330_D11N_ID         0x4360          
#define BCM4330_D11N2G_ID       0x4361          
#define BCM4330_D11N5G_ID       0x4362          
#define BCM4336_D11N_ID		0x4343		
#define BCM6362_D11N_ID		0x435f		
#define BCM4331_D11N_ID		0x4331		
#define BCM4331_D11N2G_ID	0x4332		
#define BCM4331_D11N5G_ID	0x4333		
#define BCM43237_D11N_ID	0x4355		
#define BCM43237_D11N5G_ID	0x4356		
#define BCM43227_D11N2G_ID	0x4358		
#define BCM43228_D11N_ID	0x4359		
#define BCM43228_D11N5G_ID	0x435a		
#define BCM43362_D11N_ID	0x4363		
#define BCM43239_D11N_ID	0x4370		
#define BCM4324_D11N_ID		0x4374		
#define BCM43217_D11N2G_ID	0x43a9		
#define BCM43131_D11N2G_ID	0x43aa		
#define BCM4314_D11N2G_ID	0x4364		
#define BCM43142_D11N2G_ID	0x4365		
#define BCM4334_D11N_ID		0x4380		
#define BCM4334_D11N2G_ID	0x4381		
#define BCM4334_D11N5G_ID	0x4382		
#define BCM43341_D11N_ID	0x4386		
#define BCM43341_D11N2G_ID	0x4387		
#define BCM43341_D11N5G_ID	0x4388		
#define BCM4360_D11AC_ID	0x43a0
#define BCM4360_D11AC2G_ID	0x43a1
#define BCM4360_D11AC5G_ID	0x43a2


#define BCM943228HMB_SSID_VEN1	0x0607
#define BCM94313HMGBL_SSID_VEN1	0x0608
#define BCM94313HMG_SSID_VEN1	0x0609


#define BCM4335_D11AC_ID	0x43ae
#define BCM4335_D11AC2G_ID	0x43af
#define BCM4335_D11AC5G_ID	0x43b0
#define BCM4352_D11AC_ID	0x43b1		
#define BCM4352_D11AC2G_ID	0x43b2		
#define BCM4352_D11AC5G_ID	0x43b3		

#define	BCMGPRS_UART_ID		0x4333		
#define	BCMGPRS2_UART_ID	0x4344		
#define FPGA_JTAGM_ID		0x43f0		
#define BCM_JTAGM_ID		0x43f1		
#define SDIOH_FPGA_ID		0x43f2		
#define BCM_SDIOH_ID		0x43f3		
#define SDIOD_FPGA_ID		0x43f4		
#define SPIH_FPGA_ID		0x43f5		
#define BCM_SPIH_ID		0x43f6		
#define MIMO_FPGA_ID		0x43f8		
#define BCM_JTAGM2_ID		0x43f9		
#define SDHCI_FPGA_ID		0x43fa		
#define	BCM4402_ENET_ID		0x4402		
#define	BCM4402_V90_ID		0x4403		
#define	BCM4410_DEVICE_ID	0x4410		
#define	BCM4412_DEVICE_ID	0x4412		
#define	BCM4430_DEVICE_ID	0x4430		
#define	BCM4432_DEVICE_ID	0x4432		
#define	BCM4704_ENET_ID		0x4706		
#define	BCM4710_DEVICE_ID	0x4710		
#define	BCM47XX_AUDIO_ID	0x4711		
#define	BCM47XX_V90_ID		0x4712		
#define	BCM47XX_ENET_ID		0x4713		
#define	BCM47XX_EXT_ID		0x4714		
#define	BCM47XX_GMAC_ID		0x4715		
#define	BCM47XX_USBH_ID		0x4716		
#define	BCM47XX_USBD_ID		0x4717		
#define	BCM47XX_IPSEC_ID	0x4718		
#define	BCM47XX_ROBO_ID		0x4719		
#define	BCM47XX_USB20H_ID	0x471a		
#define	BCM47XX_USB20D_ID	0x471b		
#define	BCM47XX_ATA100_ID	0x471d		
#define	BCM47XX_SATAXOR_ID	0x471e		
#define	BCM47XX_GIGETH_ID	0x471f		
#define	BCM4712_MIPS_ID		0x4720		
#define	BCM4716_DEVICE_ID	0x4722		
#define BCM47XX_SMBUS_EMU_ID	0x47fe		
#define	BCM47XX_XOR_EMU_ID	0x47ff		
#define	EPI41210_DEVICE_ID	0xa0fa		
#define	EPI41230_DEVICE_ID	0xa10e		
#define JINVANI_SDIOH_ID	0x4743		
#define BCM27XX_SDIOH_ID	0x2702		
#define PCIXX21_FLASHMEDIA_ID	0x803b		
#define PCIXX21_SDIOH_ID	0x803c		
#define R5C822_SDIOH_ID		0x0822		
#define JMICRON_SDIOH_ID	0x2381		


#define	BCM4306_CHIP_ID		0x4306		
#define	BCM4311_CHIP_ID		0x4311		
#define	BCM43111_CHIP_ID	43111		
#define	BCM43112_CHIP_ID	43112		
#define	BCM4312_CHIP_ID		0x4312		
#define BCM4313_CHIP_ID		0x4313		
#define	BCM43131_CHIP_ID	43131		
#define	BCM4315_CHIP_ID		0x4315		
#define	BCM4318_CHIP_ID		0x4318		
#define	BCM4319_CHIP_ID		0x4319		
#define	BCM4320_CHIP_ID		0x4320		
#define	BCM4321_CHIP_ID		0x4321		
#define	BCM43217_CHIP_ID	43217		
#define	BCM4322_CHIP_ID		0x4322		
#define	BCM43221_CHIP_ID	43221		
#define	BCM43222_CHIP_ID	43222		
#define	BCM43224_CHIP_ID	43224		
#define	BCM43225_CHIP_ID	43225		
#define	BCM43227_CHIP_ID	43227		
#define	BCM43228_CHIP_ID	43228		
#define	BCM43226_CHIP_ID	43226		
#define	BCM43231_CHIP_ID	43231		
#define	BCM43234_CHIP_ID	43234		
#define	BCM43235_CHIP_ID	43235		
#define	BCM43236_CHIP_ID	43236		
#define	BCM43237_CHIP_ID	43237		
#define	BCM43238_CHIP_ID	43238		
#define	BCM43239_CHIP_ID	43239		
#define	BCM43420_CHIP_ID	43420		
#define	BCM43421_CHIP_ID	43421		
#define	BCM43428_CHIP_ID	43428		
#define	BCM43431_CHIP_ID	43431		
#define	BCM43460_CHIP_ID	43460		
#define	BCM4325_CHIP_ID		0x4325		
#define	BCM4328_CHIP_ID		0x4328		
#define	BCM4329_CHIP_ID		0x4329		
#define	BCM4331_CHIP_ID		0x4331		
#define BCM4336_CHIP_ID		0x4336		
#define BCM43362_CHIP_ID	43362		
#define BCM4330_CHIP_ID		0x4330		
#define BCM6362_CHIP_ID		0x6362		
#define BCM4314_CHIP_ID		0x4314		
#define BCM43142_CHIP_ID	43142		
#define	BCM4324_CHIP_ID		0x4324		
#define	BCM43242_CHIP_ID	43242		
#define BCM4334_CHIP_ID		0x4334		
#define BCM4360_CHIP_ID		0x4360          
#define BCM4352_CHIP_ID		0x4352          
#define BCM43526_CHIP_ID	0xAA06
#define BCM43341_CHIP_ID	43341		
#define BCM43342_CHIP_ID	43342		

#define BCM4335_CHIP_ID         0x4335

#define	BCM4342_CHIP_ID		4342		
#define	BCM4402_CHIP_ID		0x4402		
#define	BCM4704_CHIP_ID		0x4704		
#define	BCM4706_CHIP_ID		0x5300		
#define	BCM4710_CHIP_ID		0x4710		
#define	BCM4712_CHIP_ID		0x4712		
#define	BCM4716_CHIP_ID		0x4716		
#define	BCM47162_CHIP_ID	47162		
#define	BCM4748_CHIP_ID		0x4748		
#define	BCM4749_CHIP_ID		0x4749		
#define BCM4785_CHIP_ID		0x4785		
#define	BCM5350_CHIP_ID		0x5350		
#define	BCM5352_CHIP_ID		0x5352		
#define	BCM5354_CHIP_ID		0x5354		
#define BCM5365_CHIP_ID		0x5365		
#define	BCM5356_CHIP_ID		0x5356		
#define	BCM5357_CHIP_ID		0x5357		
#define	BCM53572_CHIP_ID	53572		


#define	BCM4303_PKG_ID		2		
#define	BCM4309_PKG_ID		1		
#define	BCM4712LARGE_PKG_ID	0		
#define	BCM4712SMALL_PKG_ID	1		
#define	BCM4712MID_PKG_ID	2		
#define BCM4328USBD11G_PKG_ID	2		
#define BCM4328USBDUAL_PKG_ID	3		
#define BCM4328SDIOD11G_PKG_ID	4		
#define BCM4328SDIODUAL_PKG_ID	5		
#define BCM4329_289PIN_PKG_ID	0		
#define BCM4329_182PIN_PKG_ID	1		
#define BCM5354E_PKG_ID		1		
#define	BCM4716_PKG_ID		8		
#define	BCM4717_PKG_ID		9		
#define	BCM4718_PKG_ID		10		
#define BCM5356_PKG_NONMODE	1		
#define BCM5358U_PKG_ID		8		
#define BCM5358_PKG_ID		9		
#define BCM47186_PKG_ID		10		
#define BCM5357_PKG_ID		11		
#define BCM5356U_PKG_ID		12		
#define BCM53572_PKG_ID		8		
#define BCM5357C0_PKG_ID	8		
#define BCM47188_PKG_ID		9		
#define BCM5358C0_PKG_ID	0xa		
#define BCM5356C0_PKG_ID	0xb		
#define BCM4331TT_PKG_ID        8		
#define BCM4331TN_PKG_ID        9		
#define BCM4331TNA0_PKG_ID     0xb		
#define	BCM4706L_PKG_ID		1		

#define HDLSIM5350_PKG_ID	1		
#define HDLSIM_PKG_ID		14		
#define HWSIM_PKG_ID		15		
#define BCM43224_FAB_CSM	0x8		
#define BCM43224_FAB_SMIC	0xa		
#define BCM4336_WLBGA_PKG_ID	0x8
#define BCM4330_WLBGA_PKG_ID	0x0
#define BCM4314PCIE_ARM_PKG_ID		(8 | 0)	
#define BCM4314SDIO_PKG_ID		(8 | 1)	
#define BCM4314PCIE_PKG_ID		(8 | 2)	
#define BCM4314SDIO_ARM_PKG_ID		(8 | 3)	
#define BCM4314SDIO_FPBGA_PKG_ID	(8 | 4)	
#define BCM4314DEV_PKG_ID		(8 | 6)	

#define PCIXX21_FLASHMEDIA0_ID	0x8033		
#define PCIXX21_SDIOH0_ID	0x8034		


#define	BFL_BTC2WIRE		0x00000001  
#define BFL_BTCOEX      0x00000001      
#define	BFL_PACTRL		0x00000002  
#define BFL_AIRLINEMODE	0x00000004  
#define	BFL_ADCDIV		0x00000008  
#define	BFL_RFPLL	        0x00000008  
#define	BFL_ENETROBO		0x00000010  
#define	BFL_NOPLLDOWN		0x00000020  
#define	BFL_CCKHIPWR		0x00000040  
#define	BFL_ENETADM		0x00000080  
#define	BFL_ENETVLAN		0x00000100  
#define	BFL_UNUSED		0x00000200
#define BFL_NOPCI		0x00000400  
#define BFL_FEM			0x00000800  
#define BFL_EXTLNA		0x00001000  
#define BFL_HGPA		0x00002000  
#define	BFL_BTC2WIRE_ALTGPIO	0x00004000  
#define	BFL_ALTIQ		0x00008000  
#define BFL_NOPA		0x00010000  
#define BFL_RSSIINV		0x00020000  
#define BFL_PAREF		0x00040000  
#define BFL_3TSWITCH		0x00080000  
#define BFL_PHASESHIFT		0x00100000  
#define BFL_BUCKBOOST		0x00200000  
#define BFL_FEM_BT		0x00400000  
#define BFL_NOCBUCK		0x00800000  
#define BFL_CCKFAVOREVM		0x01000000  
#define BFL_PALDO		0x02000000  
#define BFL_LNLDO2_2P5		0x04000000  
#define BFL_FASTPWR		0x08000000
#define BFL_UCPWRCTL_MININDX	0x08000000  
#define BFL_EXTLNA_5GHz		0x10000000  
#define BFL_TRSW_1by2		0x20000000  
#define BFL_LO_TRSW_R_5GHz	0x40000000  
#define BFL_ELNA_GAINDEF	0x80000000  
#define BFL_EXTLNA_TX	0x20000000	


#define BFL2_RXBB_INT_REG_DIS	0x00000001  
#define BFL2_APLL_WAR		0x00000002  
#define BFL2_TXPWRCTRL_EN	0x00000004  
#define BFL2_2X4_DIV		0x00000008  
#define BFL2_5G_PWRGAIN		0x00000010  
#define BFL2_PCIEWAR_OVR	0x00000020  
#define BFL2_CAESERS_BRD	0x00000040  
#define BFL2_BTC3WIRE		0x00000080  
#define BFL2_BTCLEGACY          0x00000080  
#define BFL2_SKWRKFEM_BRD	0x00000100  
#define BFL2_SPUR_WAR		0x00000200  
#define BFL2_GPLL_WAR		0x00000400  
#define BFL2_TRISTATE_LED	0x00000800  
#define BFL2_SINGLEANT_CCK	0x00001000  
#define BFL2_2G_SPUR_WAR	0x00002000  
#define BFL2_BPHY_ALL_TXCORES	0x00004000  
#define BFL2_FCC_BANDEDGE_WAR	0x00008000  
#define BFL2_GPLL_WAR2	        0x00010000  
#define BFL2_IPALVLSHIFT_3P3    0x00020000
#define BFL2_INTERNDET_TXIQCAL  0x00040000  
#define BFL2_XTALBUFOUTEN       0x00080000  
				
				

#define BFL2_ANAPACTRL_2G	0x00100000  
#define BFL2_ANAPACTRL_5G	0x00200000  
#define BFL2_ELNACTRL_TRSW_2G	0x00400000  
#define BFL2_BT_SHARE_ANT0	0x00800000  
#define BFL2_TEMPSENSE_HIGHER	0x01000000  
#define BFL2_BTC3WIREONLY       0x02000000  
#define BFL2_PWR_NOMINAL	0x04000000  
#define BFL2_EXTLNA_PWRSAVE	0x08000000  
						
#define BFL2_4313_RADIOREG	0x10000000
									   
#define BFL2_SDR_EN		0x20000000	


#define	BOARD_GPIO_BTC3W_IN	0x850	
#define	BOARD_GPIO_BTC3W_OUT	0x020	
#define	BOARD_GPIO_BTCMOD_IN	0x010	
#define	BOARD_GPIO_BTCMOD_OUT	0x020	
#define	BOARD_GPIO_BTC_IN	0x080	
#define	BOARD_GPIO_BTC_OUT	0x100	
#define	BOARD_GPIO_PACTRL	0x200	
#define BOARD_GPIO_12		0x1000	
#define BOARD_GPIO_13		0x2000	
#define BOARD_GPIO_BTC4_IN	0x0800	
#define BOARD_GPIO_BTC4_BT	0x2000	
#define BOARD_GPIO_BTC4_STAT	0x4000	
#define BOARD_GPIO_BTC4_WLAN	0x8000	
#define	BOARD_GPIO_1_WLAN_PWR	0x02	
#define	BOARD_GPIO_3_WLAN_PWR	0x08	
#define	BOARD_GPIO_4_WLAN_PWR	0x10	

#define GPIO_BTC4W_OUT_4312  0x010  
#define GPIO_BTC4W_OUT_43224  0x020  
#define GPIO_BTC4W_OUT_43224_SHARED  0x0e0  
#define GPIO_BTC4W_OUT_43225  0x0e0  
#define GPIO_BTC4W_OUT_43421  0x020  
#define GPIO_BTC4W_OUT_4313  0x060  
#define GPIO_BTC4W_OUT_4331_SHARED  0x010  

#define	PCI_CFG_GPIO_SCS	0x10	
#define PCI_CFG_GPIO_HWRAD	0x20	
#define PCI_CFG_GPIO_XTAL	0x40	
#define PCI_CFG_GPIO_PLL	0x80	


#define PLL_DELAY		150		
#define FREF_DELAY		200		
#define MIN_SLOW_CLK		32		
#define	XTAL_ON_DELAY		1000		



#define BCM943341WLABGS_SSID	0x062d

#define GPIO_NUMPINS		32


#define RDL_RAM_BASE_4319 0x60000000
#define RDL_RAM_BASE_4329 0x60000000
#define RDL_RAM_SIZE_4319 0x48000
#define RDL_RAM_SIZE_4329  0x48000
#define RDL_RAM_SIZE_43236 0x70000
#define RDL_RAM_BASE_43236 0x60000000
#define RDL_RAM_SIZE_4328 0x60000
#define RDL_RAM_BASE_4328 0x80000000
#define RDL_RAM_SIZE_4322 0x60000
#define RDL_RAM_BASE_4322 0x60000000


#define MUXENAB_UART		0x00000001
#define MUXENAB_GPIO		0x00000002
#define MUXENAB_ERCX		0x00000004	
#define MUXENAB_JTAG		0x00000008
#define MUXENAB_HOST_WAKE	0x00000010	
#define MUXENAB_I2S_EN		0x00000020
#define MUXENAB_I2S_MASTER	0x00000040
#define MUXENAB_I2S_FULL	0x00000080
#define MUXENAB_SFLASH		0x00000100
#define MUXENAB_RFSWCTRL0	0x00000200
#define MUXENAB_RFSWCTRL1	0x00000400
#define MUXENAB_RFSWCTRL2	0x00000800
#define MUXENAB_SECI		0x00001000
#define MUXENAB_BT_LEGACY	0x00002000
#define MUXENAB_HOST_WAKE1	0x00004000	


#define FLASH_KERNEL_NFLASH	0x00000001
#define FLASH_BOOT_NFLASH	0x00000002

#endif 
