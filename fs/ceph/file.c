#include <linux/ceph/ceph_debug.h>

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/file.h>
#include <linux/namei.h>
#include <linux/writeback.h>

#include "super.h"
#include "mds_client.h"

/*
 * Ceph file operations
 *
 * Implement basic open/close functionality, and implement
 * read/write.
 *
 * We implement three modes of file I/O:
 *  - buffered uses the generic_file_aio_{read,write} helpers
 *
 *  - synchronous is used when there is multi-client read/write
 *    sharing, avoids the page cache, and synchronously waits for an
 *    ack from the OSD.
 *
 *  - direct io takes the variant of the sync path that references
 *    user pages directly.
 *
 * fsync() flushes and waits on dirty pages, but just queues metadata
 * for writeback: since the MDS can recover size and mtime there is no
 * need to wait for MDS acknowledgement.
 */


/*
 * Prepare an open request.  Preallocate ceph_cap to avoid an
 * inopportune ENOMEM later.
 */
static struct ceph_mds_request *
prepare_open_request(struct super_block *sb, int flags, int create_mode)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	int want_auth = USE_ANY_MDS;
	int op = (flags & O_CREAT) ? CEPH_MDS_OP_CREATE : CEPH_MDS_OP_OPEN;

	if (flags & (O_WRONLY|O_RDWR|O_CREAT|O_TRUNC))
		want_auth = USE_AUTH_MDS;

	req = ceph_mdsc_create_request(mdsc, op, want_auth);
	if (IS_ERR(req))
		goto out;
	req->r_fmode = ceph_flags_to_mode(flags);
	req->r_args.open.flags = cpu_to_le32(flags);
	req->r_args.open.mode = cpu_to_le32(create_mode);
	req->r_args.open.preferred = cpu_to_le32(-1);
out:
	return req;
}

/*
 * initialize private struct file data.
 * if we fail, clean up by dropping fmode reference on the ceph_inode
 */
static int ceph_init_file(struct inode *inode, struct file *file, int fmode)
{
	struct ceph_file_info *cf;
	int ret = 0;

	switch (inode->i_mode & S_IFMT) {
	case S_IFREG:
	case S_IFDIR:
		dout("init_file %p %p 0%o (regular)\n", inode, file,
		     inode->i_mode);
		cf = kmem_cache_alloc(ceph_file_cachep, GFP_NOFS | __GFP_ZERO);
		if (cf == NULL) {
			ceph_put_fmode(ceph_inode(inode), fmode); /* clean up */
			return -ENOMEM;
		}
		cf->fmode = fmode;
		cf->next_offset = 2;
		file->private_data = cf;
		BUG_ON(inode->i_fop->release != ceph_release);
		break;

	case S_IFLNK:
		dout("init_file %p %p 0%o (symlink)\n", inode, file,
		     inode->i_mode);
		ceph_put_fmode(ceph_inode(inode), fmode); /* clean up */
		break;

	default:
		dout("init_file %p %p 0%o (special)\n", inode, file,
		     inode->i_mode);
		/*
		 * we need to drop the open ref now, since we don't
		 * have .release set to ceph_release.
		 */
		ceph_put_fmode(ceph_inode(inode), fmode); /* clean up */
		BUG_ON(inode->i_fop->release == ceph_release);

		/* call the proper open fop */
		ret = inode->i_fop->open(inode, file);
	}
	return ret;
}

/*
 * If the filp already has private_data, that means the file was
 * already opened by intent during lookup, and we do nothing.
 *
 * If we already have the requisite capabilities, we can satisfy
 * the open request locally (no need to request new caps from the
 * MDS).  We do, however, need to inform the MDS (asynchronously)
 * if our wanted caps set expands.
 */
