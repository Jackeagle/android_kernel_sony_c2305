/*
 * drivers/misc/logger.c
 *
 * A Logging Subsystem
 *
 * Copyright (C) 2007-2008 Google, Inc.
 *
 * Robert Love <rlove@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/sched.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <stdarg.h>

#include "logger.h"

#include <asm/ioctls.h>

#include <linux/proc_fs.h>

#define LOG_TS_FILE    "log_ts"

static int s_fake_read;

module_param_named(fake_read, s_fake_read, int, 0660);

int g_ts_switch = 0; // 0: android default timestamp; 1: kernel timestamp

/*
 * struct logger_log - represents a specific log, such as 'main' or 'radio'
 *
 * This structure lives from module insertion until module removal, so it does
 * not need additional reference counting. The structure is protected by the
 * mutex 'mutex'.
 */
struct logger_log {
	unsigned char		*buffer;/* the ring buffer itself */
	struct miscdevice	misc;	/* misc device representing the log */
	wait_queue_head_t	wq;	/* wait queue for readers */
	struct list_head	readers; /* this log's readers */
	struct mutex		mutex;	/* mutex protecting buffer */
	size_t			w_off;	/* current write head offset */
	size_t			head;	/* new readers start here */
	size_t			size;	/* size of the log */
  /* } */
};

/*
 * struct logger_reader - a logging device open for reading
 *
 * This object lives from open to release, so we don't need additional
 * reference counting. The structure is protected by log->mutex.
 */
struct logger_reader {
	struct logger_log	*log;	/* associated log */
	struct list_head	list;	/* entry in logger_log's list */
	size_t			r_off;	/* current read head offset */
	bool			r_all;	/* reader can read all entries */
	int			r_ver;	/* reader ABI version */

	size_t                  missing_bytes; /* android log missing warning */
  /* } */
};

/* logger_offset - returns index 'n' into the log via (optimized) modulus */
size_t logger_offset(struct logger_log *log, size_t n)
{
	return n & (log->size-1);
}


/*
 * file_get_log - Given a file structure, return the associated log
 *
 * This isn't aesthetic. We have several goals:
 *
 *	1) Need to quickly obtain the associated log during an I/O operation
 *	2) Readers need to maintain state (logger_reader)
 *	3) Writers need to be very fast (open() should be a near no-op)
 *
 * In the reader case, we can trivially go file->logger_reader->logger_log.
 * For a writer, we don't want to maintain a logger_reader, so we just go
 * file->logger_log. Thus what file->private_data points at depends on whether
 * or not the file was opened for reading. This function hides that dirtiness.
 */
static inline struct logger_log *file_get_log(struct file *file)
{
	if (file->f_mode & FMODE_READ) {
		struct logger_reader *reader = file->private_data;
		return reader->log;
	} else
		return file->private_data;
}

/*
 * get_entry_header - returns a pointer to the logger_entry header within
 * 'log' starting at offset 'off'. A temporary logger_entry 'scratch' must
 * be provided. Typically the return value will be a pointer within
 * 'logger->buf'.  However, a pointer to 'scratch' may be returned if
 * the log entry spans the end and beginning of the circular buffer.
 */
static struct logger_entry *get_entry_header(struct logger_log *log,
		size_t off, struct logger_entry *scratch)
{
	size_t len = min(sizeof(struct logger_entry), log->size - off);
	if (len != sizeof(struct logger_entry)) {
		memcpy(((void *) scratch), log->buffer + off, len);
		memcpy(((void *) scratch) + len, log->buffer,
			sizeof(struct logger_entry) - len);
		return scratch;
	}

	return (struct logger_entry *) (log->buffer + off);
}

/*
 * get_entry_msg_len - Grabs the length of the message of the entry
 * starting from from 'off'.
 *
 * An entry length is 2 bytes (16 bits) in host endian order.
 * In the log, the length does not include the size of the log entry structure.
 * This function returns the size including the log entry structure.
 *
 * Caller needs to hold log->mutex.
 */
