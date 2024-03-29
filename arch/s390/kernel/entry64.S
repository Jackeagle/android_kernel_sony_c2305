/*
 *  arch/s390/kernel/entry64.S
 *    S390 low-level entry points.
 *
 *    Copyright (C) IBM Corp. 1999,2012
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *		 Hartmut Penner (hp@de.ibm.com),
 *		 Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#include <linux/init.h>
#include <linux/linkage.h>
#include <asm/cache.h>
#include <asm/errno.h>
#include <asm/ptrace.h>
#include <asm/thread_info.h>
#include <asm/asm-offsets.h>
#include <asm/unistd.h>
#include <asm/page.h>

__PT_R0      =	__PT_GPRS
__PT_R1      =	__PT_GPRS + 8
__PT_R2      =	__PT_GPRS + 16
__PT_R3      =	__PT_GPRS + 24
__PT_R4      =	__PT_GPRS + 32
__PT_R5      =	__PT_GPRS + 40
__PT_R6      =	__PT_GPRS + 48
__PT_R7      =	__PT_GPRS + 56
__PT_R8      =	__PT_GPRS + 64
__PT_R9      =	__PT_GPRS + 72
__PT_R10     =	__PT_GPRS + 80
__PT_R11     =	__PT_GPRS + 88
__PT_R12     =	__PT_GPRS + 96
__PT_R13     =	__PT_GPRS + 104
__PT_R14     =	__PT_GPRS + 112
__PT_R15     =	__PT_GPRS + 120

STACK_SHIFT = PAGE_SHIFT + THREAD_ORDER
STACK_SIZE  = 1 << STACK_SHIFT

_TIF_WORK_SVC = (_TIF_SIGPENDING | _TIF_NOTIFY_RESUME | _TIF_NEED_RESCHED | \
		 _TIF_MCCK_PENDING | _TIF_PER_TRAP )
_TIF_WORK_INT = (_TIF_SIGPENDING | _TIF_NOTIFY_RESUME | _TIF_NEED_RESCHED | \
		 _TIF_MCCK_PENDING)
_TIF_TRACE    = (_TIF_SYSCALL_TRACE | _TIF_SYSCALL_AUDIT | _TIF_SECCOMP | \
		 _TIF_SYSCALL_TRACEPOINT)
_TIF_EXIT_SIE = (_TIF_SIGPENDING | _TIF_NEED_RESCHED | _TIF_MCCK_PENDING)

#define BASED(name) name-system_call(%r13)

	.macro	TRACE_IRQS_ON
#ifdef CONFIG_TRACE_IRQFLAGS
	basr	%r2,%r0
	brasl	%r14,trace_hardirqs_on_caller
#endif
	.endm

	.macro	TRACE_IRQS_OFF
#ifdef CONFIG_TRACE_IRQFLAGS
	basr	%r2,%r0
	brasl	%r14,trace_hardirqs_off_caller
#endif
	.endm

	.macro	LOCKDEP_SYS_EXIT
#ifdef CONFIG_LOCKDEP
	tm	__PT_PSW+1(%r11),0x01	# returning to user ?
	jz	.+10
	brasl	%r14,lockdep_sys_exit
#endif
	.endm

	.macro SPP newpp
#if defined(CONFIG_KVM) || defined(CONFIG_KVM_MODULE)
	tm	__LC_MACHINE_FLAGS+6,0x20	# MACHINE_FLAG_SPP
	jz	.+8
	.insn	s,0xb2800000,\newpp
#endif
	.endm

	.macro	HANDLE_SIE_INTERCEPT scratch
#if defined(CONFIG_KVM) || defined(CONFIG_KVM_MODULE)
	tm	__TI_flags+6(%r12),_TIF_SIE>>8
	jz	.+42
	tm	__LC_MACHINE_FLAGS+6,0x20	# MACHINE_FLAG_SPP
	jz	.+8
	.insn	s,0xb2800000,BASED(.Lhost_id)	# set host id
	lgr	\scratch,%r9
	slg	\scratch,BASED(.Lsie_loop)
	clg	\scratch,BASED(.Lsie_length)
	jhe	.+10
	lg	%r9,BASED(.Lsie_loop)
#endif
	.endm

	.macro	CHECK_STACK stacksize,savearea
#ifdef CONFIG_CHECK_STACK
	tml	%r15,\stacksize - CONFIG_STACK_GUARD
	lghi	%r14,\savearea
	jz	stack_overflow
#endif
	.endm

	.macro	SWITCH_ASYNC savearea,stack,shift
	tmhh	%r8,0x0001		# interrupting from user ?
	jnz	1f
	lgr	%r14,%r9
	slg	%r14,BASED(.Lcritical_start)
	clg	%r14,BASED(.Lcritical_length)
	jhe	0f
	lghi	%r11,\savearea		# inside critical section, do cleanup
	brasl	%r14,cleanup_critical
	tmhh	%r8,0x0001		# retest problem state after cleanup
	jnz	1f
0:	lg	%r14,\stack		# are we already on the target stack?
	slgr	%r14,%r15
	srag	%r14,%r14,\shift
	jnz	1f
	CHECK_STACK 1<<\shift,\savearea
	j	2f
1:	lg	%r15,\stack		# load target stack
2:	aghi	%r15,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	la	%r11,STACK_FRAME_OVERHEAD(%r15)
	.endm

	.macro UPDATE_VTIME scratch,enter_timer
	lg	\scratch,__LC_EXIT_TIMER
	slg	\scratch,\enter_timer
	alg	\scratch,__LC_USER_TIMER
	stg	\scratch,__LC_USER_TIMER
	lg	\scratch,__LC_LAST_UPDATE_TIMER
	slg	\scratch,__LC_EXIT_TIMER
	alg	\scratch,__LC_SYSTEM_TIMER
	stg	\scratch,__LC_SYSTEM_TIMER
	mvc	__LC_LAST_UPDATE_TIMER(8),\enter_timer
	.endm

	.macro	LAST_BREAK scratch
	srag	\scratch,%r10,23
	jz	.+10
	stg	%r10,__TI_last_break(%r12)
	.endm

	.macro REENABLE_IRQS
	stg	%r8,__LC_RETURN_PSW
	ni	__LC_RETURN_PSW,0xbf
	ssm	__LC_RETURN_PSW
	.endm

	.section .kprobes.text, "ax"

/*
 * Scheduler resume function, called by switch_to
 *  gpr2 = (task_struct *) prev
 *  gpr3 = (task_struct *) next
 * Returns:
 *  gpr2 = prev
 */
