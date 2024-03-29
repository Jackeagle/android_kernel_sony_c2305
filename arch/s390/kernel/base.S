/*
 *  arch/s390/kernel/base.S
 *
 *    Copyright IBM Corp. 2006,2007
 *    Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 */

#include <linux/linkage.h>
#include <asm/asm-offsets.h>
#include <asm/ptrace.h>

#ifdef CONFIG_64BIT

ENTRY(s390_base_mcck_handler)
	basr	%r13,0
0:	lg	%r15,__LC_PANIC_STACK	# load panic stack
	aghi	%r15,-STACK_FRAME_OVERHEAD
	larl	%r1,s390_base_mcck_handler_fn
	lg	%r1,0(%r1)
	ltgr	%r1,%r1
	jz	1f
	basr	%r14,%r1
1:	la	%r1,4095
	lmg	%r0,%r15,__LC_GPREGS_SAVE_AREA-4095(%r1)
	lpswe	__LC_MCK_OLD_PSW

	.section .bss
	.align 8
	.globl	s390_base_mcck_handler_fn
s390_base_mcck_handler_fn:
	.quad	0
	.previous

ENTRY(s390_base_ext_handler)
	stmg	%r0,%r15,__LC_SAVE_AREA_ASYNC
	basr	%r13,0
0:	aghi	%r15,-STACK_FRAME_OVERHEAD
	larl	%r1,s390_base_ext_handler_fn
	lg	%r1,0(%r1)
	ltgr	%r1,%r1
	jz	1f
	basr	%r14,%r1
1:	lmg	%r0,%r15,__LC_SAVE_AREA_ASYNC
	ni	__LC_EXT_OLD_PSW+1,0xfd	# clear wait state bit
	lpswe	__LC_EXT_OLD_PSW

	.section .bss
	.align 8
	.globl s390_base_ext_handler_fn
s390_base_ext_handler_fn:
	.quad	0
	.previous

ENTRY(s390_base_pgm_handler)
	stmg	%r0,%r15,__LC_SAVE_AREA_SYNC
	basr	%r13,0
0:	aghi	%r15,-STACK_FRAME_OVERHEAD
	larl	%r1,s390_base_pgm_handler_fn
	lg	%r1,0(%r1)
	ltgr	%r1,%r1
	jz	1f
	basr	%r14,%r1
	lmg	%r0,%r15,__LC_SAVE_AREA_SYNC
	lpswe	__LC_PGM_OLD_PSW
1:	lpswe	disabled_wait_psw-0b(%r13)

	.align	8
disabled_wait_psw:
	.quad	0x0002000180000000,0x0000000000000000 + s390_base_pgm_handler

	.section .bss
	.align 8
	.globl s390_base_pgm_handler_fn
s390_base_pgm_handler_fn:
	.quad	0
	.previous

#
# Calls diag 308 subcode 1 and continues execution
#
# The following conditions must be ensured before calling this function:
# * Prefix register = 0
# * Lowcore protection is disabled
#
ENTRY(diag308_reset)
	larl	%r4,.Lctlregs		# Save control registers
	stctg	%c0,%c15,0(%r4)
	larl	%r4,.Lfpctl		# Floating point control register
	stfpc	0(%r4)
	larl	%r4,.Lrestart_psw	# Setup restart PSW at absolute 0
	lghi	%r3,0
	lg	%r4,0(%r4)		# Save PSW
	sturg	%r4,%r3			# Use sturg, because of large pages
	lghi	%r1,1
	diag	%r1,%r1,0x308
.Lrestart_part2:
	lhi	%r0,0			# Load r0 with zero
	lhi	%r1,2			# Use mode 2 = ESAME (dump)
	sigp	%r1,%r0,0x12		# Switch to ESAME mode
	sam64				# Switch to 64 bit addressing mode
	larl	%r4,.Lctlregs		# Restore control registers
	lctlg	%c0,%c15,0(%r4)
	larl	%r4,.Lfpctl		# Restore floating point ctl register
	lfpc	0(%r4)
	br	%r14
.align 16
.Lrestart_psw:
	.long	0x00080000,0x80000000 + .Lrestart_part2

	.section .bss
.align 8
.Lctlregs:
	.rept	16
	.quad	0
	.endr
.Lfpctl:
	.long	0
	.previous

#else /* CONFIG_64BIT */

ENTRY(s390_base_mcck_handler)
	basr	%r13,0
0:	l	%r15,__LC_PANIC_STACK	# load panic stack
	ahi	%r15,-STACK_FRAME_OVERHEAD
	l	%r1,2f-0b(%r13)
	l	%r1,0(%r1)
	ltr	%r1,%r1
	jz	1f
	basr	%r14,%r1
1:	lm	%r0,%r15,__LC_GPREGS_SAVE_AREA
	lpsw	__LC_MCK_OLD_PSW

2:	.long	s390_base_mcck_handler_fn

	.section .bss
	.align 4
	.globl	s390_base_mcck_handler_fn
s390_base_mcck_handler_fn:
	.long	0
	.previous

ENTRY(s390_base_ext_handler)
	stm	%r0,%r15,__LC_SAVE_AREA_ASYNC
	basr	%r13,0
0:	ahi	%r15,-STACK_FRAME_OVERHEAD
	l	%r1,2f-0b(%r13)
	l	%r1,0(%r1)
	ltr	%r1,%r1
	jz	1f
	basr	%r14,%r1
1:	lm	%r0,%r15,__LC_SAVE_AREA_ASYNC
	ni	__LC_EXT_OLD_PSW+1,0xfd	# clear wait state bit
	lpsw	__LC_EXT_OLD_PSW

2:	.long	s390_base_ext_handler_fn

	.section .bss
	.align 4
	.globl	s390_base_ext_handler_fn
s390_base_ext_handler_fn:
	.long	0
	.previous

ENTRY(s390_base_pgm_handler)
	stm	%r0,%r15,__LC_SAVE_AREA_SYNC
	basr	%r13,0
0:	ahi	%r15,-STACK_FRAME_OVERHEAD
	l	%r1,2f-0b(%r13)
	l	%r1,0(%r1)
	ltr	%r1,%r1
	jz	1f
	basr	%r14,%r1
	lm	%r0,%r15,__LC_SAVE_AREA_SYNC
	lpsw	__LC_PGM_OLD_PSW

1:	lpsw	disabled_wait_psw-0b(%r13)

2:	.long	s390_base_pgm_handler_fn

disabled_wait_psw:
	.align	8
	.long	0x000a0000,0x00000000 + s390_base_pgm_handler

	.section .bss
	.align 4
	.globl	s390_base_pgm_handler_fn
s390_base_pgm_handler_fn:
	.long	0
	.previous

#endif /* CONFIG_64BIT */
