#
# Makefile for Kernel-based Virtual Machine module
#

subdir-ccflags-$(CONFIG_PPC_WERROR) := -Werror

ccflags-y := -Ivirt/kvm -Iarch/powerpc/kvm

common-objs-y = $(addprefix ../../../virt/kvm/, kvm_main.o coalesced_mmio.o)

CFLAGS_44x_tlb.o  := -I.
CFLAGS_e500_tlb.o := -I.
CFLAGS_emulate.o  := -I.

common-objs-y += powerpc.o emulate.o
obj-$(CONFIG_KVM_EXIT_TIMING) += timing.o
obj-$(CONFIG_KVM_BOOK3S_HANDLER) += book3s_exports.o

AFLAGS_booke_interrupts.o := -I$(obj)

kvm-440-objs := \
	$(common-objs-y) \
	booke.o \
	booke_emulate.o \
	booke_interrupts.o \
	44x.o \
	44x_tlb.o \
	44x_emulate.o
kvm-objs-$(CONFIG_KVM_440) := $(kvm-440-objs)

kvm-e500-objs := \
	$(common-objs-y) \
	booke.o \
	booke_emulate.o \
	booke_interrupts.o \
	e500.o \
	e500_tlb.o \
	e500_emulate.o
kvm-objs-$(CONFIG_KVM_E500) := $(kvm-e500-objs)

kvm-book3s_64-objs-$(CONFIG_KVM_BOOK3S_64_PR) := \
	../../../virt/kvm/coalesced_mmio.o \
	fpu.o \
	book3s_paired_singles.o \
	book3s_pr.o \
	book3s_pr_papr.o \
	book3s_emulate.o \
	book3s_interrupts.o \
	book3s_mmu_hpte.o \
	book3s_64_mmu_host.o \
	book3s_64_mmu.o \
	book3s_32_mmu.o
kvm-book3s_64-builtin-objs-$(CONFIG_KVM_BOOK3S_64_PR) := \
	book3s_rmhandlers.o

kvm-book3s_64-objs-$(CONFIG_KVM_BOOK3S_64_HV) := \
	book3s_hv.o \
	book3s_hv_interrupts.o \
	book3s_64_mmu_hv.o
kvm-book3s_64-builtin-objs-$(CONFIG_KVM_BOOK3S_64_HV) := \
	book3s_hv_rmhandlers.o \
	book3s_hv_rm_mmu.o \
	book3s_64_vio_hv.o \
	book3s_hv_builtin.o

kvm-book3s_64-module-objs := \
	../../../virt/kvm/kvm_main.o \
	powerpc.o \
	emulate.o \
	book3s.o \
	$(kvm-book3s_64-objs-y)

kvm-objs-$(CONFIG_KVM_BOOK3S_64) := $(kvm-book3s_64-module-objs)

kvm-book3s_32-objs := \
	$(common-objs-y) \
	fpu.o \
	book3s_paired_singles.o \
	book3s.o \
	book3s_pr.o \
	book3s_emulate.o \
	book3s_interrupts.o \
	book3s_mmu_hpte.o \
	book3s_32_mmu_host.o \
	book3s_32_mmu.o
kvm-objs-$(CONFIG_KVM_BOOK3S_32) := $(kvm-book3s_32-objs)

kvm-objs := $(kvm-objs-m) $(kvm-objs-y)

obj-$(CONFIG_KVM_440) += kvm.o
obj-$(CONFIG_KVM_E500) += kvm.o
obj-$(CONFIG_KVM_BOOK3S_64) += kvm.o
obj-$(CONFIG_KVM_BOOK3S_32) += kvm.o

obj-y += $(kvm-book3s_64-builtin-objs-y)