int ceph_open(struct inode *inode, struct file *file)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_sb_to_client(inode->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	struct ceph_file_info *cf = file->private_data;
	struct inode *parent_inode = NULL;
	int err;
	int flags, fmode, wanted;

	if (cf) {
		dout("open file %p is already opened\n", file);
		return 0;
	}

	/* filter out O_CREAT|O_EXCL; vfs did that already.  yuck. */
	flags = file->f_flags & ~(O_CREAT|O_EXCL);
	if (S_ISDIR(inode->i_mode))
		flags = O_DIRECTORY;  /* mds likes to know */

	dout("open inode %p ino %llx.%llx file %p flags %d (%d)\n", inode,
	     ceph_vinop(inode), file, flags, file->f_flags);
	fmode = ceph_flags_to_mode(flags);
	wanted = ceph_caps_for_mode(fmode);

	/* snapped files are read-only */
	if (ceph_snap(inode) != CEPH_NOSNAP && (file->f_mode & FMODE_WRITE))
		return -EROFS;

	/* trivially open snapdir */
	if (ceph_snap(inode) == CEPH_SNAPDIR) {
		spin_lock(&ci->i_ceph_lock);
		__ceph_get_fmode(ci, fmode);
		spin_unlock(&ci->i_ceph_lock);
		return ceph_init_file(inode, file, fmode);
	}

	/*
	 * No need to block if we have caps on the auth MDS (for
	 * write) or any MDS (for read).  Update wanted set
	 * asynchronously.
	 */
	spin_lock(&ci->i_ceph_lock);
	if (__ceph_is_any_real_caps(ci) &&
	    (((fmode & CEPH_FILE_MODE_WR) == 0) || ci->i_auth_cap)) {
		int mds_wanted = __ceph_caps_mds_wanted(ci);
		int issued = __ceph_caps_issued(ci, NULL);

		dout("open %p fmode %d want %s issued %s using existing\n",
		     inode, fmode, ceph_cap_string(wanted),
		     ceph_cap_string(issued));
		__ceph_get_fmode(ci, fmode);
		spin_unlock(&ci->i_ceph_lock);

		/* adjust wanted? */
		if ((issued & wanted) != wanted &&
		    (mds_wanted & wanted) != wanted &&
		    ceph_snap(inode) != CEPH_SNAPDIR)
			ceph_check_caps(ci, 0, NULL);

		return ceph_init_file(inode, file, fmode);
	} else if (ceph_snap(inode) != CEPH_NOSNAP &&
		   (ci->i_snap_caps & wanted) == wanted) {
		__ceph_get_fmode(ci, fmode);
		spin_unlock(&ci->i_ceph_lock);
		return ceph_init_file(inode, file, fmode);
	}
	spin_unlock(&ci->i_ceph_lock);

	dout("open fmode %d wants %s\n", fmode, ceph_cap_string(wanted));
	req = prepare_open_request(inode->i_sb, flags, 0);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto out;
	}
	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;
	if (flags & (O_CREAT|O_TRUNC))
		parent_inode = ceph_get_dentry_parent_inode(file->f_dentry);
	err = ceph_mdsc_do_request(mdsc, parent_inode, req);
	iput(parent_inode);
	if (!err)
		err = ceph_init_file(inode, file, req->r_fmode);
	ceph_mdsc_put_request(req);
	dout("open result=%d on %llx.%llx\n", err, ceph_vinop(inode));
out:
	return err;
}


/*
 * Do a lookup + open with a single request.
 *
 * If this succeeds, but some subsequent check in the vfs
 * may_open() fails, the struct *file gets cleaned up (i.e.
 * ceph_release gets called).  So fear not!
 */
/*
 * flags
 *  path_lookup_open   -> LOOKUP_OPEN
 *  path_lookup_create -> LOOKUP_OPEN|LOOKUP_CREATE
 */
struct dentry *ceph_lookup_open(struct inode *dir, struct dentry *dentry,
				struct nameidata *nd, int mode,
				int locked_dir)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct file *file;
	struct ceph_mds_request *req;
	struct dentry *ret;
	int err;
	int flags = nd->intent.open.flags;

	dout("ceph_lookup_open dentry %p '%.*s' flags %d mode 0%o\n",
	     dentry, dentry->d_name.len, dentry->d_name.name, flags, mode);

	/* do the open */
	req = prepare_open_request(dir->i_sb, flags, mode);
	if (IS_ERR(req))
		return ERR_CAST(req);
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	if (flags & O_CREAT) {
		req->r_dentry_drop = CEPH_CAP_FILE_SHARED;
		req->r_dentry_unless = CEPH_CAP_FILE_EXCL;
	}
	req->r_locked_dir = dir;           /* caller holds dir->i_mutex */
	err = ceph_mdsc_do_request(mdsc,
				   (flags & (O_CREAT|O_TRUNC)) ? dir : NULL,
				   req);
	err = ceph_handle_snapdir(req, dentry, err);
	if (err)
		goto out;
	if ((flags & O_CREAT) && !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);
	if (err)
		goto out;
	file = lookup_instantiate_filp(nd, req->r_dentry, ceph_open);
	if (IS_ERR(file))
		err = PTR_ERR(file);