static __u32 get_entry_msg_len(struct logger_log *log, size_t off)
{
	struct logger_entry scratch;
	struct logger_entry *entry;

	entry = get_entry_header(log, off, &scratch);
	return entry->len;
}

static size_t get_user_hdr_len(int ver)
{
	if (ver < 2)
		return sizeof(struct user_logger_entry_compat);
	else
		return sizeof(struct logger_entry);
}

static ssize_t copy_header_to_user(int ver, struct logger_entry *entry,
					 char __user *buf)
{
	void *hdr;
	size_t hdr_len;
	struct user_logger_entry_compat v1;

	if (ver < 2) {
		v1.len      = entry->len;
		v1.__pad    = 0;
		v1.pid      = entry->pid;
		v1.tid      = entry->tid;
		v1.sec      = entry->sec;
		v1.nsec     = entry->nsec;
		hdr         = &v1;
		hdr_len     = sizeof(struct user_logger_entry_compat);
	} else {
		hdr         = entry;
		hdr_len     = sizeof(struct logger_entry);
	}

	return copy_to_user(buf, hdr, hdr_len);
}

/*
 * do_read_log_to_user - reads exactly 'count' bytes from 'log' into the
 * user-space buffer 'buf'. Returns 'count' on success.
 *
 * Caller must hold log->mutex.
 */
static ssize_t do_read_log_to_user(struct logger_log *log,
				   struct logger_reader *reader,
				   char __user *buf,
				   size_t count)
{
	struct logger_entry scratch;
	struct logger_entry *entry;
	size_t len;
	size_t msg_start;

	/*
	 * First, copy the header to userspace, using the version of
	 * the header requested
	 */
	entry = get_entry_header(log, reader->r_off, &scratch);
	if (copy_header_to_user(reader->r_ver, entry, buf))
		return -EFAULT;

	count -= get_user_hdr_len(reader->r_ver);
	buf += get_user_hdr_len(reader->r_ver);
	msg_start = logger_offset(log,
		reader->r_off + sizeof(struct logger_entry));

	/*
	 * We read from the msg in two disjoint operations. First, we read from
	 * the current msg head offset up to 'count' bytes or to the end of
	 * the log, whichever comes first.
	 */
	len = min(count, log->size - msg_start);
	if (copy_to_user(buf, log->buffer + msg_start, len))
		return -EFAULT;

	/*
	 * Second, we read any remaining bytes, starting back at the head of
	 * the log.
	 */
	if (count != len)
		if (copy_to_user(buf + len, log->buffer, count - len))
			return -EFAULT;

	reader->r_off = logger_offset(log, reader->r_off +
		sizeof(struct logger_entry) + count);

	return count + get_user_hdr_len(reader->r_ver);
}

/*
 * get_next_entry_by_uid - Starting at 'off', returns an offset into
 * 'log->buffer' which contains the first entry readable by 'euid'
 */
static size_t get_next_entry_by_uid(struct logger_log *log,
		size_t off, uid_t euid)
{
	while (off != log->w_off) {
		struct logger_entry *entry;
		struct logger_entry scratch;
		size_t next_len;

		entry = get_entry_header(log, off, &scratch);

		if (entry->euid == euid)
			return off;

		next_len = sizeof(struct logger_entry) + entry->len;
		off = logger_offset(log, off + next_len);
	}

	return off;
}

/* for android log missing warning { */

