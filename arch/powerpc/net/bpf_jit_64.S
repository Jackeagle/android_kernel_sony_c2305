/* bpf_jit.S: Packet/header access helper functions
 * for PPC64 BPF compiler.
 *
 * Copyright 2011 Matt Evans <matt@ozlabs.org>, IBM Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 */

#include <asm/ppc_asm.h>
#include "bpf_jit.h"

/*
 * All of these routines are called directly from generated code,
 * whose register usage is:
 *
 * r3		skb
 * r4,r5	A,X
 * r6		*** address parameter to helper ***
 * r7-r10	scratch
 * r14		skb->data
 * r15		skb headlen
 * r16-31	M[]
 */

/*
 * To consider: These helpers are so small it could be better to just
 * generate them inline.  Inline code can do the simple headlen check
 * then branch directly to slow_path_XXX if required.  (In fact, could
 * load a spare GPR with the address of slow_path_generic and pass size
 * as an argument, making the call site a mtlr, li and bllr.)
 */
	.globl	sk_load_word
sk_load_word:
	cmpdi	r_addr, 0
	blt	bpf_slow_path_word_neg
	.globl	sk_load_word_positive_offset
sk_load_word_positive_offset:
	/* Are we accessing past headlen? */
	subi	r_scratch1, r_HL, 4
	cmpd	r_scratch1, r_addr
	blt	bpf_slow_path_word
	/* Nope, just hitting the header.  cr0 here is eq or gt! */
	lwzx	r_A, r_D, r_addr
	/* When big endian we don't need to byteswap. */
	blr	/* Return success, cr0 != LT */

	.globl	sk_load_half
sk_load_half:
	cmpdi	r_addr, 0
	blt	bpf_slow_path_half_neg
	.globl	sk_load_half_positive_offset
sk_load_half_positive_offset:
	subi	r_scratch1, r_HL, 2
	cmpd	r_scratch1, r_addr
	blt	bpf_slow_path_half
	lhzx	r_A, r_D, r_addr
	blr

	.globl	sk_load_byte
sk_load_byte:
	cmpdi	r_addr, 0
	blt	bpf_slow_path_byte_neg
	.globl	sk_load_byte_positive_offset
sk_load_byte_positive_offset:
	cmpd	r_HL, r_addr
	ble	bpf_slow_path_byte
	lbzx	r_A, r_D, r_addr
	blr

/*
 * BPF_S_LDX_B_MSH: ldxb  4*([offset]&0xf)
 * r_addr is the offset value
 */
	.globl sk_load_byte_msh
sk_load_byte_msh:
	cmpdi	r_addr, 0
	blt	bpf_slow_path_byte_msh_neg
	.globl sk_load_byte_msh_positive_offset
sk_load_byte_msh_positive_offset:
	cmpd	r_HL, r_addr
	ble	bpf_slow_path_byte_msh
	lbzx	r_X, r_D, r_addr
	rlwinm	r_X, r_X, 2, 32-4-2, 31-2
	blr

/* Call out to skb_copy_bits:
 * We'll need to back up our volatile regs first; we have
 * local variable space at r1+(BPF_PPC_STACK_BASIC).
 * Allocate a new stack frame here to remain ABI-compliant in
 * stashing LR.
 */
#define bpf_slow_path_common(SIZE)				\
	mflr	r0;						\
	std	r0, 16(r1);					\
	/* R3 goes in parameter space of caller's frame */	\
	std	r_skb, (BPF_PPC_STACKFRAME+48)(r1);		\
	std	r_A, (BPF_PPC_STACK_BASIC+(0*8))(r1);		\
	std	r_X, (BPF_PPC_STACK_BASIC+(1*8))(r1);		\
	addi	r5, r1, BPF_PPC_STACK_BASIC+(2*8);		\
	stdu	r1, -BPF_PPC_SLOWPATH_FRAME(r1);		\
	/* R3 = r_skb, as passed */				\
	mr	r4, r_addr;					\
	li	r6, SIZE;					\
	bl	skb_copy_bits;					\
	/* R3 = 0 on success */					\
	addi	r1, r1, BPF_PPC_SLOWPATH_FRAME;			\
	ld	r0, 16(r1);					\
	ld	r_A, (BPF_PPC_STACK_BASIC+(0*8))(r1);		\
	ld	r_X, (BPF_PPC_STACK_BASIC+(1*8))(r1);		\
	mtlr	r0;						\
	cmpdi	r3, 0;						\
	blt	bpf_error;	/* cr0 = LT */			\
	ld	r_skb, (BPF_PPC_STACKFRAME+48)(r1);		\
	/* Great success! */