out:
	ret = ceph_finish_lookup(req, dentry, err);
	ceph_mdsc_put_request(req);
	dout("ceph_lookup_open result=%p\n", ret);
	return ret;
}

int ceph_release(struct inode *inode, struct file *file)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_file_info *cf = file->private_data;

	dout("release inode %p file %p\n", inode, file);
	ceph_put_fmode(ci, cf->fmode);
	if (cf->last_readdir)
		ceph_mdsc_put_request(cf->last_readdir);
	kfree(cf->last_name);
	kfree(cf->dir_info);
	dput(cf->dentry);
	kmem_cache_free(ceph_file_cachep, cf);

	/* wake up anyone waiting for caps on this inode */
	wake_up_all(&ci->i_cap_wq);
	return 0;
}

/*
 * Read a range of bytes striped over one or more objects.  Iterate over
 * objects we stripe over.  (That's not atomic, but good enough for now.)
 *
 * If we get a short result from the OSD, check against i_size; we need to
 * only return a short read to the caller if we hit EOF.
 */
static int striped_read(struct inode *inode,
			u64 off, u64 len,
			struct page **pages, int num_pages,
			int *checkeof, bool o_direct,
			unsigned long buf_align)
{
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_inode_info *ci = ceph_inode(inode);
	u64 pos, this_len;
	int io_align, page_align;
	int left, pages_left;
	int read;
	struct page **page_pos;
	int ret;
	bool hit_stripe, was_short;

	/*
	 * we may need to do multiple reads.  not atomic, unfortunately.
	 */
	pos = off;
	left = len;
	page_pos = pages;
	pages_left = num_pages;
	read = 0;
	io_align = off & ~PAGE_MASK;

more:
	if (o_direct)
		page_align = (pos - io_align + buf_align) & ~PAGE_MASK;
	else
		page_align = pos & ~PAGE_MASK;
	this_len = left;
	ret = ceph_osdc_readpages(&fsc->client->osdc, ceph_vino(inode),
				  &ci->i_layout, pos, &this_len,
				  ci->i_truncate_seq,
				  ci->i_truncate_size,
				  page_pos, pages_left, page_align);
	if (ret == -ENOENT)
		ret = 0;
	hit_stripe = this_len < left;
	was_short = ret >= 0 && ret < this_len;
	dout("striped_read %llu~%u (read %u) got %d%s%s\n", pos, left, read,
	     ret, hit_stripe ? " HITSTRIPE" : "", was_short ? " SHORT" : "");

	if (ret > 0) {
		int didpages = (page_align + ret) >> PAGE_CACHE_SHIFT;

		if (read < pos - off) {
			dout(" zero gap %llu to %llu\n", off + read, pos);
			ceph_zero_page_vector_range(page_align + read,
						    pos - off - read, pages);
		}
		pos += ret;
		read = pos - off;
		left -= ret;
		page_pos += didpages;
		pages_left -= didpages;

		/* hit stripe? */
		if (left && hit_stripe)
			goto more;
	}

	if (was_short) {
		/* did we bounce off eof? */
		if (pos + left > inode->i_size)
			*checkeof = 1;

		/* zero trailing bytes (inside i_size) */
		if (left > 0 && pos < inode->i_size) {
			if (pos + left > inode->i_size)
				left = inode->i_size - pos;

			dout("zero tail %d\n", left);
			ceph_zero_page_vector_range(page_align + read, left,
						    pages);
			read += left;
		}
	}

	if (ret >= 0)
		ret = read;
	dout("striped_read returns %d\n", ret);
	return ret;
}

/*
 * Completely synchronous read and write methods.  Direct from __user
 * buffer to osd, or directly to user pages (if O_DIRECT).
 *
 * If the read spans object boundary, just do multiple reads.
 */