static ssize_t logger_fake_message(struct logger_log *log, struct logger_reader *reader, char __user *buf, const char *fmt, ...) 
{
	int len, header_size, entry_len;
        char message[256], *tag;
	va_list ap;
	struct logger_entry *current_entry, scratch;
	
	header_size = get_user_hdr_len(reader->r_ver);

	current_entry = get_entry_header(log, reader->r_off, &scratch);

	memset(message, 0, header_size);
	va_start(ap, fmt);
        len = vsnprintf(message + header_size + 5, sizeof(message) - (header_size + 5), fmt, ap);
	va_end(ap);

	entry_len = 5 + len + 1/* message size */;
	tag = message + header_size;
	tag[0] = 0x5;
	tag[1] = 'A';
	tag[2] = 'E';
	tag[3] = 'E';
	tag[4] = 0;

	switch (reader->r_ver) {
	case 1: {
		struct user_logger_entry_compat *entryp = (struct user_logger_entry_compat *)message;
		entryp->sec = current_entry->sec;
		entryp->nsec = current_entry->nsec;
		entryp->len = entry_len;
		break;
	}
	case 2: {
		struct logger_entry *entryp = (struct logger_entry *)message;
		entryp->sec = current_entry->sec;
		entryp->nsec = current_entry->nsec;
		entryp->len = entry_len;
		entryp->hdr_size = header_size;
		break;
	}
	default:
		/* FIXME: ? */
		return 0;
		break;
	}

        if (copy_to_user(buf, message, entry_len + header_size))
		return -EFAULT;

	return entry_len + header_size;
}

/*
 * logger_read - our log's read() method
 *
 * Behavior:
 *
 *	- O_NONBLOCK works
 *	- If there are no log entries to read, blocks until log is written to
 *	- Atomically reads exactly one log entry
 *
 * Will set errno to EINVAL if read
 * buffer is insufficient to hold next entry.
 */
static ssize_t logger_read(struct file *file, char __user *buf,
			   size_t count, loff_t *pos)
{
	struct logger_reader *reader = file->private_data;
	struct logger_log *log = reader->log;
	ssize_t ret;
	DEFINE_WAIT(wait);

start:
	while (1) {
		mutex_lock(&log->mutex);

		prepare_to_wait(&log->wq, &wait, TASK_INTERRUPTIBLE);

		ret = (log->w_off == reader->r_off);
		mutex_unlock(&log->mutex);
		if (!ret)
			break;

		if (file->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			break;
		}

		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}

		schedule();
	}

	finish_wait(&log->wq, &wait);
	if (ret)
		return ret;

	mutex_lock(&log->mutex);

	if (!reader->r_all)
		reader->r_off = get_next_entry_by_uid(log,
			reader->r_off, current_euid());

	/* is there still something to read or did we race? */
	if (unlikely(log->w_off == reader->r_off)) {
		mutex_unlock(&log->mutex);
		goto start;
	}

	if (unlikely(s_fake_read)) {
		ret = logger_fake_message(log, reader, buf, "Fake read return string.");
		goto out;
	}

	/* for android log missing warning { */
	if (reader->missing_bytes > 0) {
		ret = logger_fake_message(log, reader, buf, "some logs have been lost (%u bytes estimated)", reader->missing_bytes);
		reader->missing_bytes = 0;
		goto out;
	}
	/* } */

	/* get the size of the next entry */
	ret = get_user_hdr_len(reader->r_ver) +
		get_entry_msg_len(log, reader->r_off);
	if (count < ret) {
		ret = -EINVAL;
		goto out;
	}

	/* get exactly one entry from the log */
	ret = do_read_log_to_user(log, reader, buf, ret);

out:
	mutex_unlock(&log->mutex);

	return ret;
}

/*
 * get_next_entry - return the offset of the first valid entry at least 'len'
 * bytes after 'off'.
 *
 * Caller must hold log->mutex.
 */
static size_t get_next_entry(struct logger_log *log, size_t off, size_t len)
{
	size_t count = 0;

	do {
		size_t nr = sizeof(struct logger_entry) +
			get_entry_msg_len(log, off);
		off = logger_offset(log, off + nr);
		count += nr;
	} while (count < len);

	return off;
}

/*
 * is_between - is a < c < b, accounting for wrapping of a, b, and c
 *    positions in the buffer
 *
 * That is, if a<b, check for c between a and b
 * and if a>b, check for c outside (not between) a and b
 *
 * |------- a xxxxxxxx b --------|
 *               c^
 *
 * |xxxxx b --------- a xxxxxxxxx|
 *    c^
 *  or                    c^
 */