ENTRY(__switch_to)
	lg	%r4,__THREAD_info(%r2)		# get thread_info of prev
	lg	%r5,__THREAD_info(%r3)		# get thread_info of next
	tm	__TI_flags+7(%r4),_TIF_MCCK_PENDING # machine check pending?
	jz	0f
	ni	__TI_flags+7(%r4),255-_TIF_MCCK_PENDING	# clear flag in prev
	oi	__TI_flags+7(%r5),_TIF_MCCK_PENDING	# set it in next
0:	stmg	%r6,%r15,__SF_GPRS(%r15)	# store gprs of prev task
	stg	%r15,__THREAD_ksp(%r2)		# store kernel stack of prev
	lg	%r15,__THREAD_ksp(%r3)		# load kernel stack of next
	lctl	%c4,%c4,__TASK_pid(%r3)		# load pid to control reg. 4
	lmg	%r6,%r15,__SF_GPRS(%r15)	# load gprs of next task
	stg	%r3,__LC_CURRENT		# store task struct of next
	mvc	__LC_CURRENT_PID+4(4,%r0),__TASK_pid(%r3) # store pid of next
	stg	%r5,__LC_THREAD_INFO		# store thread info of next
	aghi	%r5,STACK_SIZE			# end of kernel stack of next
	stg	%r5,__LC_KERNEL_STACK		# store end of kernel stack
	br	%r14

__critical_start:
/*
 * SVC interrupt handler routine. System calls are synchronous events and
 * are executed with interrupts enabled.
 */

ENTRY(system_call)
	stpt	__LC_SYNC_ENTER_TIMER
sysc_stmg:
	stmg	%r8,%r15,__LC_SAVE_AREA_SYNC
	lg	%r10,__LC_LAST_BREAK
	lg	%r12,__LC_THREAD_INFO
	larl	%r13,system_call
sysc_per:
	lg	%r15,__LC_KERNEL_STACK
	aghi	%r15,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	la	%r11,STACK_FRAME_OVERHEAD(%r15)	# pointer to pt_regs
sysc_vtime:
	UPDATE_VTIME %r13,__LC_SYNC_ENTER_TIMER
	LAST_BREAK %r13
	stmg	%r0,%r7,__PT_R0(%r11)
	mvc	__PT_R8(64,%r11),__LC_SAVE_AREA_SYNC
	mvc	__PT_PSW(16,%r11),__LC_SVC_OLD_PSW
	mvc	__PT_INT_CODE(4,%r11),__LC_SVC_ILC
sysc_do_svc:
	oi	__TI_flags+7(%r12),_TIF_SYSCALL
	llgh	%r8,__PT_INT_CODE+2(%r11)
	slag	%r8,%r8,2			# shift and test for svc 0
	jnz	sysc_nr_ok
	# svc 0: system call number in %r1
	llgfr	%r1,%r1				# clear high word in r1
	cghi	%r1,NR_syscalls
	jnl	sysc_nr_ok
	sth	%r1,__PT_INT_CODE+2(%r11)
	slag	%r8,%r1,2
sysc_nr_ok:
	larl	%r10,sys_call_table		# 64 bit system call table
#ifdef CONFIG_COMPAT
	tm	__TI_flags+5(%r12),(_TIF_31BIT>>16)
	jno	sysc_noemu
	larl	%r10,sys_call_table_emu		# 31 bit system call table
sysc_noemu:
#endif
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	stg	%r2,__PT_ORIG_GPR2(%r11)
	stg	%r7,STACK_FRAME_OVERHEAD(%r15)
	lgf	%r9,0(%r8,%r10)			# get system call add.
	tm	__TI_flags+6(%r12),_TIF_TRACE >> 8
	jnz	sysc_tracesys
	basr	%r14,%r9			# call sys_xxxx
	stg	%r2,__PT_R2(%r11)		# store return value

sysc_return:
	LOCKDEP_SYS_EXIT
sysc_tif:
	tm	__PT_PSW+1(%r11),0x01		# returning to user ?
	jno	sysc_restore
	tm	__TI_flags+7(%r12),_TIF_WORK_SVC
	jnz	sysc_work			# check for work
	ni	__TI_flags+7(%r12),255-_TIF_SYSCALL
sysc_restore:
	lg	%r14,__LC_VDSO_PER_CPU
	lmg	%r0,%r10,__PT_R0(%r11)
	mvc	__LC_RETURN_PSW(16),__PT_PSW(%r11)
	stpt	__LC_EXIT_TIMER
	mvc	__VDSO_ECTG_BASE(16,%r14),__LC_EXIT_TIMER
	lmg	%r11,%r15,__PT_R11(%r11)
	lpswe	__LC_RETURN_PSW
sysc_done:

#
# One of the work bits is on. Find out which one.
#
sysc_work:
	tm	__TI_flags+7(%r12),_TIF_MCCK_PENDING
	jo	sysc_mcck_pending
	tm	__TI_flags+7(%r12),_TIF_NEED_RESCHED
	jo	sysc_reschedule
	tm	__TI_flags+7(%r12),_TIF_SIGPENDING
	jo	sysc_sigpending
	tm	__TI_flags+7(%r12),_TIF_NOTIFY_RESUME
	jo	sysc_notify_resume
	tm	__TI_flags+7(%r12),_TIF_PER_TRAP
	jo	sysc_singlestep
	j	sysc_return		# beware of critical section cleanup

