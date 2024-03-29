#include <linux/linkage.h>
#include <asm/assembler.h>
#include "abort-macro.S"
/*
 * Function: v6_early_abort
 *
 * Params  : r2 = pt_regs
 *	   : r4 = aborted context pc
 *	   : r5 = aborted context psr
 *
 * Returns : r4 - r11, r13 preserved
 *
 * Purpose : obtain information about current aborted instruction.
 * Note: we read user space.  This means we might cause a data
 * abort here if the I-TLB and D-TLB aren't seeing the same
 * picture.  Unfortunately, this does happen.  We live with it.
 */
	.align	5
ENTRY(v6_early_abort)
#ifdef CONFIG_CPU_V6
	sub	r1, sp, #4			@ Get unused stack location
	strex	r0, r1, [r1]			@ Clear the exclusive monitor
#elif defined(CONFIG_CPU_32v6K)
	clrex
#endif
	mrc	p15, 0, r1, c5, c0, 0		@ get FSR
	mrc	p15, 0, r0, c6, c0, 0		@ get FAR
/*
 * Faulty SWP instruction on 1136 doesn't set bit 11 in DFSR.
 */
#ifdef CONFIG_ARM_ERRATA_326103
	ldr	ip, =0x4107b36
	mrc	p15, 0, r3, c0, c0, 0		@ get processor id
	teq	ip, r3, lsr #4			@ r0 ARM1136?
	bne	do_DataAbort
	tst	r5, #PSR_J_BIT			@ Java?
	tsteq	r5, #PSR_T_BIT			@ Thumb?
	bne	do_DataAbort
	bic	r1, r1, #1 << 11		@ clear bit 11 of FSR
	ldr	r3, [r4]			@ read aborted ARM instruction
#ifdef CONFIG_CPU_ENDIAN_BE8
	rev	r3, r3
#endif
	do_ldrd_abort tmp=ip, insn=r3
	tst	r3, #1 << 20			@ L = 0 -> write
	orreq	r1, r1, #1 << 11		@ yes.
#endif
	b	do_DataAbort