static inline int is_between(size_t a, size_t b, size_t c)
{
	if (a < b) {
		/* is c between a and b? */
		if (a < c && c <= b)
			return 1;
	} else {
		/* is c outside of b through a? */
		if (c <= b || a < c)
			return 1;
	}

	return 0;
}

/*
 * fix_up_readers - walk the list of all readers and "fix up" any who were
 * lapped by the writer; also do the same for the default "start head".
 * We do this by "pulling forward" the readers and start head to the first
 * entry after the new write head.
 *
 * The caller needs to hold log->mutex.
 */
static void fix_up_readers(struct logger_log *log, size_t len)
{
	size_t old = log->w_off;
	size_t new = logger_offset(log, old + len);
	struct logger_reader *reader;

	if (is_between(old, new, log->head))
		log->head = get_next_entry(log, log->head, len);

	list_for_each_entry(reader, &log->readers, list)
		if (is_between(old, new, reader->r_off)) {
			size_t old_r_off = reader->r_off;
			reader->r_off = get_next_entry(log, reader->r_off, len);
			if (reader->r_off >= old_r_off) {
				reader->missing_bytes += (reader->r_off - old_r_off);
			}
			else {
				reader->missing_bytes += (reader->r_off + (log->size - old_r_off));
			}
		}
}

/*
 * do_write_log - writes 'len' bytes from 'buf' to 'log'
 *
 * The caller needs to hold log->mutex.
 */
static void do_write_log(struct logger_log *log, const void *buf, size_t count)
{
	size_t len;

	len = min(count, log->size - log->w_off);
	memcpy(log->buffer + log->w_off, buf, len);

	if (count != len)
		memcpy(log->buffer, buf + len, count - len);

	log->w_off = logger_offset(log, log->w_off + count);
}

/*
 * do_write_log_user - writes 'len' bytes from the user-space buffer 'buf' to
 * the log 'log'
 *
 * The caller needs to hold log->mutex.
 *
 * Returns 'count' on success, negative error code on failure.
 */
static ssize_t do_write_log_from_user(struct logger_log *log,
				      const void __user *buf, size_t count)
{
	size_t len;

	len = min(count, log->size - log->w_off);
	if (len && copy_from_user(log->buffer + log->w_off, buf, len))
		return -EFAULT;

	if (count != len)
		if (copy_from_user(log->buffer, buf + len, count - len))
			/*
			 * Note that by not updating w_off, this abandons the
			 * portion of the new entry that *was* successfully
			 * copied, just above.  This is intentional to avoid
			 * message corruption from missing fragments.
			 */
			return -EFAULT;

	log->w_off = logger_offset(log, log->w_off + count);
  
	return count;
}

/*
 * logger_aio_write - our write method, implementing support for write(),
 * writev(), and aio_write(). Writes are our fast path, and we try to optimize
 * them above all else.
 */