#
# _TIF_NEED_RESCHED is set, call schedule
#
sysc_reschedule:
	larl	%r14,sysc_return
	jg	schedule

#
# _TIF_MCCK_PENDING is set, call handler
#
sysc_mcck_pending:
	larl	%r14,sysc_return
	jg	s390_handle_mcck	# TIF bit will be cleared by handler

#
# _TIF_SIGPENDING is set, call do_signal
#
sysc_sigpending:
	ni	__TI_flags+7(%r12),255-_TIF_PER_TRAP # clear TIF_PER_TRAP
	lgr	%r2,%r11		# pass pointer to pt_regs
	brasl	%r14,do_signal
	tm	__TI_flags+7(%r12),_TIF_SYSCALL
	jno	sysc_return
	lmg	%r2,%r7,__PT_R2(%r11)	# load svc arguments
	lghi	%r8,0			# svc 0 returns -ENOSYS
	lh	%r1,__PT_INT_CODE+2(%r11)	# load new svc number
	cghi	%r1,NR_syscalls
	jnl	sysc_nr_ok		# invalid svc number -> do svc 0
	slag	%r8,%r1,2
	j	sysc_nr_ok		# restart svc

#
# _TIF_NOTIFY_RESUME is set, call do_notify_resume
#
sysc_notify_resume:
	lgr	%r2,%r11		# pass pointer to pt_regs
	larl	%r14,sysc_return
	jg	do_notify_resume

#
# _TIF_PER_TRAP is set, call do_per_trap
#
sysc_singlestep:
	ni	__TI_flags+7(%r12),255-(_TIF_SYSCALL | _TIF_PER_TRAP)
	lgr	%r2,%r11		# pass pointer to pt_regs
	larl	%r14,sysc_return
	jg	do_per_trap

#
# call tracehook_report_syscall_entry/tracehook_report_syscall_exit before
# and after the system call
#
sysc_tracesys:
	lgr	%r2,%r11		# pass pointer to pt_regs
	la	%r3,0
	llgh	%r0,__PT_INT_CODE+2(%r11)
	stg	%r0,__PT_R2(%r11)
	brasl	%r14,do_syscall_trace_enter
	lghi	%r0,NR_syscalls
	clgr	%r0,%r2
	jnh	sysc_tracenogo
	sllg	%r8,%r2,2
	lgf	%r9,0(%r8,%r10)
sysc_tracego:
	lmg	%r3,%r7,__PT_R3(%r11)
	stg	%r7,STACK_FRAME_OVERHEAD(%r15)
	lg	%r2,__PT_ORIG_GPR2(%r11)
	basr	%r14,%r9		# call sys_xxx
	stg	%r2,__PT_R2(%r11)	# store return value
sysc_tracenogo:
	tm	__TI_flags+6(%r12),_TIF_TRACE >> 8
	jz	sysc_return
	lgr	%r2,%r11		# pass pointer to pt_regs
	larl	%r14,sysc_return
	jg	do_syscall_trace_exit

#
# a new process exits the kernel with ret_from_fork
#
ENTRY(ret_from_fork)
	la	%r11,STACK_FRAME_OVERHEAD(%r15)
	lg	%r12,__LC_THREAD_INFO
	tm	__PT_PSW+1(%r11),0x01	# forking a kernel thread ?
	jo	0f
	stg	%r15,__PT_R15(%r11)	# store stack pointer for new kthread
0:	brasl	%r14,schedule_tail
	TRACE_IRQS_ON
	ssm	__LC_SVC_NEW_PSW	# reenable interrupts
	j	sysc_tracenogo

#
# kernel_execve function needs to deal with pt_regs that is not
# at the usual place
#
ENTRY(kernel_execve)
	stmg	%r12,%r15,96(%r15)
	lgr	%r14,%r15
	aghi	%r15,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	stg	%r14,__SF_BACKCHAIN(%r15)
	la	%r12,STACK_FRAME_OVERHEAD(%r15)
	xc	0(__PT_SIZE,%r12),0(%r12)
	lgr	%r5,%r12
	brasl	%r14,do_execve
	ltgfr	%r2,%r2
	je	0f
	aghi	%r15,(STACK_FRAME_OVERHEAD + __PT_SIZE)
	lmg	%r12,%r15,96(%r15)
	br	%r14
	# execve succeeded.
0:	ssm	__LC_PGM_NEW_PSW	# disable I/O and ext. interrupts
	lg	%r15,__LC_KERNEL_STACK	# load ksp
	aghi	%r15,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	la	%r11,STACK_FRAME_OVERHEAD(%r15)
	mvc	0(__PT_SIZE,%r11),0(%r12)	# copy pt_regs
	lg	%r12,__LC_THREAD_INFO
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	ssm	__LC_SVC_NEW_PSW	# reenable interrupts
	brasl	%r14,execve_tail
	j	sysc_return

/*
 * Program check handler routine
 */

ENTRY(pgm_check_handler)
	stpt	__LC_SYNC_ENTER_TIMER
	stmg	%r8,%r15,__LC_SAVE_AREA_SYNC
	lg	%r10,__LC_LAST_BREAK
	lg	%r12,__LC_THREAD_INFO
	larl	%r13,system_call
	lmg	%r8,%r9,__LC_PGM_OLD_PSW
	HANDLE_SIE_INTERCEPT %r14
	tmhh	%r8,0x0001		# test problem state bit
	jnz	1f			# -> fault in user space
	tmhh	%r8,0x4000		# PER bit set in old PSW ?
	jnz	0f			# -> enabled, can't be a double fault
	tm	__LC_PGM_ILC+3,0x80	# check for per exception
	jnz	pgm_svcper		# -> single stepped svc
