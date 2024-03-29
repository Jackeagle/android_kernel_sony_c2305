/*
 * ZIO Motherboard USB driver
 *
 * Copyright (C) 2010 Zilogic Systems <code@zilogic.com>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License version
 *	2 as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/usb/serial.h>
#include <linux/uaccess.h>

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(0x1CBE, 0x0103) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_driver zio_driver = {
	.name =		"zio",
	.probe =	usb_serial_probe,
	.disconnect =	usb_serial_disconnect,
	.id_table =	id_table,
};

static struct usb_serial_driver zio_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"zio",
	},
	.id_table =		id_table,
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&zio_device, NULL
};

module_usb_serial_driver(zio_driver, serial_drivers);
MODULE_LICENSE("GPL");