bpf_slow_path_word:
	bpf_slow_path_common(4)
	/* Data value is on stack, and cr0 != LT */
	lwz	r_A, BPF_PPC_STACK_BASIC+(2*8)(r1)
	blr

bpf_slow_path_half:
	bpf_slow_path_common(2)
	lhz	r_A, BPF_PPC_STACK_BASIC+(2*8)(r1)
	blr

bpf_slow_path_byte:
	bpf_slow_path_common(1)
	lbz	r_A, BPF_PPC_STACK_BASIC+(2*8)(r1)
	blr

bpf_slow_path_byte_msh:
	bpf_slow_path_common(1)
	lbz	r_X, BPF_PPC_STACK_BASIC+(2*8)(r1)
	rlwinm	r_X, r_X, 2, 32-4-2, 31-2
	blr

/* Call out to bpf_internal_load_pointer_neg_helper:
 * We'll need to back up our volatile regs first; we have
 * local variable space at r1+(BPF_PPC_STACK_BASIC).
 * Allocate a new stack frame here to remain ABI-compliant in
 * stashing LR.
 */
#define sk_negative_common(SIZE)				\
	mflr	r0;						\
	std	r0, 16(r1);					\
	/* R3 goes in parameter space of caller's frame */	\
	std	r_skb, (BPF_PPC_STACKFRAME+48)(r1);		\
	std	r_A, (BPF_PPC_STACK_BASIC+(0*8))(r1);		\
	std	r_X, (BPF_PPC_STACK_BASIC+(1*8))(r1);		\
	stdu	r1, -BPF_PPC_SLOWPATH_FRAME(r1);		\
	/* R3 = r_skb, as passed */				\
	mr	r4, r_addr;					\
	li	r5, SIZE;					\
	bl	bpf_internal_load_pointer_neg_helper;		\
	/* R3 != 0 on success */				\
	addi	r1, r1, BPF_PPC_SLOWPATH_FRAME;			\
	ld	r0, 16(r1);					\
	ld	r_A, (BPF_PPC_STACK_BASIC+(0*8))(r1);		\
	ld	r_X, (BPF_PPC_STACK_BASIC+(1*8))(r1);		\
	mtlr	r0;						\
	cmpldi	r3, 0;						\
	beq	bpf_error_slow;	/* cr0 = EQ */			\
	mr	r_addr, r3;					\
	ld	r_skb, (BPF_PPC_STACKFRAME+48)(r1);		\
	/* Great success! */

bpf_slow_path_word_neg:
	lis     r_scratch1,-32	/* SKF_LL_OFF */
	cmpd	r_addr, r_scratch1	/* addr < SKF_* */
	blt	bpf_error	/* cr0 = LT */
	.globl	sk_load_word_negative_offset
sk_load_word_negative_offset:
	sk_negative_common(4)
	lwz	r_A, 0(r_addr)
	blr

bpf_slow_path_half_neg:
	lis     r_scratch1,-32	/* SKF_LL_OFF */
	cmpd	r_addr, r_scratch1	/* addr < SKF_* */
	blt	bpf_error	/* cr0 = LT */
	.globl	sk_load_half_negative_offset
sk_load_half_negative_offset:
	sk_negative_common(2)
	lhz	r_A, 0(r_addr)
	blr

bpf_slow_path_byte_neg:
	lis     r_scratch1,-32	/* SKF_LL_OFF */
	cmpd	r_addr, r_scratch1	/* addr < SKF_* */
	blt	bpf_error	/* cr0 = LT */
	.globl	sk_load_byte_negative_offset
sk_load_byte_negative_offset:
	sk_negative_common(1)
	lbz	r_A, 0(r_addr)
	blr

bpf_slow_path_byte_msh_neg:
	lis     r_scratch1,-32	/* SKF_LL_OFF */
	cmpd	r_addr, r_scratch1	/* addr < SKF_* */
	blt	bpf_error	/* cr0 = LT */
	.globl	sk_load_byte_msh_negative_offset
sk_load_byte_msh_negative_offset:
	sk_negative_common(1)
	lbz	r_X, 0(r_addr)
	rlwinm	r_X, r_X, 2, 32-4-2, 31-2
	blr

bpf_error_slow:
	/* fabricate a cr0 = lt */
	li	r_scratch1, -1
	cmpdi	r_scratch1, 0
bpf_error:
	/* Entered with cr0 = lt */
	li	r3, 0
	/* Generated code will 'blt epilogue', returning 0. */
	blr
