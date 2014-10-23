#ifndef __ASM_MACH_CLKDEV_H
#define __ASM_MACH_CLKDEV_H

#include <plat/clock.h>

struct clk {
	const struct clk_ops	*ops;
	unsigned long		rate;
	const struct icst_params *params;
};

#define __clk_get(clk) ({ 1; })
#define __clk_put(clk) do { } while (0)

#endif