static ssize_t ceph_sync_read(struct file *file, char __user *data,
			      unsigned len, loff_t *poff, int *checkeof)
{
	struct inode *inode = file->f_dentry->d_inode;
	struct page **pages;
	u64 off = *poff;
	int num_pages, ret;

	dout("sync_read on file %p %llu~%u %s\n", file, off, len,
	     (file->f_flags & O_DIRECT) ? "O_DIRECT" : "");

	if (file->f_flags & O_DIRECT) {
		num_pages = calc_pages_for((unsigned long)data, len);
		pages = ceph_get_direct_page_vector(data, num_pages, true);
	} else {
		num_pages = calc_pages_for(off, len);
		pages = ceph_alloc_page_vector(num_pages, GFP_NOFS);
	}
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	/*
	 * flush any page cache pages in this range.  this
	 * will make concurrent normal and sync io slow,
	 * but it will at least behave sensibly when they are
	 * in sequence.
	 */
	ret = filemap_write_and_wait(inode->i_mapping);
	if (ret < 0)
		goto done;

	ret = striped_read(inode, off, len, pages, num_pages, checkeof,
			   file->f_flags & O_DIRECT,
			   (unsigned long)data & ~PAGE_MASK);

	if (ret >= 0 && (file->f_flags & O_DIRECT) == 0)
		ret = ceph_copy_page_vector_to_user(pages, data, off, ret);
	if (ret >= 0)
		*poff = off + ret;

done:
	if (file->f_flags & O_DIRECT)
		ceph_put_page_vector(pages, num_pages, true);
	else
		ceph_release_page_vector(pages, num_pages);
	dout("sync_read result %d\n", ret);
	return ret;
}

/*
 * Write commit callback, called if we requested both an ACK and
 * ONDISK commit reply from the OSD.
 */
static void sync_write_commit(struct ceph_osd_request *req,
			      struct ceph_msg *msg)
{
	struct ceph_inode_info *ci = ceph_inode(req->r_inode);

	dout("sync_write_commit %p tid %llu\n", req, req->r_tid);
	spin_lock(&ci->i_unsafe_lock);
	list_del_init(&req->r_unsafe_item);
	spin_unlock(&ci->i_unsafe_lock);
	ceph_put_cap_refs(ci, CEPH_CAP_FILE_WR);
}

/*
 * Synchronous write, straight from __user pointer or user pages (if
 * O_DIRECT).
 *
 * If write spans object boundary, just do multiple writes.  (For a
 * correct atomic write, we should e.g. take write locks on all
 * objects, rollback on failure, etc.)
 */
