/***************************************************************************/

/*
 *	linux/arch/m68knommu/platform/5272/config.c
 *
 *	Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2002, SnapGear Inc. (www.snapgear.com)
 */

/***************************************************************************/

#include <linux/kernel.h>
#include <linux/param.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/phy.h>
#include <linux/phy_fixed.h>
#include <asm/machdep.h>
#include <asm/coldfire.h>
#include <asm/mcfsim.h>
#include <asm/mcfuart.h>

/***************************************************************************/

/*
 *	Some platforms need software versions of the GPIO data registers.
 */
unsigned short ppdata;
unsigned char ledbank = 0xff;

/***************************************************************************/

static void __init m5272_uarts_init(void)
{
	u32 v;

	/* Enable the output lines for the serial ports */
	v = readl(MCF_MBAR + MCFSIM_PBCNT);
	v = (v & ~0x000000ff) | 0x00000055;
	writel(v, MCF_MBAR + MCFSIM_PBCNT);

	v = readl(MCF_MBAR + MCFSIM_PDCNT);
	v = (v & ~0x000003fc) | 0x000002a8;
	writel(v, MCF_MBAR + MCFSIM_PDCNT);
}

/***************************************************************************/

static void m5272_cpu_reset(void)
{
	local_irq_disable();
	/* Set watchdog to reset, and enabled */
	__raw_writew(0, MCF_MBAR + MCFSIM_WIRR);
	__raw_writew(1, MCF_MBAR + MCFSIM_WRRR);
	__raw_writew(0, MCF_MBAR + MCFSIM_WCR);
	for (;;)
		/* wait for watchdog to timeout */;
}

/***************************************************************************/

void __init config_BSP(char *commandp, int size)
{
#if defined (CONFIG_MOD5272)
	volatile unsigned char	*pivrp;

	/* Set base of device vectors to be 64 */
	pivrp = (volatile unsigned char *) (MCF_MBAR + MCFSIM_PIVR);
	*pivrp = 0x40;
#endif

#if defined(CONFIG_NETtel) || defined(CONFIG_SCALES)
	/* Copy command line from FLASH to local buffer... */
	memcpy(commandp, (char *) 0xf0004000, size);
	commandp[size-1] = 0;
#elif defined(CONFIG_CANCam)
	/* Copy command line from FLASH to local buffer... */
	memcpy(commandp, (char *) 0xf0010000, size);
	commandp[size-1] = 0;
#endif

	mach_reset = m5272_cpu_reset;
	mach_sched_init = hw_timer_init;
}

/***************************************************************************/

/*
 * Some 5272 based boards have the FEC ethernet diectly connected to
 * an ethernet switch. In this case we need to use the fixed phy type,
 * and we need to declare it early in boot.
 */
static struct fixed_phy_status nettel_fixed_phy_status __initdata = {
	.link	= 1,
	.speed	= 100,
	.duplex	= 0,
};

/***************************************************************************/

static int __init init_BSP(void)
{
	m5272_uarts_init();
	fixed_phy_add(PHY_POLL, 0, &nettel_fixed_phy_status);
	return 0;
}

arch_initcall(init_BSP);

/***************************************************************************/