ssize_t logger_aio_write(struct kiocb *iocb, const struct iovec *iov,
			 unsigned long nr_segs, loff_t ppos)
{
	struct logger_log *log = file_get_log(iocb->ki_filp);
	size_t orig = log->w_off;
	struct logger_entry header;
	struct timespec now;
	ssize_t ret = 0;
	
/* make android timestamp same with printk {*/
	if (g_ts_switch == 0) {
		// android default timestamp
		//now = current_kernel_time();
		getnstimeofday(&now);
		header.pid = current->tgid;
		header.tid = current->pid;
		header.sec = now.tv_sec;
		header.nsec = now.tv_nsec;
		header.euid = current_euid();
		header.len = min_t(size_t, iocb->ki_left, LOGGER_ENTRY_MAX_PAYLOAD);
		header.hdr_size = sizeof(struct logger_entry);

	} 
	else {
		// use kernel timestamp
		unsigned long long t;
		unsigned long nanosec_rem;
		
		t = cpu_clock(UINT_MAX);
		nanosec_rem = do_div(t, 1000000000);

		header.pid = current->tgid;
		header.tid = current->pid;
		header.sec = (unsigned long)t;
		header.nsec = nanosec_rem;
		header.euid = current_euid();
		header.len = min_t(size_t, iocb->ki_left, LOGGER_ENTRY_MAX_PAYLOAD);
		header.hdr_size = sizeof(struct logger_entry);
	}
/* } */
	
	/* null writes succeed, return zero */
	if (unlikely(!header.len))
		return 0;

	mutex_lock(&log->mutex);

	/*
	 * Fix up any readers, pulling them forward to the first readable
	 * entry after (what will be) the new write offset. We do this now
	 * because if we partially fail, we can end up with clobbered log
	 * entries that encroach on readable buffer.
	 */
	fix_up_readers(log, sizeof(struct logger_entry) + header.len);

	do_write_log(log, &header, sizeof(struct logger_entry));

	while (nr_segs-- > 0) {
		size_t len;
		ssize_t nr;

		/* figure out how much of this vector we can keep */
		len = min_t(size_t, iov->iov_len, header.len - ret);

		/* write out this segment's payload */
		nr = do_write_log_from_user(log, iov->iov_base, len);
		if (unlikely(nr < 0)) {
			log->w_off = orig;
			mutex_unlock(&log->mutex);
			return nr;
		}

		iov++;
		ret += nr;
	}

	mutex_unlock(&log->mutex);

	/* wake up any blocked readers */
	wake_up_interruptible(&log->wq);

	return ret;
}

static struct logger_log *get_log_from_minor(int);

/*
 * logger_open - the log's open() file operation
 *
 * Note how near a no-op this is in the write-only case. Keep it that way!
 */
static int logger_open(struct inode *inode, struct file *file)
{
	struct logger_log *log;
	int ret;

	ret = nonseekable_open(inode, file);
	if (ret)
		return ret;

	log = get_log_from_minor(MINOR(inode->i_rdev));
	if (!log)
		return -ENODEV;

	if (file->f_mode & FMODE_READ) {
		struct logger_reader *reader;

		reader = kmalloc(sizeof(struct logger_reader), GFP_KERNEL);
		if (!reader)
			return -ENOMEM;

		reader->log = log;
		reader->r_ver = 1;
		reader->r_all = in_egroup_p(inode->i_gid) ||
			capable(CAP_SYSLOG);
		reader->missing_bytes = 0;

		INIT_LIST_HEAD(&reader->list);

		mutex_lock(&log->mutex);
		reader->r_off = log->head;

		list_add_tail(&reader->list, &log->readers);
		mutex_unlock(&log->mutex);

		file->private_data = reader;
	} else
		file->private_data = log;

	return 0;
}

/*
 * logger_release - the log's release file operation
 *
 * Note this is a total no-op in the write-only case. Keep it that way!
 */
static int logger_release(struct inode *ignored, struct file *file)
{
	if (file->f_mode & FMODE_READ) {
		struct logger_reader *reader = file->private_data;
		struct logger_log *log = reader->log;

		mutex_lock(&log->mutex);
		list_del(&reader->list);
		mutex_unlock(&log->mutex);

		kfree(reader);
	}

	return 0;
}

/*
 * logger_poll - the log's poll file operation, for poll/select/epoll
 *
 * Note we always return POLLOUT, because you can always write() to the log.
 * Note also that, strictly speaking, a return value of POLLIN does not
 * guarantee that the log is readable without blocking, as there is a small
 * chance that the writer can lap the reader in the interim between poll()
 * returning and the read() request.
 */
static unsigned int logger_poll(struct file *file, poll_table *wait)
{
	struct logger_reader *reader;
	struct logger_log *log;
	unsigned int ret = POLLOUT | POLLWRNORM;

	if (!(file->f_mode & FMODE_READ))
		return ret;

	reader = file->private_data;
	log = reader->log;

	poll_wait(file, &log->wq, wait);

	mutex_lock(&log->mutex);
	if (!reader->r_all)
		reader->r_off = get_next_entry_by_uid(log,
			reader->r_off, current_euid());

	if (log->w_off != reader->r_off)
		ret |= POLLIN | POLLRDNORM;
	mutex_unlock(&log->mutex);

	return ret;
}

