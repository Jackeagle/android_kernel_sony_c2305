#include <linux/mount.h>
#include <linux/seq_file.h>
#include <linux/poll.h>

struct mnt_namespace {
	atomic_t		count;
	struct mount *	root;
	struct list_head	list;
	wait_queue_head_t poll;
	int event;
};

struct mnt_pcp {
	int mnt_count;
	int mnt_writers;
};

struct mount {
	struct list_head mnt_hash;
	struct mount *mnt_parent;
	struct dentry *mnt_mountpoint;
	struct vfsmount mnt;
#ifdef CONFIG_SMP
	struct mnt_pcp __percpu *mnt_pcp;
	atomic_t mnt_longterm;		/* how many of the refs are longterm */
#else
	int mnt_count;
	int mnt_writers;
#endif
	struct list_head mnt_mounts;	/* list of children, anchored here */
	struct list_head mnt_child;	/* and going through their mnt_child */
	struct list_head mnt_instance;	/* mount instance on sb->s_mounts */
	const char *mnt_devname;	/* Name of device e.g. /dev/dsk/hda1 */
	struct list_head mnt_list;
	struct list_head mnt_expire;	/* link in fs-specific expiry list */
	struct list_head mnt_share;	/* circular list of shared mounts */
	struct list_head mnt_slave_list;/* list of slave mounts */
	struct list_head mnt_slave;	/* slave list entry */
	struct mount *mnt_master;	/* slave is on master->mnt_slave_list */
	struct mnt_namespace *mnt_ns;	/* containing namespace */
#ifdef CONFIG_FSNOTIFY
	struct hlist_head mnt_fsnotify_marks;
	__u32 mnt_fsnotify_mask;
#endif
	int mnt_id;			/* mount identifier */
	int mnt_group_id;		/* peer group identifier */
	int mnt_expiry_mark;		/* true if marked for expiry */
	int mnt_pinned;
	int mnt_ghosts;
};

static inline struct mount *real_mount(struct vfsmount *mnt)
{
	return container_of(mnt, struct mount, mnt);
}

static inline int mnt_has_parent(struct mount *mnt)
{
	return mnt != mnt->mnt_parent;
}

extern struct mount *__lookup_mnt(struct vfsmount *, struct dentry *, int);

static inline void get_mnt_ns(struct mnt_namespace *ns)
{
	atomic_inc(&ns->count);
}

struct proc_mounts {
	struct seq_file m; /* must be the first element */
	struct mnt_namespace *ns;
	struct path root;
	int (*show)(struct seq_file *, struct vfsmount *);
};

extern const struct seq_operations mounts_op;
