/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#ifndef __BTRFS_I__
#define __BTRFS_I__

#include "extent_map.h"
#include "extent_io.h"
#include "ordered-data.h"
#include "delayed-inode.h"

/* in memory btrfs inode */
struct btrfs_inode {
	/* which subvolume this inode belongs to */
	struct btrfs_root *root;

	/* key used to find this inode on disk.  This is used by the code
	 * to read in roots of subvolumes
	 */
	struct btrfs_key location;

	/* Lock for counters */
	spinlock_t lock;

	/* the extent_tree has caches of all the extent mappings to disk */
	struct extent_map_tree extent_tree;

	/* the io_tree does range state (DIRTY, LOCKED etc) */
	struct extent_io_tree io_tree;

	/* special utility tree used to record which mirrors have already been
	 * tried when checksums fail for a given block
	 */
	struct extent_io_tree io_failure_tree;

	/* held while logging the inode in tree-log.c */
	struct mutex log_mutex;

	/* held while doing delalloc reservations */
	struct mutex delalloc_mutex;

	/* used to order data wrt metadata */
	struct btrfs_ordered_inode_tree ordered_tree;

	/* for keeping track of orphaned inodes */
	struct list_head i_orphan;

	/* list of all the delalloc inodes in the FS.  There are times we need
	 * to write all the delalloc pages to disk, and this list is used
	 * to walk them all.
	 */
	struct list_head delalloc_inodes;

	/*
	 * list for tracking inodes that must be sent to disk before a
	 * rename or truncate commit
	 */
	struct list_head ordered_operations;

	/* node for the red-black tree that links inodes in subvolume root */
	struct rb_node rb_node;

	/* the space_info for where this inode's data allocations are done */
	struct btrfs_space_info *space_info;

	/* full 64 bit generation number, struct vfs_inode doesn't have a big
	 * enough field for this.
	 */
	u64 generation;

	/* sequence number for NFS changes */
	u64 sequence;

	/*
	 * transid of the trans_handle that last modified this inode
	 */
	u64 last_trans;

	/*
	 * log transid when this inode was last modified
	 */
	u64 last_sub_trans;

	/*
	 * transid that last logged this inode
	 */
	u64 logged_trans;

	/* total number of bytes pending delalloc, used by stat to calc the
	 * real block usage of the file
	 */
	u64 delalloc_bytes;

	/*
	 * the size of the file stored in the metadata on disk.  data=ordered
	 * means the in-memory i_size might be larger than the size on disk
	 * because not all the blocks are written yet.
	 */
	u64 disk_i_size;

	/*
	 * if this is a directory then index_cnt is the counter for the index
	 * number for new files that are created
	 */
	u64 index_cnt;

	/* the fsync log has some corner cases that mean we have to check
	 * directories to see if any unlinks have been done before
	 * the directory was logged.  See tree-log.c for all the
	 * details
	 */
	u64 last_unlink_trans;

	/*
	 * Number of bytes outstanding that are going to need csums.  This is
	 * used in ENOSPC accounting.
	 */
	u64 csum_bytes;

	/* flags field from the on disk inode */
	u32 flags;

	/*
	 * Counters to keep track of the number of extent item's we may use due
	 * to delalloc and such.  outstanding_extents is the number of extent
	 * items we think we'll end up using, and reserved_extents is the number
	 * of extent items we've reserved metadata for.
	 */
	unsigned outstanding_extents;
	unsigned reserved_extents;

	/*
	 * ordered_data_close is set by truncate when a file that used
	 * to have good data has been truncated to zero.  When it is set
	 * the btrfs file release call will add this inode to the
	 * ordered operations list so that we make sure to flush out any
	 * new data the application may have written before commit.
	 */
	unsigned ordered_data_close:1;
	unsigned orphan_meta_reserved:1;
	unsigned dummy_inode:1;
	unsigned in_defrag:1;
	unsigned delalloc_meta_reserved:1;

	/*
	 * always compress this one file
	 */
	unsigned force_compress:4;

	struct btrfs_delayed_node *delayed_node;

	struct inode vfs_inode;
};

extern unsigned char btrfs_filetype_table[];

static inline struct btrfs_inode *BTRFS_I(struct inode *inode)
{
	return container_of(inode, struct btrfs_inode, vfs_inode);
}

static inline u64 btrfs_ino(struct inode *inode)
{
	u64 ino = BTRFS_I(inode)->location.objectid;

	/*
	 * !ino: btree_inode
	 * type == BTRFS_ROOT_ITEM_KEY: subvol dir
	 */
	if (!ino || BTRFS_I(inode)->location.type == BTRFS_ROOT_ITEM_KEY)
		ino = inode->i_ino;
	return ino;
}

static inline void btrfs_i_size_write(struct inode *inode, u64 size)
{
	i_size_write(inode, size);
	BTRFS_I(inode)->disk_i_size = size;
}

static inline bool btrfs_is_free_space_inode(struct btrfs_root *root,
				       struct inode *inode)
{
	if (root == root->fs_info->tree_root ||
	    BTRFS_I(inode)->location.objectid == BTRFS_FREE_INO_OBJECTID)
		return true;
	return false;
}

#endif