static long logger_set_version(struct logger_reader *reader, void __user *arg)
{
	int version;
	if (copy_from_user(&version, arg, sizeof(int)))
		return -EFAULT;

	if ((version < 1) || (version > 2))
		return -EINVAL;

	reader->r_ver = version;
	return 0;
}

static long logger_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct logger_log *log = file_get_log(file);
	struct logger_reader *reader;
	long ret = -EINVAL;
	void __user *argp = (void __user *) arg;

	mutex_lock(&log->mutex);

	switch (cmd) {
	case LOGGER_GET_LOG_BUF_SIZE:
		ret = log->size;
		break;
	case LOGGER_GET_LOG_LEN:
		if (!(file->f_mode & FMODE_READ)) {
			ret = -EBADF;
			break;
		}
		reader = file->private_data;
		if (log->w_off >= reader->r_off)
			ret = log->w_off - reader->r_off;
		else
			ret = (log->size - reader->r_off) + log->w_off;
		break;
	case LOGGER_GET_NEXT_ENTRY_LEN:
		if (!(file->f_mode & FMODE_READ)) {
			ret = -EBADF;
			break;
		}
		reader = file->private_data;

		if (!reader->r_all)
			reader->r_off = get_next_entry_by_uid(log,
				reader->r_off, current_euid());

		if (log->w_off != reader->r_off)
			ret = get_user_hdr_len(reader->r_ver) +
				get_entry_msg_len(log, reader->r_off);
		else
			ret = 0;
		break;
	case LOGGER_FLUSH_LOG:
		if (!(file->f_mode & FMODE_WRITE)) {
			ret = -EBADF;
			break;
		}
		if (!(in_egroup_p(file->f_dentry->d_inode->i_gid) ||
				capable(CAP_SYSLOG))) {
			ret = -EPERM;
			break;
		}
		list_for_each_entry(reader, &log->readers, list)
			reader->r_off = log->w_off;
		log->head = log->w_off;
		ret = 0;
		break;
	case LOGGER_GET_VERSION:
		if (!(file->f_mode & FMODE_READ)) {
			ret = -EBADF;
			break;
		}
		reader = file->private_data;
		ret = reader->r_ver;
		break;
	case LOGGER_SET_VERSION:
		if (!(file->f_mode & FMODE_READ)) {
			ret = -EBADF;
			break;
		}
		reader = file->private_data;
		ret = logger_set_version(reader, argp);
		break;
	}

	mutex_unlock(&log->mutex);

	return ret;
}

static const struct file_operations logger_fops = {
	.owner = THIS_MODULE,
	.read = logger_read,
	.aio_write = logger_aio_write,
	.poll = logger_poll,
	.unlocked_ioctl = logger_ioctl,
	.compat_ioctl = logger_ioctl,
	.open = logger_open,
	.release = logger_release,
};

/*
 * Defines a log structure with name 'NAME' and a size of 'SIZE' bytes, which
 * must be a power of two, and greater than
 * (LOGGER_ENTRY_MAX_PAYLOAD + sizeof(struct logger_entry)).
 */
#define DEFINE_LOGGER_DEVICE(VAR, NAME, SIZE) \
static unsigned char _buf_ ## VAR[SIZE]; \
static struct logger_log VAR = { \
	.buffer = _buf_ ## VAR, \
	.misc = { \
		.minor = MISC_DYNAMIC_MINOR, \
		.name = NAME, \
		.fops = &logger_fops, \
		.parent = NULL, \
	}, \
	.wq = __WAIT_QUEUE_HEAD_INITIALIZER(VAR .wq), \
	.readers = LIST_HEAD_INIT(VAR .readers), \
	.mutex = __MUTEX_INITIALIZER(VAR .mutex), \
	.w_off = 0, \
	.head = 0, \
	.size = SIZE, \
};


