/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Copyright SUSE Linux Products GmbH 2009
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#include <asm/ppc_asm.h>
#include <asm/kvm_asm.h>
#include <asm/reg.h>
#include <asm/page.h>
#include <asm/asm-offsets.h>
#include <asm/exception-64s.h>

#if defined(CONFIG_PPC_BOOK3S_64)

#define ULONG_SIZE 		8
#define FUNC(name) 		GLUE(.,name)

#elif defined(CONFIG_PPC_BOOK3S_32)

#define ULONG_SIZE              4
#define FUNC(name)		name

#endif /* CONFIG_PPC_BOOK3S_XX */


#define VCPU_GPR(n)		(VCPU_GPRS + (n * ULONG_SIZE))
#define VCPU_LOAD_NVGPRS(vcpu) \
	PPC_LL	r14, VCPU_GPR(r14)(vcpu); \
	PPC_LL	r15, VCPU_GPR(r15)(vcpu); \
	PPC_LL	r16, VCPU_GPR(r16)(vcpu); \
	PPC_LL	r17, VCPU_GPR(r17)(vcpu); \
	PPC_LL	r18, VCPU_GPR(r18)(vcpu); \
	PPC_LL	r19, VCPU_GPR(r19)(vcpu); \
	PPC_LL	r20, VCPU_GPR(r20)(vcpu); \
	PPC_LL	r21, VCPU_GPR(r21)(vcpu); \
	PPC_LL	r22, VCPU_GPR(r22)(vcpu); \
	PPC_LL	r23, VCPU_GPR(r23)(vcpu); \
	PPC_LL	r24, VCPU_GPR(r24)(vcpu); \
	PPC_LL	r25, VCPU_GPR(r25)(vcpu); \
	PPC_LL	r26, VCPU_GPR(r26)(vcpu); \
	PPC_LL	r27, VCPU_GPR(r27)(vcpu); \
	PPC_LL	r28, VCPU_GPR(r28)(vcpu); \
	PPC_LL	r29, VCPU_GPR(r29)(vcpu); \
	PPC_LL	r30, VCPU_GPR(r30)(vcpu); \
	PPC_LL	r31, VCPU_GPR(r31)(vcpu); \

/*****************************************************************************
 *                                                                           *
 *     Guest entry / exit code that is in kernel module memory (highmem)     *
 *                                                                           *
 ****************************************************************************/

/* Registers:
 *  r3: kvm_run pointer
 *  r4: vcpu pointer
 */
_GLOBAL(__kvmppc_vcpu_run)

kvm_start_entry:
	/* Write correct stack frame */
	mflr	r0
	PPC_STL	r0,PPC_LR_STKOFF(r1)

	/* Save host state to the stack */
	PPC_STLU r1, -SWITCH_FRAME_SIZE(r1)

	/* Save r3 (kvm_run) and r4 (vcpu) */
	SAVE_2GPRS(3, r1)

	/* Save non-volatile registers (r14 - r31) */
	SAVE_NVGPRS(r1)

	/* Save CR */
	mfcr	r14
	stw	r14, _CCR(r1)

	/* Save LR */
	PPC_STL	r0, _LINK(r1)

	/* Load non-volatile guest state from the vcpu */
	VCPU_LOAD_NVGPRS(r4)

kvm_start_lightweight:

#ifdef CONFIG_PPC_BOOK3S_64
	PPC_LL	r3, VCPU_HFLAGS(r4)
	rldicl	r3, r3, 0, 63		/* r3 &= 1 */
	stb	r3, HSTATE_RESTORE_HID5(r13)
#endif /* CONFIG_PPC_BOOK3S_64 */

	PPC_LL	r4, VCPU_SHADOW_MSR(r4)	/* get shadow_msr */

	/* Jump to segment patching handler and into our guest */
	bl	FUNC(kvmppc_entry_trampoline)
	nop

/*
 * This is the handler in module memory. It gets jumped at from the
 * lowmem trampoline code, so it's basically the guest exit code.
 *
 */

.global kvmppc_handler_highmem
kvmppc_handler_highmem:

	/*
	 * Register usage at this point:
	 *
	 * R1       = host R1
	 * R2       = host R2
	 * R12      = exit handler id
	 * R13      = PACA
	 * SVCPU.*  = guest *
	 *
	 */

	/* R7 = vcpu */
	PPC_LL	r7, GPR4(r1)

	PPC_STL	r14, VCPU_GPR(r14)(r7)
	PPC_STL	r15, VCPU_GPR(r15)(r7)
	PPC_STL	r16, VCPU_GPR(r16)(r7)
	PPC_STL	r17, VCPU_GPR(r17)(r7)
	PPC_STL	r18, VCPU_GPR(r18)(r7)
	PPC_STL	r19, VCPU_GPR(r19)(r7)
	PPC_STL	r20, VCPU_GPR(r20)(r7)
	PPC_STL	r21, VCPU_GPR(r21)(r7)
	PPC_STL	r22, VCPU_GPR(r22)(r7)
	PPC_STL	r23, VCPU_GPR(r23)(r7)
	PPC_STL	r24, VCPU_GPR(r24)(r7)
	PPC_STL	r25, VCPU_GPR(r25)(r7)
	PPC_STL	r26, VCPU_GPR(r26)(r7)
	PPC_STL	r27, VCPU_GPR(r27)(r7)
	PPC_STL	r28, VCPU_GPR(r28)(r7)
	PPC_STL	r29, VCPU_GPR(r29)(r7)
	PPC_STL	r30, VCPU_GPR(r30)(r7)
	PPC_STL	r31, VCPU_GPR(r31)(r7)

	/* Pass the exit number as 3rd argument to kvmppc_handle_exit */
	mr	r5, r12

	/* Restore r3 (kvm_run) and r4 (vcpu) */
	REST_2GPRS(3, r1)
	bl	FUNC(kvmppc_handle_exit)

	/* If RESUME_GUEST, get back in the loop */
	cmpwi	r3, RESUME_GUEST
	beq	kvm_loop_lightweight

	cmpwi	r3, RESUME_GUEST_NV
	beq	kvm_loop_heavyweight

kvm_exit_loop:

	PPC_LL	r4, _LINK(r1)
	mtlr	r4

	lwz	r14, _CCR(r1)
	mtcr	r14

	/* Restore non-volatile host registers (r14 - r31) */
	REST_NVGPRS(r1)

	addi    r1, r1, SWITCH_FRAME_SIZE
	blr

kvm_loop_heavyweight:

	PPC_LL	r4, _LINK(r1)
	PPC_STL r4, (PPC_LR_STKOFF + SWITCH_FRAME_SIZE)(r1)

	/* Load vcpu and cpu_run */
	REST_2GPRS(3, r1)

	/* Load non-volatile guest state from the vcpu */
	VCPU_LOAD_NVGPRS(r4)

	/* Jump back into the beginning of this function */
	b	kvm_start_lightweight

kvm_loop_lightweight:

	/* We'll need the vcpu pointer */
	REST_GPR(4, r1)

	/* Jump back into the beginning of this function */
	b	kvm_start_lightweight
