/*
 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Yu Liu, yu.liu@freescale.com
 *
 * Description:
 * This file is based on arch/powerpc/kvm/44x_tlb.h,
 * by Hollis Blanchard <hollisb@us.ibm.com>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 */

#ifndef __KVM_E500_TLB_H__
#define __KVM_E500_TLB_H__

#include <linux/kvm_host.h>
#include <asm/mmu-book3e.h>
#include <asm/tlb.h>
#include <asm/kvm_e500.h>

/* This geometry is the legacy default -- can be overridden by userspace */
#define KVM_E500_TLB0_WAY_SIZE		128
#define KVM_E500_TLB0_WAY_NUM		2

#define KVM_E500_TLB0_SIZE  (KVM_E500_TLB0_WAY_SIZE * KVM_E500_TLB0_WAY_NUM)
#define KVM_E500_TLB1_SIZE  16

#define index_of(tlbsel, esel)	(((tlbsel) << 16) | ((esel) & 0xFFFF))
#define tlbsel_of(index)	((index) >> 16)
#define esel_of(index)		((index) & 0xFFFF)

#define E500_TLB_USER_PERM_MASK (MAS3_UX|MAS3_UR|MAS3_UW)
#define E500_TLB_SUPER_PERM_MASK (MAS3_SX|MAS3_SR|MAS3_SW)
#define MAS2_ATTRIB_MASK \
	  (MAS2_X0 | MAS2_X1)
#define MAS3_ATTRIB_MASK \
	  (MAS3_U0 | MAS3_U1 | MAS3_U2 | MAS3_U3 \
	   | E500_TLB_USER_PERM_MASK | E500_TLB_SUPER_PERM_MASK)

extern void kvmppc_dump_tlbs(struct kvm_vcpu *);
extern int kvmppc_e500_emul_mt_mmucsr0(struct kvmppc_vcpu_e500 *, ulong);
extern int kvmppc_e500_emul_tlbwe(struct kvm_vcpu *);
extern int kvmppc_e500_emul_tlbre(struct kvm_vcpu *);
extern int kvmppc_e500_emul_tlbivax(struct kvm_vcpu *, int, int);
extern int kvmppc_e500_emul_tlbsx(struct kvm_vcpu *, int);
extern int kvmppc_e500_tlb_search(struct kvm_vcpu *, gva_t, unsigned int, int);
extern void kvmppc_e500_tlb_put(struct kvm_vcpu *);
extern void kvmppc_e500_tlb_load(struct kvm_vcpu *, int);
extern int kvmppc_e500_tlb_init(struct kvmppc_vcpu_e500 *);
extern void kvmppc_e500_tlb_uninit(struct kvmppc_vcpu_e500 *);
extern void kvmppc_e500_tlb_setup(struct kvmppc_vcpu_e500 *);
extern void kvmppc_e500_recalc_shadow_pid(struct kvmppc_vcpu_e500 *);

/* TLB helper functions */
static inline unsigned int
get_tlb_size(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return (tlbe->mas1 >> 7) & 0x1f;
}

static inline gva_t get_tlb_eaddr(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return tlbe->mas2 & 0xfffff000;
}

static inline u64 get_tlb_bytes(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	unsigned int pgsize = get_tlb_size(tlbe);
	return 1ULL << 10 << pgsize;
}

static inline gva_t get_tlb_end(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	u64 bytes = get_tlb_bytes(tlbe);
	return get_tlb_eaddr(tlbe) + bytes - 1;
}

static inline u64 get_tlb_raddr(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return tlbe->mas7_3 & ~0xfffULL;
}

static inline unsigned int
get_tlb_tid(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return (tlbe->mas1 >> 16) & 0xff;
}

static inline unsigned int
get_tlb_ts(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return (tlbe->mas1 >> 12) & 0x1;
}

static inline unsigned int
get_tlb_v(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return (tlbe->mas1 >> 31) & 0x1;
}

static inline unsigned int
get_tlb_iprot(const struct kvm_book3e_206_tlb_entry *tlbe)
{
	return (tlbe->mas1 >> 30) & 0x1;
}

static inline unsigned int get_cur_pid(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.pid & 0xff;
}

static inline unsigned int get_cur_as(struct kvm_vcpu *vcpu)
{
	return !!(vcpu->arch.shared->msr & (MSR_IS | MSR_DS));
}

static inline unsigned int get_cur_pr(struct kvm_vcpu *vcpu)
{
	return !!(vcpu->arch.shared->msr & MSR_PR);
}

static inline unsigned int get_cur_spid(const struct kvm_vcpu *vcpu)
{
	return (vcpu->arch.shared->mas6 >> 16) & 0xff;
}

static inline unsigned int get_cur_sas(const struct kvm_vcpu *vcpu)
{
	return vcpu->arch.shared->mas6 & 0x1;
}

static inline unsigned int get_tlb_tlbsel(const struct kvm_vcpu *vcpu)
{
	/*
	 * Manual says that tlbsel has 2 bits wide.
	 * Since we only have two TLBs, only lower bit is used.
	 */
	return (vcpu->arch.shared->mas0 >> 28) & 0x1;
}

static inline unsigned int get_tlb_nv_bit(const struct kvm_vcpu *vcpu)
{
	return vcpu->arch.shared->mas0 & 0xfff;
}

static inline unsigned int get_tlb_esel_bit(const struct kvm_vcpu *vcpu)
{
	return (vcpu->arch.shared->mas0 >> 16) & 0xfff;
}

static inline int tlbe_is_host_safe(const struct kvm_vcpu *vcpu,
			const struct kvm_book3e_206_tlb_entry *tlbe)
{
	gpa_t gpa;

	if (!get_tlb_v(tlbe))
		return 0;

	/* Does it match current guest AS? */
	/* XXX what about IS != DS? */
	if (get_tlb_ts(tlbe) != !!(vcpu->arch.shared->msr & MSR_IS))
		return 0;

	gpa = get_tlb_raddr(tlbe);
	if (!gfn_to_memslot(vcpu->kvm, gpa >> PAGE_SHIFT))
		/* Mapping is not for RAM. */
		return 0;

	return 1;
}

#endif /* __KVM_E500_TLB_H__ */