0:	CHECK_STACK STACK_SIZE,__LC_SAVE_AREA_SYNC
	j	2f
1:	UPDATE_VTIME %r14,__LC_SYNC_ENTER_TIMER
	LAST_BREAK %r14
	lg	%r15,__LC_KERNEL_STACK
2:	aghi	%r15,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	la	%r11,STACK_FRAME_OVERHEAD(%r15)
	stmg	%r0,%r7,__PT_R0(%r11)
	mvc	__PT_R8(64,%r11),__LC_SAVE_AREA_SYNC
	stmg	%r8,%r9,__PT_PSW(%r11)
	mvc	__PT_INT_CODE(4,%r11),__LC_PGM_ILC
	mvc	__PT_INT_PARM_LONG(8,%r11),__LC_TRANS_EXC_CODE
	stg	%r10,__PT_ARGS(%r11)
	tm	__LC_PGM_ILC+3,0x80	# check for per exception
	jz	0f
	lg	%r1,__TI_task(%r12)
	tmhh	%r8,0x0001		# kernel per event ?
	jz	pgm_kprobe
	oi	__TI_flags+7(%r12),_TIF_PER_TRAP
	mvc	__THREAD_per_address(8,%r1),__LC_PER_ADDRESS
	mvc	__THREAD_per_cause(2,%r1),__LC_PER_CAUSE
	mvc	__THREAD_per_paid(1,%r1),__LC_PER_PAID
0:	REENABLE_IRQS
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	larl	%r1,pgm_check_table
	llgh	%r10,__PT_INT_CODE+2(%r11)
	nill	%r10,0x007f
	sll	%r10,3
	je	sysc_return
	lg	%r1,0(%r10,%r1)		# load address of handler routine
	lgr	%r2,%r11		# pass pointer to pt_regs
	basr	%r14,%r1		# branch to interrupt-handler
	j	sysc_return

#
# PER event in supervisor state, must be kprobes
#
pgm_kprobe:
	REENABLE_IRQS
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	lgr	%r2,%r11		# pass pointer to pt_regs
	brasl	%r14,do_per_trap
	j	sysc_return

#
# single stepped system call
#
pgm_svcper:
	oi	__TI_flags+7(%r12),_TIF_PER_TRAP
	mvc	__LC_RETURN_PSW(8),__LC_SVC_NEW_PSW
	larl	%r14,sysc_per
	stg	%r14,__LC_RETURN_PSW+8
	lpswe	__LC_RETURN_PSW		# branch to sysc_per and enable irqs

/*
 * IO interrupt handler routine
 */
ENTRY(io_int_handler)
	stck	__LC_INT_CLOCK
	stpt	__LC_ASYNC_ENTER_TIMER
	stmg	%r8,%r15,__LC_SAVE_AREA_ASYNC
	lg	%r10,__LC_LAST_BREAK
	lg	%r12,__LC_THREAD_INFO
	larl	%r13,system_call
	lmg	%r8,%r9,__LC_IO_OLD_PSW
	HANDLE_SIE_INTERCEPT %r14
	SWITCH_ASYNC __LC_SAVE_AREA_ASYNC,__LC_ASYNC_STACK,STACK_SHIFT
	tmhh	%r8,0x0001		# interrupting from user?
	jz	io_skip
	UPDATE_VTIME %r14,__LC_ASYNC_ENTER_TIMER
	LAST_BREAK %r14
io_skip:
	stmg	%r0,%r7,__PT_R0(%r11)
	mvc	__PT_R8(64,%r11),__LC_SAVE_AREA_ASYNC
	stmg	%r8,%r9,__PT_PSW(%r11)
	TRACE_IRQS_OFF
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	lgr	%r2,%r11		# pass pointer to pt_regs
	brasl	%r14,do_IRQ
io_return:
	LOCKDEP_SYS_EXIT
	TRACE_IRQS_ON
io_tif:
	tm	__TI_flags+7(%r12),_TIF_WORK_INT
	jnz	io_work 		# there is work to do (signals etc.)
io_restore:
	lg	%r14,__LC_VDSO_PER_CPU
	lmg	%r0,%r10,__PT_R0(%r11)
	mvc	__LC_RETURN_PSW(16),__PT_PSW(%r11)
	stpt	__LC_EXIT_TIMER
	mvc	__VDSO_ECTG_BASE(16,%r14),__LC_EXIT_TIMER
	lmg	%r11,%r15,__PT_R11(%r11)
	lpswe	__LC_RETURN_PSW
io_done:

#
# There is work todo, find out in which context we have been interrupted:
# 1) if we return to user space we can do all _TIF_WORK_INT work
# 2) if we return to kernel code and kvm is enabled check if we need to
#    modify the psw to leave SIE
# 3) if we return to kernel code and preemptive scheduling is enabled check
#    the preemption counter and if it is zero call preempt_schedule_irq
# Before any work can be done, a switch to the kernel stack is required.
#
io_work:
	tm	__PT_PSW+1(%r11),0x01	# returning to user ?
	jo	io_work_user		# yes -> do resched & signal
#ifdef CONFIG_PREEMPT
	# check for preemptive scheduling
	icm	%r0,15,__TI_precount(%r12)
	jnz	io_restore		# preemption is disabled
	tm	__TI_flags+7(%r12),_TIF_NEED_RESCHED
	jno	io_restore
	# switch to kernel stack
	lg	%r1,__PT_R15(%r11)
	aghi	%r1,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	mvc	STACK_FRAME_OVERHEAD(__PT_SIZE,%r1),0(%r11)
	xc	__SF_BACKCHAIN(8,%r1),__SF_BACKCHAIN(%r1)
	la	%r11,STACK_FRAME_OVERHEAD(%r1)
	lgr	%r15,%r1
	# TRACE_IRQS_ON already done at io_return, call
	# TRACE_IRQS_OFF to keep things symmetrical
	TRACE_IRQS_OFF
	brasl	%r14,preempt_schedule_irq
	j	io_return
