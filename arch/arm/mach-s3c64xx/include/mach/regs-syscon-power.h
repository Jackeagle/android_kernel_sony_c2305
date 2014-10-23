/* arch/arm/plat-s3c64xx/include/plat/regs-syscon-power.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      http://armlinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * S3C64XX - syscon power and sleep control registers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __PLAT_S3C64XX_REGS_SYSCON_POWER_H
#define __PLAT_S3C64XX_REGS_SYSCON_POWER_H __FILE__

#define S3C64XX_PWR_CFG				S3C_SYSREG(0x804)

#define S3C64XX_PWRCFG_OSC_OTG_DISABLE		(1 << 17)
#define S3C64XX_PWRCFG_MMC2_DISABLE		(1 << 16)
#define S3C64XX_PWRCFG_MMC1_DISABLE		(1 << 15)
#define S3C64XX_PWRCFG_MMC0_DISABLE		(1 << 14)
#define S3C64XX_PWRCFG_HSI_DISABLE		(1 << 13)
#define S3C64XX_PWRCFG_TS_DISABLE		(1 << 12)
#define S3C64XX_PWRCFG_RTC_TICK_DISABLE		(1 << 11)
#define S3C64XX_PWRCFG_RTC_ALARM_DISABLE	(1 << 10)
#define S3C64XX_PWRCFG_MSM_DISABLE		(1 << 9)
#define S3C64XX_PWRCFG_KEY_DISABLE		(1 << 8)
#define S3C64XX_PWRCFG_BATF_DISABLE		(1 << 7)

#define S3C64XX_PWRCFG_CFG_WFI_MASK		(0x3 << 5)
#define S3C64XX_PWRCFG_CFG_WFI_SHIFT		(5)
#define S3C64XX_PWRCFG_CFG_WFI_IGNORE		(0x0 << 5)
#define S3C64XX_PWRCFG_CFG_WFI_IDLE		(0x1 << 5)
#define S3C64XX_PWRCFG_CFG_WFI_STOP		(0x2 << 5)
#define S3C64XX_PWRCFG_CFG_WFI_SLEEP		(0x3 << 5)

#define S3C64XX_PWRCFG_CFG_BATFLT_MASK		(0x3 << 3)
#define S3C64XX_PWRCFG_CFG_BATFLT_SHIFT		(3)
#define S3C64XX_PWRCFG_CFG_BATFLT_IGNORE	(0x0 << 3)
#define S3C64XX_PWRCFG_CFG_BATFLT_IRQ		(0x1 << 3)
#define S3C64XX_PWRCFG_CFG_BATFLT_SLEEP		(0x3 << 3)

#define S3C64XX_PWRCFG_CFG_BAT_WAKE		(1 << 2)
#define S3C64XX_PWRCFG_OSC27_EN			(1 << 0)

#define S3C64XX_EINT_MASK			S3C_SYSREG(0x808)

#define S3C64XX_NORMAL_CFG			S3C_SYSREG(0x810)

#define S3C64XX_NORMALCFG_IROM_ON		(1 << 30)
#define S3C64XX_NORMALCFG_DOMAIN_ETM_ON		(1 << 16)
#define S3C64XX_NORMALCFG_DOMAIN_S_ON		(1 << 15)
#define S3C64XX_NORMALCFG_DOMAIN_F_ON		(1 << 14)
#define S3C64XX_NORMALCFG_DOMAIN_P_ON		(1 << 13)
#define S3C64XX_NORMALCFG_DOMAIN_I_ON		(1 << 12)
#define S3C64XX_NORMALCFG_DOMAIN_G_ON		(1 << 10)
#define S3C64XX_NORMALCFG_DOMAIN_V_ON		(1 << 9)

#define S3C64XX_STOP_CFG			S3C_SYSREG(0x814)

#define S3C64XX_STOPCFG_MEMORY_ARM_ON		(1 << 29)
#define S3C64XX_STOPCFG_TOP_MEMORY_ON		(1 << 20)
#define S3C64XX_STOPCFG_ARM_LOGIC_ON		(1 << 17)
#define S3C64XX_STOPCFG_TOP_LOGIC_ON		(1 << 8)
#define S3C64XX_STOPCFG_OSC_EN			(1 << 0)

#define S3C64XX_SLEEP_CFG			S3C_SYSREG(0x818)

#define S3C64XX_SLEEPCFG_OSC_EN			(1 << 0)

#define S3C64XX_STOP_MEM_CFG			S3C_SYSREG(0x81c)

#define S3C64XX_STOPMEMCFG_MODEMIF_RETAIN	(1 << 6)
#define S3C64XX_STOPMEMCFG_HOSTIF_RETAIN	(1 << 5)
#define S3C64XX_STOPMEMCFG_OTG_RETAIN		(1 << 4)
#define S3C64XX_STOPMEMCFG_HSMCC_RETAIN		(1 << 3)
#define S3C64XX_STOPMEMCFG_IROM_RETAIN		(1 << 2)
#define S3C64XX_STOPMEMCFG_IRDA_RETAIN		(1 << 1)
#define S3C64XX_STOPMEMCFG_NFCON_RETAIN		(1 << 0)

#define S3C64XX_OSC_STABLE			S3C_SYSREG(0x824)
#define S3C64XX_PWR_STABLE			S3C_SYSREG(0x828)

#define S3C64XX_WAKEUP_STAT			S3C_SYSREG(0x908)

#define S3C64XX_WAKEUPSTAT_MMC2			(1 << 11)
#define S3C64XX_WAKEUPSTAT_MMC1			(1 << 10)
#define S3C64XX_WAKEUPSTAT_MMC0			(1 << 9)
#define S3C64XX_WAKEUPSTAT_HSI			(1 << 8)
#define S3C64XX_WAKEUPSTAT_BATFLT		(1 << 6)
#define S3C64XX_WAKEUPSTAT_MSM			(1 << 5)
#define S3C64XX_WAKEUPSTAT_KEY			(1 << 4)
#define S3C64XX_WAKEUPSTAT_TS			(1 << 3)
#define S3C64XX_WAKEUPSTAT_RTC_TICK		(1 << 2)
#define S3C64XX_WAKEUPSTAT_RTC_ALARM		(1 << 1)
#define S3C64XX_WAKEUPSTAT_EINT			(1 << 0)

#define S3C64XX_BLK_PWR_STAT			S3C_SYSREG(0x90c)

#define S3C64XX_BLKPWRSTAT_G			(1 << 7)
#define S3C64XX_BLKPWRSTAT_ETM			(1 << 6)
#define S3C64XX_BLKPWRSTAT_S			(1 << 5)
#define S3C64XX_BLKPWRSTAT_F			(1 << 4)
#define S3C64XX_BLKPWRSTAT_P			(1 << 3)
#define S3C64XX_BLKPWRSTAT_I			(1 << 2)
#define S3C64XX_BLKPWRSTAT_V			(1 << 1)
#define S3C64XX_BLKPWRSTAT_TOP			(1 << 0)

#define S3C64XX_INFORM0				S3C_SYSREG(0xA00)
#define S3C64XX_INFORM1				S3C_SYSREG(0xA04)
#define S3C64XX_INFORM2				S3C_SYSREG(0xA08)
#define S3C64XX_INFORM3				S3C_SYSREG(0xA0C)

#endif /* __PLAT_S3C64XX_REGS_SYSCON_POWER_H */