static ssize_t ceph_sync_write(struct file *file, const char __user *data,
			       size_t left, loff_t *offset)
{
	struct inode *inode = file->f_dentry->d_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_osd_request *req;
	struct page **pages;
	int num_pages;
	long long unsigned pos;
	u64 len;
	int written = 0;
	int flags;
	int do_sync = 0;
	int check_caps = 0;
	int page_align, io_align;
	unsigned long buf_align;
	int ret;
	struct timespec mtime = CURRENT_TIME;

	if (ceph_snap(file->f_dentry->d_inode) != CEPH_NOSNAP)
		return -EROFS;

	dout("sync_write on file %p %lld~%u %s\n", file, *offset,
	     (unsigned)left, (file->f_flags & O_DIRECT) ? "O_DIRECT" : "");

	if (file->f_flags & O_APPEND)
		pos = i_size_read(inode);
	else
		pos = *offset;

	ret = filemap_write_and_wait_range(inode->i_mapping, pos, pos + left);
	if (ret < 0)
		return ret;

	ret = invalidate_inode_pages2_range(inode->i_mapping,
					    pos >> PAGE_CACHE_SHIFT,
					    (pos + left) >> PAGE_CACHE_SHIFT);
	if (ret < 0)
		dout("invalidate_inode_pages2_range returned %d\n", ret);

	flags = CEPH_OSD_FLAG_ORDERSNAP |
		CEPH_OSD_FLAG_ONDISK |
		CEPH_OSD_FLAG_WRITE;
	if ((file->f_flags & (O_SYNC|O_DIRECT)) == 0)
		flags |= CEPH_OSD_FLAG_ACK;
	else
		do_sync = 1;

	/*
	 * we may need to do multiple writes here if we span an object
	 * boundary.  this isn't atomic, unfortunately.  :(
	 */
more:
	io_align = pos & ~PAGE_MASK;
	buf_align = (unsigned long)data & ~PAGE_MASK;
	len = left;
	if (file->f_flags & O_DIRECT) {
		/* write from beginning of first page, regardless of
		   io alignment */
		page_align = (pos - io_align + buf_align) & ~PAGE_MASK;
		num_pages = calc_pages_for((unsigned long)data, len);
	} else {
		page_align = pos & ~PAGE_MASK;
		num_pages = calc_pages_for(pos, len);
	}
	req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout,
				    ceph_vino(inode), pos, &len,
				    CEPH_OSD_OP_WRITE, flags,
				    ci->i_snap_realm->cached_context,
				    do_sync,
				    ci->i_truncate_seq, ci->i_truncate_size,
				    &mtime, false, 2, page_align);
	if (!req)
		return -ENOMEM;

	if (file->f_flags & O_DIRECT) {
		pages = ceph_get_direct_page_vector(data, num_pages, false);
		if (IS_ERR(pages)) {
			ret = PTR_ERR(pages);
			goto out;
		}

		/*
		 * throw out any page cache pages in this range. this
		 * may block.
		 */
		truncate_inode_pages_range(inode->i_mapping, pos,
					   (pos+len) | (PAGE_CACHE_SIZE-1));
	} else {
		pages = ceph_alloc_page_vector(num_pages, GFP_NOFS);
		if (IS_ERR(pages)) {
			ret = PTR_ERR(pages);
			goto out;
		}
		ret = ceph_copy_user_to_page_vector(pages, data, pos, len);
		if (ret < 0) {
			ceph_release_page_vector(pages, num_pages);
			goto out;
		}

		if ((file->f_flags & O_SYNC) == 0) {
			/* get a second commit callback */
			req->r_safe_callback = sync_write_commit;
			req->r_own_pages = 1;
		}
	}
	req->r_pages = pages;
	req->r_num_pages = num_pages;
	req->r_inode = inode;

	ret = ceph_osdc_start_request(&fsc->client->osdc, req, false);
	if (!ret) {
		if (req->r_safe_callback) {
			/*
			 * Add to inode unsafe list only after we
			 * start_request so that a tid has been assigned.
			 */
			spin_lock(&ci->i_unsafe_lock);
			list_add_tail(&req->r_unsafe_item,
				      &ci->i_unsafe_writes);
			spin_unlock(&ci->i_unsafe_lock);
			ceph_get_cap_refs(ci, CEPH_CAP_FILE_WR);
		}
		
		ret = ceph_osdc_wait_request(&fsc->client->osdc, req);
		if (ret < 0 && req->r_safe_callback) {
			spin_lock(&ci->i_unsafe_lock);
			list_del_init(&req->r_unsafe_item);
			spin_unlock(&ci->i_unsafe_lock);
			ceph_put_cap_refs(ci, CEPH_CAP_FILE_WR);
		}
	}

	if (file->f_flags & O_DIRECT)
		ceph_put_page_vector(pages, num_pages, false);
	else if (file->f_flags & O_SYNC)
		ceph_release_page_vector(pages, num_pages);

out:
	ceph_osdc_put_request(req);
	if (ret == 0) {
		pos += len;
		written += len;
		left -= len;
		data += written;
		if (left)
			goto more;

		ret = written;
		*offset = pos;
		if (pos > i_size_read(inode))
			check_caps = ceph_inode_set_size(inode, pos);
		if (check_caps)
			ceph_check_caps(ceph_inode(inode), CHECK_CAPS_AUTHONLY,
					NULL);
	}
	return ret;
}

/*
 * Wrap generic_file_aio_read with checks for cap bits on the inode.
 * Atomically grab references, so that those bits are not released
 * back to the MDS mid-read.
 *
 * Hmm, the sync read case isn't actually async... should it be?
 */
