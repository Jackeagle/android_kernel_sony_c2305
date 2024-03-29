#
# Makefile for the linux kernel.
#

ifdef CONFIG_FUNCTION_TRACER
# Don't trace early setup code and tracing code
CFLAGS_REMOVE_early.o = -pg
CFLAGS_REMOVE_ftrace.o = -pg
endif

#
# Passing null pointers is ok for smp code, since we access the lowcore here.
#
CFLAGS_smp.o	:= -Wno-nonnull

#
# Pass UTS_MACHINE for user_regset definition
#
CFLAGS_ptrace.o		+= -DUTS_MACHINE='"$(UTS_MACHINE)"'

CFLAGS_sysinfo.o += -Iinclude/math-emu -Iarch/s390/math-emu -w

obj-y	:=  bitmap.o traps.o time.o process.o base.o early.o setup.o vtime.o \
	    processor.o sys_s390.o ptrace.o signal.o cpcmd.o ebcdic.o nmi.o \
	    debug.o irq.o ipl.o dis.o diag.o mem_detect.o sclp.o vdso.o \
	    sysinfo.o jump_label.o lgr.o os_info.o

obj-y	+= $(if $(CONFIG_64BIT),entry64.o,entry.o)
obj-y	+= $(if $(CONFIG_64BIT),reipl64.o,reipl.o)

extra-y				+= head.o init_task.o vmlinux.lds
extra-y				+= $(if $(CONFIG_64BIT),head64.o,head31.o)

obj-$(CONFIG_MODULES)		+= s390_ksyms.o module.o
obj-$(CONFIG_SMP)		+= smp.o
obj-$(CONFIG_SCHED_BOOK)	+= topology.o
obj-$(CONFIG_HIBERNATION)	+= suspend.o swsusp_asm64.o
obj-$(CONFIG_AUDIT)		+= audit.o
compat-obj-$(CONFIG_AUDIT)	+= compat_audit.o
obj-$(CONFIG_COMPAT)		+= compat_linux.o compat_signal.o \
					compat_wrapper.o compat_exec_domain.o \
					$(compat-obj-y)

obj-$(CONFIG_STACKTRACE)	+= stacktrace.o
obj-$(CONFIG_KPROBES)		+= kprobes.o
obj-$(CONFIG_FUNCTION_TRACER)	+= $(if $(CONFIG_64BIT),mcount64.o,mcount.o)
obj-$(CONFIG_DYNAMIC_FTRACE)	+= ftrace.o
obj-$(CONFIG_FUNCTION_GRAPH_TRACER) += ftrace.o
obj-$(CONFIG_FTRACE_SYSCALLS)  += ftrace.o
obj-$(CONFIG_CRASH_DUMP)	+= crash_dump.o
obj-$(CONFIG_PERF_EVENTS)	+= perf_event.o perf_cpum_cf.o

# Kexec part
S390_KEXEC_OBJS := machine_kexec.o crash.o
S390_KEXEC_OBJS += $(if $(CONFIG_64BIT),relocate_kernel64.o,relocate_kernel.o)
obj-$(CONFIG_KEXEC) += $(S390_KEXEC_OBJS)

# vdso
obj-$(CONFIG_64BIT)		+= vdso64/
obj-$(CONFIG_32BIT)		+= vdso32/
obj-$(CONFIG_COMPAT)		+= vdso32/