#else
	j	io_restore
#endif

#
# Need to do work before returning to userspace, switch to kernel stack
#
io_work_user:
	lg	%r1,__LC_KERNEL_STACK
	aghi	%r1,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	mvc	STACK_FRAME_OVERHEAD(__PT_SIZE,%r1),0(%r11)
	xc	__SF_BACKCHAIN(8,%r1),__SF_BACKCHAIN(%r1)
	la	%r11,STACK_FRAME_OVERHEAD(%r1)
	lgr	%r15,%r1

#
# One of the work bits is on. Find out which one.
# Checked are: _TIF_SIGPENDING, _TIF_NOTIFY_RESUME, _TIF_NEED_RESCHED
#	       and _TIF_MCCK_PENDING
#
io_work_tif:
	tm	__TI_flags+7(%r12),_TIF_MCCK_PENDING
	jo	io_mcck_pending
	tm	__TI_flags+7(%r12),_TIF_NEED_RESCHED
	jo	io_reschedule
	tm	__TI_flags+7(%r12),_TIF_SIGPENDING
	jo	io_sigpending
	tm	__TI_flags+7(%r12),_TIF_NOTIFY_RESUME
	jo	io_notify_resume
	j	io_return		# beware of critical section cleanup

#
# _TIF_MCCK_PENDING is set, call handler
#
io_mcck_pending:
	# TRACE_IRQS_ON already done at io_return
	brasl	%r14,s390_handle_mcck	# TIF bit will be cleared by handler
	TRACE_IRQS_OFF
	j	io_return

#
# _TIF_NEED_RESCHED is set, call schedule
#
io_reschedule:
	# TRACE_IRQS_ON already done at io_return
	ssm	__LC_SVC_NEW_PSW	# reenable interrupts
	brasl	%r14,schedule		# call scheduler
	ssm	__LC_PGM_NEW_PSW	# disable I/O and ext. interrupts
	TRACE_IRQS_OFF
	j	io_return

#
# _TIF_SIGPENDING or is set, call do_signal
#
io_sigpending:
	# TRACE_IRQS_ON already done at io_return
	ssm	__LC_SVC_NEW_PSW	# reenable interrupts
	lgr	%r2,%r11		# pass pointer to pt_regs
	brasl	%r14,do_signal
	ssm	__LC_PGM_NEW_PSW	# disable I/O and ext. interrupts
	TRACE_IRQS_OFF
	j	io_return

#
# _TIF_NOTIFY_RESUME or is set, call do_notify_resume
#
io_notify_resume:
	# TRACE_IRQS_ON already done at io_return
	ssm	__LC_SVC_NEW_PSW	# reenable interrupts
	lgr	%r2,%r11		# pass pointer to pt_regs
	brasl	%r14,do_notify_resume
	ssm	__LC_PGM_NEW_PSW	# disable I/O and ext. interrupts
	TRACE_IRQS_OFF
	j	io_return

/*
 * External interrupt handler routine
 */
ENTRY(ext_int_handler)
	stck	__LC_INT_CLOCK
	stpt	__LC_ASYNC_ENTER_TIMER
	stmg	%r8,%r15,__LC_SAVE_AREA_ASYNC
	lg	%r10,__LC_LAST_BREAK
	lg	%r12,__LC_THREAD_INFO
	larl	%r13,system_call
	lmg	%r8,%r9,__LC_EXT_OLD_PSW
	HANDLE_SIE_INTERCEPT %r14
	SWITCH_ASYNC __LC_SAVE_AREA_ASYNC,__LC_ASYNC_STACK,STACK_SHIFT
	tmhh	%r8,0x0001		# interrupting from user ?
	jz	ext_skip
	UPDATE_VTIME %r14,__LC_ASYNC_ENTER_TIMER
	LAST_BREAK %r14
ext_skip:
	stmg	%r0,%r7,__PT_R0(%r11)
	mvc	__PT_R8(64,%r11),__LC_SAVE_AREA_ASYNC
	stmg	%r8,%r9,__PT_PSW(%r11)
	TRACE_IRQS_OFF
	lghi	%r1,4096
	lgr	%r2,%r11		# pass pointer to pt_regs
	llgf	%r3,__LC_EXT_CPU_ADDR	# get cpu address + interruption code
	llgf	%r4,__LC_EXT_PARAMS	# get external parameter
	lg	%r5,__LC_EXT_PARAMS2-4096(%r1)	# get 64 bit external parameter
	brasl	%r14,do_extint
	j	io_return

/*
 * Load idle PSW. The second "half" of this function is in cleanup_idle.
 */
ENTRY(psw_idle)
	stg	%r4,__SF_EMPTY(%r15)
	larl	%r1,psw_idle_lpsw+4
	stg	%r1,__SF_EMPTY+8(%r15)
	larl	%r1,.Lvtimer_max
	stck	__IDLE_ENTER(%r2)
	ltr	%r5,%r5
	stpt	__VQ_IDLE_ENTER(%r3)
	jz	psw_idle_lpsw
	spt	0(%r1)
psw_idle_lpsw:
	lpswe	__SF_EMPTY(%r15)
	br	%r14
psw_idle_end:

__critical_end:

/*
 * Machine check handler routines
 */