DEFINE_LOGGER_DEVICE(log_main, LOGGER_LOG_MAIN, __MAIN_BUF_SIZE)
DEFINE_LOGGER_DEVICE(log_events, LOGGER_LOG_EVENTS, __EVENTS_BUF_SIZE)
DEFINE_LOGGER_DEVICE(log_radio, LOGGER_LOG_RADIO, __RADIO_BUF_SIZE)
DEFINE_LOGGER_DEVICE(log_system, LOGGER_LOG_SYSTEM, __SYSTEM_BUF_SIZE)

static struct logger_log *get_log_from_minor(int minor)
{
	if (log_main.misc.minor == minor)
		return &log_main;
	if (log_events.misc.minor == minor)
		return &log_events;
	if (log_radio.misc.minor == minor)
		return &log_radio;
	if (log_system.misc.minor == minor)
		return &log_system;
	return NULL;
}

static int ts_switch_read(char *page, char **start, off_t off,
			       int count, int *eof, void *data)
{
    char *p = page;
    int len = 0;

	//printk(KERN_INFO "logger: ts_switch_read\n");

	p += sprintf(p, "%d\n",g_ts_switch);

    *start = page + off;

    len = p - page;
    if (len > off)
        len -= off;
    else
        len = 0;

    return len < count ? len  : count;
}

static int ts_switch_write (struct file *file, const char *buffer,
					unsigned long count, void *data)
{
	char ts_switch = 0;

	if(copy_from_user((void *)&ts_switch, (const void __user *)buffer, sizeof(char))) {
		printk(KERN_ERR "logger: ts_switch_write copy_from_user fails\n");
		return 0;
	}

	//printk(KERN_INFO "logger: ts_switch_write ts_switch = %d\n", ts_switch);
	switch(ts_switch) {
	case '0':
		g_ts_switch = 0;
		printk(KERN_INFO "logger: ts_switch_write g_ts_switch == 0\n");
		break;
	case '1':
		g_ts_switch = 1;
		printk(KERN_INFO "logger: ts_switch_write g_ts_switch == 1\n");
		break;
	default:
		printk(KERN_ERR "logger: ts_switch_write incorrect parameter\n");
		break;
	}

    return count;
}

static void init_log_proc(void)
{
	struct proc_dir_entry *ts_switch_file;
	g_ts_switch = 0; // using android default log timestamp
	
	ts_switch_file = create_proc_entry(LOG_TS_FILE, 0, NULL);
	if (ts_switch_file) {
		ts_switch_file->read_proc = ts_switch_read;
		ts_switch_file->write_proc = ts_switch_write;
	} 
	else
		printk(KERN_ERR "xlog: init_log_proc create_proc_entry fails\n");
}

static int __init init_log(struct logger_log *log)
{
	int ret;

	ret = misc_register(&log->misc);
	if (unlikely(ret)) {
		printk(KERN_ERR "logger: failed to register misc "
		       "device for log '%s'!\n", log->misc.name);
		return ret;
	}

	printk(KERN_INFO "logger: created %luK log '%s'\n",
	       (unsigned long) log->size >> 10, log->misc.name);

	return 0;
}

static int __init logger_init(void)
{
	int ret;

	ret = init_log(&log_main);
	if (unlikely(ret))
		goto out;

	ret = init_log(&log_events);
	if (unlikely(ret))
		goto out;

	ret = init_log(&log_radio);
	if (unlikely(ret))
		goto out;

	ret = init_log(&log_system);
	if (unlikely(ret))
		goto out;

	init_log_proc();

out:
	return ret;
}

