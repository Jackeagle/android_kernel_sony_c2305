/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software Foundation,
 * Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "xfs.h"
#include "xfs_fs.h"
#include "xfs_types.h"
#include "xfs_bit.h"
#include "xfs_log.h"
#include "xfs_inum.h"
#include "xfs_trans.h"
#include "xfs_sb.h"
#include "xfs_ag.h"
#include "xfs_mount.h"
#include "xfs_bmap_btree.h"
#include "xfs_alloc_btree.h"
#include "xfs_ialloc_btree.h"
#include "xfs_dinode.h"
#include "xfs_inode.h"
#include "xfs_btree.h"
#include "xfs_trans_priv.h"
#include "xfs_inode_item.h"
#include "xfs_trace.h"

#ifdef XFS_TRANS_DEBUG
STATIC void
xfs_trans_inode_broot_debug(
	xfs_inode_t	*ip);
#else
#define	xfs_trans_inode_broot_debug(ip)
#endif

/*
 * Add a locked inode to the transaction.
 *
 * The inode must be locked, and it cannot be associated with any transaction.
 * If lock_flags is non-zero the inode will be unlocked on transaction commit.
 */
void
xfs_trans_ijoin(
	struct xfs_trans	*tp,
	struct xfs_inode	*ip,
	uint			lock_flags)
{
	xfs_inode_log_item_t	*iip;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	if (ip->i_itemp == NULL)
		xfs_inode_item_init(ip, ip->i_mount);
	iip = ip->i_itemp;

	ASSERT(iip->ili_lock_flags == 0);
	iip->ili_lock_flags = lock_flags;

	/*
	 * Get a log_item_desc to point at the new item.
	 */
	xfs_trans_add_item(tp, &iip->ili_item);

	xfs_trans_inode_broot_debug(ip);
}

/*
 * Transactional inode timestamp update. Requires the inode to be locked and
 * joined to the transaction supplied. Relies on the transaction subsystem to
 * track dirty state and update/writeback the inode accordingly.
 */
void
xfs_trans_ichgtime(
	struct xfs_trans	*tp,
	struct xfs_inode	*ip,
	int			flags)
{
	struct inode		*inode = VFS_I(ip);
	timespec_t		tv;

	ASSERT(tp);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	tv = current_fs_time(inode->i_sb);

	if ((flags & XFS_ICHGTIME_MOD) &&
	    !timespec_equal(&inode->i_mtime, &tv)) {
		inode->i_mtime = tv;
		ip->i_d.di_mtime.t_sec = tv.tv_sec;
		ip->i_d.di_mtime.t_nsec = tv.tv_nsec;
	}
	if ((flags & XFS_ICHGTIME_CHG) &&
	    !timespec_equal(&inode->i_ctime, &tv)) {
		inode->i_ctime = tv;
		ip->i_d.di_ctime.t_sec = tv.tv_sec;
		ip->i_d.di_ctime.t_nsec = tv.tv_nsec;
	}
}

/*
 * This is called to mark the fields indicated in fieldmask as needing
 * to be logged when the transaction is committed.  The inode must
 * already be associated with the given transaction.
 *
 * The values for fieldmask are defined in xfs_inode_item.h.  We always
 * log all of the core inode if any of it has changed, and we always log
 * all of the inline data/extents/b-tree root if any of them has changed.
 */
void
xfs_trans_log_inode(
	xfs_trans_t	*tp,
	xfs_inode_t	*ip,
	uint		flags)
{
	ASSERT(ip->i_itemp != NULL);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	tp->t_flags |= XFS_TRANS_DIRTY;
	ip->i_itemp->ili_item.li_desc->lid_flags |= XFS_LID_DIRTY;

	/*
	 * Always OR in the bits from the ili_last_fields field.
	 * This is to coordinate with the xfs_iflush() and xfs_iflush_done()
	 * routines in the eventual clearing of the ili_fields bits.
	 * See the big comment in xfs_iflush() for an explanation of
	 * this coordination mechanism.
	 */
	flags |= ip->i_itemp->ili_last_fields;
	ip->i_itemp->ili_fields |= flags;
}

#ifdef XFS_TRANS_DEBUG
/*
 * Keep track of the state of the inode btree root to make sure we
 * log it properly.
 */
STATIC void
xfs_trans_inode_broot_debug(
	xfs_inode_t	*ip)
{
	xfs_inode_log_item_t	*iip;

	ASSERT(ip->i_itemp != NULL);
	iip = ip->i_itemp;
	if (iip->ili_root_size != 0) {
		ASSERT(iip->ili_orig_root != NULL);
		kmem_free(iip->ili_orig_root);
		iip->ili_root_size = 0;
		iip->ili_orig_root = NULL;
	}
	if (ip->i_d.di_format == XFS_DINODE_FMT_BTREE) {
		ASSERT((ip->i_df.if_broot != NULL) &&
		       (ip->i_df.if_broot_bytes > 0));
		iip->ili_root_size = ip->i_df.if_broot_bytes;
		iip->ili_orig_root =
			(char*)kmem_alloc(iip->ili_root_size, KM_SLEEP);
		memcpy(iip->ili_orig_root, (char*)(ip->i_df.if_broot),
		      iip->ili_root_size);
	}
}
#endif