ENTRY(mcck_int_handler)
	stck	__LC_MCCK_CLOCK
	la	%r1,4095		# revalidate r1
	spt	__LC_CPU_TIMER_SAVE_AREA-4095(%r1)	# revalidate cpu timer
	lmg	%r0,%r15,__LC_GPREGS_SAVE_AREA-4095(%r1)# revalidate gprs
	lg	%r10,__LC_LAST_BREAK
	lg	%r12,__LC_THREAD_INFO
	larl	%r13,system_call
	lmg	%r8,%r9,__LC_MCK_OLD_PSW
	HANDLE_SIE_INTERCEPT %r14
	tm	__LC_MCCK_CODE,0x80	# system damage?
	jo	mcck_panic		# yes -> rest of mcck code invalid
	lghi	%r14,__LC_CPU_TIMER_SAVE_AREA
	mvc	__LC_MCCK_ENTER_TIMER(8),0(%r14)
	tm	__LC_MCCK_CODE+5,0x02	# stored cpu timer value valid?
	jo	3f
	la	%r14,__LC_SYNC_ENTER_TIMER
	clc	0(8,%r14),__LC_ASYNC_ENTER_TIMER
	jl	0f
	la	%r14,__LC_ASYNC_ENTER_TIMER
0:	clc	0(8,%r14),__LC_EXIT_TIMER
	jl	1f
	la	%r14,__LC_EXIT_TIMER
1:	clc	0(8,%r14),__LC_LAST_UPDATE_TIMER
	jl	2f
	la	%r14,__LC_LAST_UPDATE_TIMER
2:	spt	0(%r14)
	mvc	__LC_MCCK_ENTER_TIMER(8),0(%r14)
3:	tm	__LC_MCCK_CODE+2,0x09	# mwp + ia of old psw valid?
	jno	mcck_panic		# no -> skip cleanup critical
	SWITCH_ASYNC __LC_GPREGS_SAVE_AREA+64,__LC_PANIC_STACK,PAGE_SHIFT
	tm	%r8,0x0001		# interrupting from user ?
	jz	mcck_skip
	UPDATE_VTIME %r14,__LC_MCCK_ENTER_TIMER
	LAST_BREAK %r14
mcck_skip:
	lghi	%r14,__LC_GPREGS_SAVE_AREA
	mvc	__PT_R0(128,%r11),0(%r14)
	stmg	%r8,%r9,__PT_PSW(%r11)
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	lgr	%r2,%r11		# pass pointer to pt_regs
	brasl	%r14,s390_do_machine_check
	tm	__PT_PSW+1(%r11),0x01	# returning to user ?
	jno	mcck_return
	lg	%r1,__LC_KERNEL_STACK	# switch to kernel stack
	aghi	%r1,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	mvc	STACK_FRAME_OVERHEAD(__PT_SIZE,%r1),0(%r11)
	xc	__SF_BACKCHAIN(8,%r1),__SF_BACKCHAIN(%r1)
	la	%r11,STACK_FRAME_OVERHEAD(%r1)
	lgr	%r15,%r1
	ssm	__LC_PGM_NEW_PSW	# turn dat on, keep irqs off
	tm	__TI_flags+7(%r12),_TIF_MCCK_PENDING
	jno	mcck_return
	TRACE_IRQS_OFF
	brasl	%r14,s390_handle_mcck
	TRACE_IRQS_ON
mcck_return:
	lg	%r14,__LC_VDSO_PER_CPU
	lmg	%r0,%r10,__PT_R0(%r11)
	mvc	__LC_RETURN_MCCK_PSW(16),__PT_PSW(%r11) # move return PSW
	tm	__LC_RETURN_MCCK_PSW+1,0x01 # returning to user ?
	jno	0f
	stpt	__LC_EXIT_TIMER
	mvc	__VDSO_ECTG_BASE(16,%r14),__LC_EXIT_TIMER
0:	lmg	%r11,%r15,__PT_R11(%r11)
	lpswe	__LC_RETURN_MCCK_PSW

mcck_panic:
	lg	%r14,__LC_PANIC_STACK
	slgr	%r14,%r15
	srag	%r14,%r14,PAGE_SHIFT
	jz	0f
	lg	%r15,__LC_PANIC_STACK
0:	aghi	%r15,-(STACK_FRAME_OVERHEAD + __PT_SIZE)
	j	mcck_skip

#
# PSW restart interrupt handler
#
ENTRY(restart_int_handler)
	stg	%r15,__LC_SAVE_AREA_RESTART
	lg	%r15,__LC_RESTART_STACK
	aghi	%r15,-__PT_SIZE			# create pt_regs on stack
	xc	0(__PT_SIZE,%r15),0(%r15)
	stmg	%r0,%r14,__PT_R0(%r15)
	mvc	__PT_R15(8,%r15),__LC_SAVE_AREA_RESTART
	mvc	__PT_PSW(16,%r15),__LC_RST_OLD_PSW # store restart old psw
	aghi	%r15,-STACK_FRAME_OVERHEAD	# create stack frame on stack
	xc	0(STACK_FRAME_OVERHEAD,%r15),0(%r15)
	lmg	%r1,%r3,__LC_RESTART_FN		# load fn, parm & source cpu
	ltgr	%r3,%r3				# test source cpu address
	jm	1f				# negative -> skip source stop
0:	sigp	%r4,%r3,1			# sigp sense to source cpu
	brc	10,0b				# wait for status stored
1:	basr	%r14,%r1			# call function
	stap	__SF_EMPTY(%r15)		# store cpu address
	llgh	%r3,__SF_EMPTY(%r15)
2:	sigp	%r4,%r3,5			# sigp stop to current cpu
	brc	2,2b
3:	j	3b

	.section .kprobes.text, "ax"

#ifdef CONFIG_CHECK_STACK
/*
 * The synchronous or the asynchronous stack overflowed. We are dead.
 * No need to properly save the registers, we are going to panic anyway.
 * Setup a pt_regs so that show_trace can provide a good call trace.
 */