static ssize_t ceph_aio_read(struct kiocb *iocb, const struct iovec *iov,
			     unsigned long nr_segs, loff_t pos)
{
	struct file *filp = iocb->ki_filp;
	struct ceph_file_info *fi = filp->private_data;
	loff_t *ppos = &iocb->ki_pos;
	size_t len = iov->iov_len;
	struct inode *inode = filp->f_dentry->d_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
	void __user *base = iov->iov_base;
	ssize_t ret;
	int want, got = 0;
	int checkeof = 0, read = 0;

	dout("aio_read %p %llx.%llx %llu~%u trying to get caps on %p\n",
	     inode, ceph_vinop(inode), pos, (unsigned)len, inode);
again:
	__ceph_do_pending_vmtruncate(inode);
	if (fi->fmode & CEPH_FILE_MODE_LAZY)
		want = CEPH_CAP_FILE_CACHE | CEPH_CAP_FILE_LAZYIO;
	else
		want = CEPH_CAP_FILE_CACHE;
	ret = ceph_get_caps(ci, CEPH_CAP_FILE_RD, want, &got, -1);
	if (ret < 0)
		goto out;
	dout("aio_read %p %llx.%llx %llu~%u got cap refs on %s\n",
	     inode, ceph_vinop(inode), pos, (unsigned)len,
	     ceph_cap_string(got));

	if ((got & (CEPH_CAP_FILE_CACHE|CEPH_CAP_FILE_LAZYIO)) == 0 ||
	    (iocb->ki_filp->f_flags & O_DIRECT) ||
	    (inode->i_sb->s_flags & MS_SYNCHRONOUS) ||
	    (fi->flags & CEPH_F_SYNC))
		/* hmm, this isn't really async... */
		ret = ceph_sync_read(filp, base, len, ppos, &checkeof);
	else
		ret = generic_file_aio_read(iocb, iov, nr_segs, pos);

out:
	dout("aio_read %p %llx.%llx dropping cap refs on %s = %d\n",
	     inode, ceph_vinop(inode), ceph_cap_string(got), (int)ret);
	ceph_put_cap_refs(ci, got);

	if (checkeof && ret >= 0) {
		int statret = ceph_do_getattr(inode, CEPH_STAT_CAP_SIZE);

		/* hit EOF or hole? */
		if (statret == 0 && *ppos < inode->i_size) {
			dout("aio_read sync_read hit hole, ppos %lld < size %lld, reading more\n", *ppos, inode->i_size);
			read += ret;
			base += ret;
			len -= ret;
			checkeof = 0;
			goto again;
		}
	}
	if (ret >= 0)
		ret += read;

	return ret;
}

/*
 * Take cap references to avoid releasing caps to MDS mid-write.
 *
 * If we are synchronous, and write with an old snap context, the OSD
 * may return EOLDSNAPC.  In that case, retry the write.. _after_
 * dropping our cap refs and allowing the pending snap to logically
 * complete _before_ this write occurs.
 *
 * If we are near ENOSPC, write synchronously.
 */
static ssize_t ceph_aio_write(struct kiocb *iocb, const struct iovec *iov,
		       unsigned long nr_segs, loff_t pos)
{
	struct file *file = iocb->ki_filp;
	struct ceph_file_info *fi = file->private_data;
	struct inode *inode = file->f_dentry->d_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_osd_client *osdc =
		&ceph_sb_to_client(inode->i_sb)->client->osdc;
	loff_t endoff = pos + iov->iov_len;
	int want, got = 0;
	int ret, err;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return -EROFS;

retry_snap:
	if (ceph_osdmap_flag(osdc->osdmap, CEPH_OSDMAP_FULL))
		return -ENOSPC;
	__ceph_do_pending_vmtruncate(inode);
	dout("aio_write %p %llx.%llx %llu~%u getting caps. i_size %llu\n",
	     inode, ceph_vinop(inode), pos, (unsigned)iov->iov_len,
	     inode->i_size);
	if (fi->fmode & CEPH_FILE_MODE_LAZY)
		want = CEPH_CAP_FILE_BUFFER | CEPH_CAP_FILE_LAZYIO;
	else
		want = CEPH_CAP_FILE_BUFFER;
	ret = ceph_get_caps(ci, CEPH_CAP_FILE_WR, want, &got, endoff);
	if (ret < 0)
		goto out_put;

	dout("aio_write %p %llx.%llx %llu~%u  got cap refs on %s\n",
	     inode, ceph_vinop(inode), pos, (unsigned)iov->iov_len,
	     ceph_cap_string(got));

	if ((got & (CEPH_CAP_FILE_BUFFER|CEPH_CAP_FILE_LAZYIO)) == 0 ||
	    (iocb->ki_filp->f_flags & O_DIRECT) ||
	    (inode->i_sb->s_flags & MS_SYNCHRONOUS) ||
	    (fi->flags & CEPH_F_SYNC)) {
		ret = ceph_sync_write(file, iov->iov_base, iov->iov_len,
			&iocb->ki_pos);
	} else {
		/*
		 * buffered write; drop Fw early to avoid slow
		 * revocation if we get stuck on balance_dirty_pages
		 */
		int dirty;

		spin_lock(&ci->i_ceph_lock);
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_FILE_WR);
		spin_unlock(&ci->i_ceph_lock);
		ceph_put_cap_refs(ci, got);

		ret = generic_file_aio_write(iocb, iov, nr_segs, pos);
		if ((ret >= 0 || ret == -EIOCBQUEUED) &&
		    ((file->f_flags & O_SYNC) || IS_SYNC(file->f_mapping->host)
		     || ceph_osdmap_flag(osdc->osdmap, CEPH_OSDMAP_NEARFULL))) {
			err = vfs_fsync_range(file, pos, pos + ret - 1, 1);
			if (err < 0)
				ret = err;
		}

		if (dirty)
			__mark_inode_dirty(inode, dirty);
		goto out;
	}

	if (ret >= 0) {
		int dirty;
		spin_lock(&ci->i_ceph_lock);
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_FILE_WR);
		spin_unlock(&ci->i_ceph_lock);
		if (dirty)
			__mark_inode_dirty(inode, dirty);
	}

