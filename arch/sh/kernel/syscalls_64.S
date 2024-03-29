/*
 * arch/sh/kernel/syscalls_64.S
 *
 * Copyright (C) 2000, 2001  Paolo Alberelli
 * Copyright (C) 2004 - 2007  Paul Mundt
 * Copyright (C) 2003, 2004 Richard Curnow
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <linux/sys.h>

	.section .data, "aw"
	.balign 32

/*
 * System calls jump table
 */
	.globl  sys_call_table
sys_call_table:
	.long sys_restart_syscall	/* 0  -  old "setup()" system call  */
	.long sys_exit
	.long sys_fork
	.long sys_read
	.long sys_write
	.long sys_open			/* 5 */
	.long sys_close
	.long sys_waitpid
	.long sys_creat
	.long sys_link
	.long sys_unlink		/* 10 */
	.long sys_execve
	.long sys_chdir
	.long sys_time
	.long sys_mknod
	.long sys_chmod			/* 15 */
	.long sys_lchown16
	.long sys_ni_syscall	/* old break syscall holder */
	.long sys_stat
	.long sys_lseek
	.long sys_getpid		/* 20 */
	.long sys_mount
	.long sys_oldumount
	.long sys_setuid16
	.long sys_getuid16
	.long sys_stime			/* 25 */
	.long sh64_ptrace
	.long sys_alarm
	.long sys_fstat
	.long sys_pause
	.long sys_utime			/* 30 */
	.long sys_ni_syscall	/* old stty syscall holder */
	.long sys_ni_syscall	/* old gtty syscall holder */
	.long sys_access
	.long sys_nice
	.long sys_ni_syscall		/* 35 */ /* old ftime syscall holder */
	.long sys_sync
	.long sys_kill
	.long sys_rename
	.long sys_mkdir
	.long sys_rmdir			/* 40 */
	.long sys_dup
	.long sys_pipe
	.long sys_times
	.long sys_ni_syscall	/* old prof syscall holder */
	.long sys_brk			/* 45 */
	.long sys_setgid16
	.long sys_getgid16
	.long sys_signal
	.long sys_geteuid16
	.long sys_getegid16		/* 50 */
	.long sys_acct
	.long sys_umount		/* recycled never used phys( */
	.long sys_ni_syscall	/* old lock syscall holder */
	.long sys_ioctl
	.long sys_fcntl			/* 55 */
	.long sys_ni_syscall	/* old mpx syscall holder */
	.long sys_setpgid
	.long sys_ni_syscall	/* old ulimit syscall holder */
	.long sys_ni_syscall	/* sys_olduname */
	.long sys_umask			/* 60 */
	.long sys_chroot
	.long sys_ustat
	.long sys_dup2
	.long sys_getppid
	.long sys_getpgrp		/* 65 */
	.long sys_setsid
	.long sys_sigaction
	.long sys_sgetmask
	.long sys_ssetmask
	.long sys_setreuid16		/* 70 */
	.long sys_setregid16
	.long sys_sigsuspend
	.long sys_sigpending
	.long sys_sethostname
	.long sys_setrlimit		/* 75 */
	.long sys_old_getrlimit
	.long sys_getrusage
	.long sys_gettimeofday
	.long sys_settimeofday
	.long sys_getgroups16		/* 80 */
	.long sys_setgroups16
	.long sys_ni_syscall	/* sys_oldselect */
	.long sys_symlink
	.long sys_lstat
	.long sys_readlink		/* 85 */
	.long sys_uselib
	.long sys_swapon
	.long sys_reboot
	.long sys_old_readdir
	.long old_mmap			/* 90 */
	.long sys_munmap
	.long sys_truncate
	.long sys_ftruncate
	.long sys_fchmod
	.long sys_fchown16		/* 95 */
	.long sys_getpriority
	.long sys_setpriority
	.long sys_ni_syscall	/* old profil syscall holder */
	.long sys_statfs
	.long sys_fstatfs		/* 100 */
	.long sys_ni_syscall	/* ioperm */
	.long sys_socketcall	/* Obsolete implementation of socket syscall */
	.long sys_syslog
	.long sys_setitimer
	.long sys_getitimer		/* 105 */
	.long sys_newstat
	.long sys_newlstat
	.long sys_newfstat
	.long sys_uname
	.long sys_ni_syscall		/* 110 */ /* iopl */
	.long sys_vhangup
	.long sys_ni_syscall	/* idle */
	.long sys_ni_syscall	/* vm86old */
	.long sys_wait4
	.long sys_swapoff		/* 115 */
	.long sys_sysinfo
	.long sys_ipc		/* Obsolete ipc syscall implementation */
	.long sys_fsync
	.long sys_sigreturn
	.long sys_clone			/* 120 */
	.long sys_setdomainname
	.long sys_newuname
	.long sys_cacheflush	/* x86: sys_modify_ldt */
	.long sys_adjtimex
	.long sys_mprotect		/* 125 */
	.long sys_sigprocmask
	.long sys_ni_syscall		/* old "create_module" */
	.long sys_init_module
	.long sys_delete_module
	.long sys_ni_syscall		/* 130: old "get_kernel_syms" */
	.long sys_quotactl
	.long sys_getpgid
	.long sys_fchdir
	.long sys_bdflush
	.long sys_sysfs			/* 135 */
	.long sys_personality
	.long sys_ni_syscall	/* for afs_syscall */
	.long sys_setfsuid16
	.long sys_setfsgid16
	.long sys_llseek		/* 140 */
	.long sys_getdents
	.long sys_select
	.long sys_flock
	.long sys_msync
	.long sys_readv			/* 145 */
	.long sys_writev
	.long sys_getsid
	.long sys_fdatasync
	.long sys_sysctl
	.long sys_mlock			/* 150 */
	.long sys_munlock
	.long sys_mlockall
	.long sys_munlockall
	.long sys_sched_setparam
	.long sys_sched_getparam	/* 155 */
	.long sys_sched_setscheduler
	.long sys_sched_getscheduler
	.long sys_sched_yield
	.long sys_sched_get_priority_max
	.long sys_sched_get_priority_min  /* 160 */
	.long sys_sched_rr_get_interval
	.long sys_nanosleep
	.long sys_mremap
	.long sys_setresuid16
	.long sys_getresuid16		/* 165 */
	.long sys_ni_syscall	/* vm86 */
	.long sys_ni_syscall	/* old "query_module" */
	.long sys_poll
	.long sys_ni_syscall	/* was nfsservctl */
	.long sys_setresgid16		/* 170 */
	.long sys_getresgid16
	.long sys_prctl
	.long sys_rt_sigreturn
	.long sys_rt_sigaction
	.long sys_rt_sigprocmask	/* 175 */
	.long sys_rt_sigpending
	.long sys_rt_sigtimedwait
	.long sys_rt_sigqueueinfo
	.long sys_rt_sigsuspend
	.long sys_pread64		/* 180 */
	.long sys_pwrite64
	.long sys_chown16
	.long sys_getcwd
	.long sys_capget
	.long sys_capset		/* 185 */
	.long sys_sigaltstack
	.long sys_sendfile
	.long sys_ni_syscall	/* getpmsg */
	.long sys_ni_syscall	/* putpmsg */
	.long sys_vfork			/* 190 */
	.long sys_getrlimit
	.long sys_mmap2
	.long sys_truncate64
	.long sys_ftruncate64
	.long sys_stat64		/* 195 */
	.long sys_lstat64
	.long sys_fstat64
	.long sys_lchown
	.long sys_getuid
	.long sys_getgid		/* 200 */
	.long sys_geteuid
	.long sys_getegid
	.long sys_setreuid
	.long sys_setregid
	.long sys_getgroups		/* 205 */
	.long sys_setgroups
	.long sys_fchown
	.long sys_setresuid
	.long sys_getresuid
	.long sys_setresgid		/* 210 */
	.long sys_getresgid
	.long sys_chown
	.long sys_setuid
	.long sys_setgid
	.long sys_setfsuid		/* 215 */
	.long sys_setfsgid
	.long sys_pivot_root
	.long sys_mincore
	.long sys_madvise
	/* Broken-out socket family (maintain backwards compatibility in syscall
	   numbering with 2.4) */
	.long sys_socket		/* 220 */
	.long sys_bind
	.long sys_connect
	.long sys_listen
	.long sys_accept
	.long sys_getsockname		/* 225 */
	.long sys_getpeername
	.long sys_socketpair
	.long sys_send
	.long sys_sendto
	.long sys_recv			/* 230*/
	.long sys_recvfrom
	.long sys_shutdown
	.long sys_setsockopt
	.long sys_getsockopt
	.long sys_sendmsg		/* 235 */
	.long sys_recvmsg
	/* Broken-out IPC family (maintain backwards compatibility in syscall
	   numbering with 2.4) */
	.long sys_semop
	.long sys_semget
	.long sys_semctl
	.long sys_msgsnd		/* 240 */
	.long sys_msgrcv
	.long sys_msgget
	.long sys_msgctl
	.long sys_shmat
	.long sys_shmdt			/* 245 */
	.long sys_shmget
	.long sys_shmctl
	/* Rest of syscalls listed in 2.4 i386 unistd.h */
	.long sys_getdents64
	.long sys_fcntl64
	.long sys_ni_syscall		/* 250 reserved for TUX */
	.long sys_ni_syscall		/* Reserved for Security */
	.long sys_gettid
	.long sys_readahead
	.long sys_setxattr
	.long sys_lsetxattr		/* 255 */
	.long sys_fsetxattr
	.long sys_getxattr
	.long sys_lgetxattr
	.long sys_fgetxattr
	.long sys_listxattr		/* 260 */
	.long sys_llistxattr
	.long sys_flistxattr
	.long sys_removexattr
	.long sys_lremovexattr
	.long sys_fremovexattr  	/* 265 */
	.long sys_tkill
	.long sys_sendfile64
	.long sys_futex
	.long sys_sched_setaffinity
	.long sys_sched_getaffinity	/* 270 */
	.long sys_ni_syscall		/* reserved for set_thread_area */
	.long sys_ni_syscall		/* reserved for get_thread_area */
	.long sys_io_setup
	.long sys_io_destroy
	.long sys_io_getevents		/* 275 */
	.long sys_io_submit
	.long sys_io_cancel
	.long sys_fadvise64
	.long sys_ni_syscall
	.long sys_exit_group		/* 280 */
	/* Rest of new 2.6 syscalls */
	.long sys_lookup_dcookie
	.long sys_epoll_create
	.long sys_epoll_ctl
	.long sys_epoll_wait
 	.long sys_remap_file_pages	/* 285 */
 	.long sys_set_tid_address
 	.long sys_timer_create
 	.long sys_timer_settime
 	.long sys_timer_gettime
 	.long sys_timer_getoverrun	/* 290 */
 	.long sys_timer_delete
 	.long sys_clock_settime
 	.long sys_clock_gettime
 	.long sys_clock_getres
 	.long sys_clock_nanosleep	/* 295 */
	.long sys_statfs64
	.long sys_fstatfs64
	.long sys_tgkill
	.long sys_utimes
 	.long sys_fadvise64_64		/* 300 */
	.long sys_ni_syscall	/* Reserved for vserver */
	.long sys_ni_syscall	/* Reserved for mbind */
	.long sys_ni_syscall	/* get_mempolicy */
	.long sys_ni_syscall	/* set_mempolicy */
	.long sys_mq_open		/* 305 */
	.long sys_mq_unlink
	.long sys_mq_timedsend
	.long sys_mq_timedreceive
	.long sys_mq_notify
	.long sys_mq_getsetattr		/* 310 */
	.long sys_ni_syscall	/* Reserved for kexec */
	.long sys_waitid
	.long sys_add_key
	.long sys_request_key
	.long sys_keyctl		/* 315 */
	.long sys_ioprio_set
	.long sys_ioprio_get
	.long sys_inotify_init
	.long sys_inotify_add_watch
	.long sys_inotify_rm_watch	/* 320 */
	.long sys_ni_syscall
	.long sys_migrate_pages
	.long sys_openat
	.long sys_mkdirat
	.long sys_mknodat		/* 325 */
	.long sys_fchownat
	.long sys_futimesat
	.long sys_fstatat64
	.long sys_unlinkat
	.long sys_renameat		/* 330 */
	.long sys_linkat
	.long sys_symlinkat
	.long sys_readlinkat
	.long sys_fchmodat
	.long sys_faccessat		/* 335 */
	.long sys_pselect6
	.long sys_ppoll
	.long sys_unshare
	.long sys_set_robust_list
	.long sys_get_robust_list	/* 340 */
	.long sys_splice
	.long sys_sync_file_range
	.long sys_tee
	.long sys_vmsplice
	.long sys_move_pages		/* 345 */
	.long sys_getcpu
	.long sys_epoll_pwait
	.long sys_utimensat
	.long sys_signalfd
	.long sys_timerfd_create	/* 350 */
	.long sys_eventfd
	.long sys_fallocate
	.long sys_timerfd_settime
	.long sys_timerfd_gettime
	.long sys_signalfd4		/* 355 */
	.long sys_eventfd2
	.long sys_epoll_create1
	.long sys_dup3
	.long sys_pipe2
	.long sys_inotify_init1		/* 360 */
	.long sys_preadv
	.long sys_pwritev
	.long sys_rt_tgsigqueueinfo
	.long sys_perf_event_open
	.long sys_recvmmsg		/* 365 */
	.long sys_accept4
	.long sys_fanotify_init
	.long sys_fanotify_mark
	.long sys_prlimit64
	.long sys_name_to_handle_at	/* 370 */
	.long sys_open_by_handle_at
	.long sys_clock_adjtime
	.long sys_syncfs
	.long sys_sendmmsg
	.long sys_setns			/* 375 */
	.long sys_process_vm_readv
	.long sys_process_vm_writev