stack_overflow:
	lg	%r11,__LC_PANIC_STACK	# change to panic stack
	aghi	%r11,-__PT_SIZE		# create pt_regs
	stmg	%r0,%r7,__PT_R0(%r11)
	stmg	%r8,%r9,__PT_PSW(%r11)
	mvc	__PT_R8(64,%r11),0(%r14)
	stg	%r10,__PT_ORIG_GPR2(%r11) # store last break to orig_gpr2
	lgr	%r15,%r11
	aghi	%r15,-STACK_FRAME_OVERHEAD
	xc	__SF_BACKCHAIN(8,%r15),__SF_BACKCHAIN(%r15)
	lgr	%r2,%r11		# pass pointer to pt_regs
	jg	kernel_stack_overflow
#endif

	.align	8
cleanup_table:
	.quad	system_call
	.quad	sysc_do_svc
	.quad	sysc_tif
	.quad	sysc_restore
	.quad	sysc_done
	.quad	io_tif
	.quad	io_restore
	.quad	io_done
	.quad	psw_idle
	.quad	psw_idle_end

cleanup_critical:
	clg	%r9,BASED(cleanup_table)	# system_call
	jl	0f
	clg	%r9,BASED(cleanup_table+8)	# sysc_do_svc
	jl	cleanup_system_call
	clg	%r9,BASED(cleanup_table+16)	# sysc_tif
	jl	0f
	clg	%r9,BASED(cleanup_table+24)	# sysc_restore
	jl	cleanup_sysc_tif
	clg	%r9,BASED(cleanup_table+32)	# sysc_done
	jl	cleanup_sysc_restore
	clg	%r9,BASED(cleanup_table+40)	# io_tif
	jl	0f
	clg	%r9,BASED(cleanup_table+48)	# io_restore
	jl	cleanup_io_tif
	clg	%r9,BASED(cleanup_table+56)	# io_done
	jl	cleanup_io_restore
	clg	%r9,BASED(cleanup_table+64)	# psw_idle
	jl	0f
	clg	%r9,BASED(cleanup_table+72)	# psw_idle_end
	jl	cleanup_idle
0:	br	%r14


cleanup_system_call:
	# check if stpt has been executed
	clg	%r9,BASED(cleanup_system_call_insn)
	jh	0f
	mvc	__LC_SYNC_ENTER_TIMER(8),__LC_ASYNC_ENTER_TIMER
	cghi	%r11,__LC_SAVE_AREA_ASYNC
	je	0f
	mvc	__LC_SYNC_ENTER_TIMER(8),__LC_MCCK_ENTER_TIMER
0:	# check if stmg has been executed
	clg	%r9,BASED(cleanup_system_call_insn+8)
	jh	0f
	mvc	__LC_SAVE_AREA_SYNC(64),0(%r11)
0:	# check if base register setup + TIF bit load has been done
	clg	%r9,BASED(cleanup_system_call_insn+16)
	jhe	0f
	# set up saved registers r10 and r12
	stg	%r10,16(%r11)		# r10 last break
	stg	%r12,32(%r11)		# r12 thread-info pointer
0:	# check if the user time update has been done
	clg	%r9,BASED(cleanup_system_call_insn+24)
	jh	0f
	lg	%r15,__LC_EXIT_TIMER
	slg	%r15,__LC_SYNC_ENTER_TIMER
	alg	%r15,__LC_USER_TIMER
	stg	%r15,__LC_USER_TIMER
0:	# check if the system time update has been done
	clg	%r9,BASED(cleanup_system_call_insn+32)
	jh	0f
	lg	%r15,__LC_LAST_UPDATE_TIMER
	slg	%r15,__LC_EXIT_TIMER
	alg	%r15,__LC_SYSTEM_TIMER
	stg	%r15,__LC_SYSTEM_TIMER
0:	# update accounting time stamp
	mvc	__LC_LAST_UPDATE_TIMER(8),__LC_SYNC_ENTER_TIMER
	# do LAST_BREAK
	lg	%r9,16(%r11)
	srag	%r9,%r9,23
	jz	0f
	mvc	__TI_last_break(8,%r12),16(%r11)
0:	# set up saved register r11
	lg	%r15,__LC_KERNEL_STACK
	aghi	%r15,-__PT_SIZE
	stg	%r15,24(%r11)		# r11 pt_regs pointer
	# fill pt_regs
	mvc	__PT_R8(64,%r15),__LC_SAVE_AREA_SYNC
	stmg	%r0,%r7,__PT_R0(%r15)
	mvc	__PT_PSW(16,%r15),__LC_SVC_OLD_PSW
	mvc	__PT_INT_CODE(4,%r15),__LC_SVC_ILC
	# setup saved register r15
	aghi	%r15,-STACK_FRAME_OVERHEAD
	stg	%r15,56(%r11)		# r15 stack pointer
	# set new psw address and exit
	larl	%r9,sysc_do_svc
	br	%r14
cleanup_system_call_insn:
	.quad	system_call
	.quad	sysc_stmg
	.quad	sysc_per
	.quad	sysc_vtime+18
	.quad	sysc_vtime+42

cleanup_sysc_tif:
	larl	%r9,sysc_tif
	br	%r14

cleanup_sysc_restore:
	clg	%r9,BASED(cleanup_sysc_restore_insn)
	je	0f
	lg	%r9,24(%r11)		# get saved pointer to pt_regs
	mvc	__LC_RETURN_PSW(16),__PT_PSW(%r9)
	mvc	0(64,%r11),__PT_R8(%r9)
	lmg	%r0,%r7,__PT_R0(%r9)
0:	lmg	%r8,%r9,__LC_RETURN_PSW
	br	%r14
cleanup_sysc_restore_insn:
	.quad	sysc_done - 4

cleanup_io_tif:
	larl	%r9,io_tif
	br	%r14

cleanup_io_restore:
	clg	%r9,BASED(cleanup_io_restore_insn)
	je	0f
	lg	%r9,24(%r11)		# get saved r11 pointer to pt_regs
	mvc	__LC_RETURN_PSW(16),__PT_PSW(%r9)
	mvc	0(64,%r11),__PT_R8(%r9)
	lmg	%r0,%r7,__PT_R0(%r9)
