/**
 * @file timer_int.c
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author John Levon <levon@movementarian.org>
 */

#include <linux/kernel.h>
#include <linux/notifier.h>
#include <linux/smp.h>
#include <linux/oprofile.h>
#include <linux/profile.h>
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/hrtimer.h>
#include <asm/irq_regs.h>
#include <asm/ptrace.h>

#include "oprof.h"

static DEFINE_PER_CPU(struct hrtimer, oprofile_hrtimer);
static int ctr_running;

static enum hrtimer_restart oprofile_hrtimer_notify(struct hrtimer *hrtimer)
{
	oprofile_add_sample(get_irq_regs(), 0);
	hrtimer_forward_now(hrtimer, ns_to_ktime(TICK_NSEC));
	return HRTIMER_RESTART;
}

static void __oprofile_hrtimer_start(void *unused)
{
	struct hrtimer *hrtimer = &__get_cpu_var(oprofile_hrtimer);

	if (!ctr_running)
		return;

	hrtimer_init(hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer->function = oprofile_hrtimer_notify;

	hrtimer_start(hrtimer, ns_to_ktime(TICK_NSEC),
		      HRTIMER_MODE_REL_PINNED);
}

static int oprofile_hrtimer_start(void)
{
	get_online_cpus();
	ctr_running = 1;
	on_each_cpu(__oprofile_hrtimer_start, NULL, 1);
	put_online_cpus();
	return 0;
}

static void __oprofile_hrtimer_stop(int cpu)
{
	struct hrtimer *hrtimer = &per_cpu(oprofile_hrtimer, cpu);

	if (!ctr_running)
		return;

	hrtimer_cancel(hrtimer);
}

static void oprofile_hrtimer_stop(void)
{
	int cpu;

	get_online_cpus();
	for_each_online_cpu(cpu)
		__oprofile_hrtimer_stop(cpu);
	ctr_running = 0;
	put_online_cpus();
}

static int __cpuinit oprofile_cpu_notify(struct notifier_block *self,
					 unsigned long action, void *hcpu)
{
	long cpu = (long) hcpu;

	switch (action) {
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		smp_call_function_single(cpu, __oprofile_hrtimer_start,
					 NULL, 1);
		break;
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		__oprofile_hrtimer_stop(cpu);
		break;
	}
	return NOTIFY_OK;
}

static struct notifier_block __refdata oprofile_cpu_notifier = {
	.notifier_call = oprofile_cpu_notify,
};

static int oprofile_hrtimer_setup(void)
{
	return register_hotcpu_notifier(&oprofile_cpu_notifier);
}

static void oprofile_hrtimer_shutdown(void)
{
	unregister_hotcpu_notifier(&oprofile_cpu_notifier);
}

#ifndef OP_COUNTER_H
#define OP_COUNTER_H

/*
 * Per performance monitor configuration as set via oprofilefs.
 */
struct op_counter_config {
    unsigned long count;
    unsigned long enabled;
    unsigned long event;
    unsigned long unit_mask;
    unsigned long kernel;
    unsigned long user;
};

#endif /* OP_COUNTER_H */

struct op_counter_config dummy_config = { .count = 4 };

static int op_create_files(struct super_block *sb, struct dentry *root)
{
    unsigned int i;

    for (i = 0; i < 1; i++) {
        struct dentry *dir;
        char buf[4];

        snprintf(buf, sizeof buf, "%d", i);
        dir = oprofilefs_mkdir(sb, root, buf);
        oprofilefs_create_ulong(sb, dir, "enabled", &dummy_config.enabled);
        oprofilefs_create_ulong(sb, dir, "event", &dummy_config.event);
        oprofilefs_create_ulong(sb, dir, "count", &dummy_config.count);
        oprofilefs_create_ulong(sb, dir, "unit_mask", &dummy_config.unit_mask);
        oprofilefs_create_ulong(sb, dir, "kernel", &dummy_config.kernel);
        oprofilefs_create_ulong(sb, dir, "user", &dummy_config.user);
    }
    return 0;
}

int oprofile_timer_init(struct oprofile_operations *ops)
{
	ops->create_files	= op_create_files;
	ops->setup		= oprofile_hrtimer_setup;
	ops->shutdown		= oprofile_hrtimer_shutdown;
	ops->start		= oprofile_hrtimer_start;
	ops->stop		= oprofile_hrtimer_stop;
	ops->cpu_type		= "timer";
	printk(KERN_INFO "oprofile: using timer interrupt.\n");
	return 0;
}