out_put:
	dout("aio_write %p %llx.%llx %llu~%u  dropping cap refs on %s\n",
	     inode, ceph_vinop(inode), pos, (unsigned)iov->iov_len,
	     ceph_cap_string(got));
	ceph_put_cap_refs(ci, got);

out:
	if (ret == -EOLDSNAPC) {
		dout("aio_write %p %llx.%llx %llu~%u got EOLDSNAPC, retrying\n",
		     inode, ceph_vinop(inode), pos, (unsigned)iov->iov_len);
		goto retry_snap;
	}

	return ret;
}

/*
 * llseek.  be sure to verify file size on SEEK_END.
 */
static loff_t ceph_llseek(struct file *file, loff_t offset, int origin)
{
	struct inode *inode = file->f_mapping->host;
	int ret;

	mutex_lock(&inode->i_mutex);
	__ceph_do_pending_vmtruncate(inode);

	if (origin == SEEK_END || origin == SEEK_DATA || origin == SEEK_HOLE) {
		ret = ceph_do_getattr(inode, CEPH_STAT_CAP_SIZE);
		if (ret < 0) {
			offset = ret;
			goto out;
		}
	}

	switch (origin) {
	case SEEK_END:
		offset += inode->i_size;
		break;
	case SEEK_CUR:
		/*
		 * Here we special-case the lseek(fd, 0, SEEK_CUR)
		 * position-querying operation.  Avoid rewriting the "same"
		 * f_pos value back to the file because a concurrent read(),
		 * write() or lseek() might have altered it
		 */
		if (offset == 0) {
			offset = file->f_pos;
			goto out;
		}
		offset += file->f_pos;
		break;
	case SEEK_DATA:
		if (offset >= inode->i_size) {
			ret = -ENXIO;
			goto out;
		}
		break;
	case SEEK_HOLE:
		if (offset >= inode->i_size) {
			ret = -ENXIO;
			goto out;
		}
		offset = inode->i_size;
		break;
	}

	if (offset < 0 || offset > inode->i_sb->s_maxbytes) {
		offset = -EINVAL;
		goto out;
	}

	/* Special lock needed here? */
	if (offset != file->f_pos) {
		file->f_pos = offset;
		file->f_version = 0;
	}

out:
	mutex_unlock(&inode->i_mutex);
	return offset;
}

const struct file_operations ceph_file_fops = {
	.open = ceph_open,
	.release = ceph_release,
	.llseek = ceph_llseek,
	.read = do_sync_read,
	.write = do_sync_write,
	.aio_read = ceph_aio_read,
	.aio_write = ceph_aio_write,
	.mmap = ceph_mmap,
	.fsync = ceph_fsync,
	.lock = ceph_lock,
	.flock = ceph_flock,
	.splice_read = generic_file_splice_read,
	.splice_write = generic_file_splice_write,
	.unlocked_ioctl = ceph_ioctl,
	.compat_ioctl	= ceph_ioctl,
};