0:	lmg	%r8,%r9,__LC_RETURN_PSW
	br	%r14
cleanup_io_restore_insn:
	.quad	io_done - 4

cleanup_idle:
	# copy interrupt clock & cpu timer
	mvc	__IDLE_EXIT(8,%r2),__LC_INT_CLOCK
	mvc	__VQ_IDLE_EXIT(8,%r3),__LC_ASYNC_ENTER_TIMER
	cghi	%r11,__LC_SAVE_AREA_ASYNC
	je	0f
	mvc	__IDLE_EXIT(8,%r2),__LC_MCCK_CLOCK
	mvc	__VQ_IDLE_EXIT(8,%r3),__LC_MCCK_ENTER_TIMER
0:	# check if stck & stpt have been executed
	clg	%r9,BASED(cleanup_idle_insn)
	jhe	1f
	mvc	__IDLE_ENTER(8,%r2),__IDLE_EXIT(%r2)
	mvc	__VQ_IDLE_ENTER(8,%r3),__VQ_IDLE_EXIT(%r3)
	j	2f
1:	# check if the cpu timer has been reprogrammed
	ltr	%r5,%r5
	jz	2f
	spt	__VQ_IDLE_ENTER(%r3)
2:	# account system time going idle
	lg	%r9,__LC_STEAL_TIMER
	alg	%r9,__IDLE_ENTER(%r2)
	slg	%r9,__LC_LAST_UPDATE_CLOCK
	stg	%r9,__LC_STEAL_TIMER
	mvc	__LC_LAST_UPDATE_CLOCK(8),__IDLE_EXIT(%r2)
	lg	%r9,__LC_SYSTEM_TIMER
	alg	%r9,__LC_LAST_UPDATE_TIMER
	slg	%r9,__VQ_IDLE_ENTER(%r3)
	stg	%r9,__LC_SYSTEM_TIMER
	mvc	__LC_LAST_UPDATE_TIMER(8),__VQ_IDLE_EXIT(%r3)
	# prepare return psw
	nihh	%r8,0xfffd		# clear wait state bit
	lg	%r9,48(%r11)		# return from psw_idle
	br	%r14
cleanup_idle_insn:
	.quad	psw_idle_lpsw

/*
 * Integer constants
 */
	.align	8
.Lcritical_start:
	.quad	__critical_start
.Lcritical_length:
	.quad	__critical_end - __critical_start
.Lvtimer_max:
	.quad	0x7fffffffffffffff


#if defined(CONFIG_KVM) || defined(CONFIG_KVM_MODULE)
/*
 * sie64a calling convention:
 * %r2 pointer to sie control block
 * %r3 guest register save area
 */
ENTRY(sie64a)
	stmg	%r6,%r14,__SF_GPRS(%r15)	# save kernel registers
	stg	%r2,__SF_EMPTY(%r15)		# save control block pointer
	stg	%r3,__SF_EMPTY+8(%r15)		# save guest register save area
	xc	__SF_EMPTY+16(8,%r15),__SF_EMPTY+16(%r15) # host id == 0
	lmg	%r0,%r13,0(%r3)			# load guest gprs 0-13
	lg	%r14,__LC_THREAD_INFO		# pointer thread_info struct
	oi	__TI_flags+6(%r14),_TIF_SIE>>8
sie_loop:
	lg	%r14,__LC_THREAD_INFO		# pointer thread_info struct
	tm	__TI_flags+7(%r14),_TIF_EXIT_SIE
	jnz	sie_exit
	lg	%r14,__LC_GMAP			# get gmap pointer
	ltgr	%r14,%r14
	jz	sie_gmap
	lctlg	%c1,%c1,__GMAP_ASCE(%r14)	# load primary asce
sie_gmap:
	lg	%r14,__SF_EMPTY(%r15)		# get control block pointer
	SPP	__SF_EMPTY(%r15)		# set guest id
	sie	0(%r14)
sie_done:
	SPP	__SF_EMPTY+16(%r15)		# set host id
	lg	%r14,__LC_THREAD_INFO		# pointer thread_info struct
sie_exit:
	lctlg	%c1,%c1,__LC_USER_ASCE		# load primary asce
	ni	__TI_flags+6(%r14),255-(_TIF_SIE>>8)
	lg	%r14,__SF_EMPTY+8(%r15)		# load guest register save area
	stmg	%r0,%r13,0(%r14)		# save guest gprs 0-13
	lmg	%r6,%r14,__SF_GPRS(%r15)	# restore kernel registers
	lghi	%r2,0
	br	%r14
sie_fault:
	lctlg	%c1,%c1,__LC_USER_ASCE		# load primary asce
	lg	%r14,__LC_THREAD_INFO		# pointer thread_info struct
	ni	__TI_flags+6(%r14),255-(_TIF_SIE>>8)
	lg	%r14,__SF_EMPTY+8(%r15)		# load guest register save area
	stmg	%r0,%r13,0(%r14)		# save guest gprs 0-13
	lmg	%r6,%r14,__SF_GPRS(%r15)	# restore kernel registers
	lghi	%r2,-EFAULT
	br	%r14

	.align	8
.Lsie_loop:
	.quad	sie_loop
.Lsie_length:
	.quad	sie_done - sie_loop
.Lhost_id:
	.quad	0

	.section __ex_table,"a"
	.quad	sie_loop,sie_fault
	.previous
#endif

		.section .rodata, "a"
#define SYSCALL(esa,esame,emu)	.long esame
	.globl	sys_call_table
sys_call_table:
#include "syscalls.S"
#undef SYSCALL

#ifdef CONFIG_COMPAT

#define SYSCALL(esa,esame,emu)	.long emu
sys_call_table_emu:
#include "syscalls.S"
#undef SYSCALL
#endif