int panic_dump_main(char *buf, size_t size) {
	static size_t offset = 0; //offset of log buffer
	static int isFirst = 0;
	size_t len = 0;
	size_t distance = 0;
	size_t realsize = 0;
	if (isFirst == 0){
		offset = log_main.head;
		isFirst++;
	}
	distance = (log_main.w_off + log_main.size - offset) & (log_main.size -1);
	//printk("offset = %d, w_off = %d, head = %d distance = %d\n", offset, log_main.w_off, log_main.head, distance);
	if(distance > size)
		realsize = size;
	else
		realsize = distance;
	len = min(realsize, log_main.size - offset);
	memcpy(buf, log_main.buffer + offset, len);
	if (realsize != len)
		memcpy(buf + len, log_main.buffer, realsize - len);
	offset += realsize;
	offset &= (log_main.size - 1);
	return realsize;
}

int panic_dump_events(char *buf, size_t size) {
	static size_t offset = 0; //offset of log buffer
	static int isFirst = 0;
	size_t len = 0;
	size_t distance = 0;
	size_t realsize = 0;
	if (isFirst == 0){
		offset = log_events.head;
		isFirst++;
	}
	distance = (log_events.w_off + log_events.size - offset) & (log_events.size -1);
	//printk("offset = %d, w_off = %d, head = %d distance = %d\n", offset, log_events.w_off, log_events.head, distance);
	if(distance > size)
		realsize = size;
	else
		realsize = distance;	
	len = min(realsize, log_events.size - offset);
	memcpy(buf, log_events.buffer + offset, len);
	if (realsize != len)
		memcpy(buf + len, log_events.buffer, realsize - len);
	offset += realsize;
	offset &= (log_events.size - 1);
	return realsize;
}

int panic_dump_radio(char *buf, size_t size) {
	static size_t offset = 0; //offset of log buffer
	static int isFirst = 0;
	size_t len = 0;
	size_t distance = 0;
	size_t realsize = 0;
	if (isFirst == 0){
		offset = log_radio.head;
		isFirst++;
	}
	distance = (log_radio.w_off + log_radio.size - offset) & (log_radio.size -1);
	//printk("offset = %d, w_off = %d, head = %d distance = %d\n", offset, log_radio.w_off, log_radio.head, distance);
	if(distance > size)
		realsize = size;
	else
		realsize = distance;
	len = min(realsize, log_radio.size - offset);
	memcpy(buf, log_radio.buffer + offset, len);
	if (realsize != len)
		memcpy(buf + len, log_radio.buffer, realsize - len);
	offset += realsize;
	offset &= (log_radio.size - 1);
	return realsize;
}

int panic_dump_system(char *buf, size_t size) {
	static size_t offset = 0; //offset of log buffer
	static int isFirst = 0;
	size_t len = 0;
	size_t distance = 0;
	size_t realsize = 0;
	if (isFirst == 0){
		offset = log_system.head;
		isFirst++;
	}
	distance = (log_system.w_off + log_system.size - offset) & (log_system.size -1);
	//printk("offset = %d, w_off = %d, head = %d distance = %d\n", offset, log_system.w_off, log_system.head, distance);
	if(distance > size)
		realsize = size;
	else
		realsize = distance;
	len = min(realsize, log_system.size - offset);
	memcpy(buf, log_system.buffer + offset, len);
	if (realsize != len)
		memcpy(buf + len, log_system.buffer, realsize - len);
	offset += realsize;
	offset &= (log_system.size - 1);
	return realsize;
}


int panic_dump_android_log(char *buf, size_t size, int type)
{
	size_t ret = 0 ;
	//printk ("type %d, buf %x, size %d\n", type, buf, size) ;
	memset (buf, 0, size);
	switch (type)
	{
        case 1:
		ret = panic_dump_main(buf, size);
		break;
        case 2:
		ret = panic_dump_events(buf, size);
		break;
        case 3:
		ret = panic_dump_radio(buf, size);
		break;
        case 4:
		ret = panic_dump_system(buf, size);
		break;
        default:
		ret = 0;
		break;
    }
    if (ret!=0)
	    ret = size;
	
    return ret;
}

device_initcall(logger_init);
