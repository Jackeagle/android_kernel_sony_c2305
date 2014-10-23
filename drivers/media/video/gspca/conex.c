/*
 *		Connexant Cx11646 library
 *		Copyright (C) 2004 Michel Xhaard mxhaard@magic.fr
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.free.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#define MODULE_NAME "conex"

#include "gspca.h"
#define CONEX_CAM 1		/* special JPEG header */
#include "jpeg.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("GSPCA USB Conexant Camera Driver");
MODULE_LICENSE("GPL");

/* specific webcam descriptor */
struct sd {
	struct gspca_dev gspca_dev;	/* !! must be the first item */

	unsigned char brightness;
	unsigned char contrast;
	unsigned char colors;
	u8 quality;
#define QUALITY_MIN 30
#define QUALITY_MAX 60
#define QUALITY_DEF 40

	u8 jpeg_hdr[JPEG_HDR_SZ];
};

/* V4L2 controls supported by the driver */
static int sd_setbrightness(struct gspca_dev *gspca_dev, __s32 val);
static int sd_getbrightness(struct gspca_dev *gspca_dev, __s32 *val);
static int sd_setcontrast(struct gspca_dev *gspca_dev, __s32 val);
static int sd_getcontrast(struct gspca_dev *gspca_dev, __s32 *val);
static int sd_setcolors(struct gspca_dev *gspca_dev, __s32 val);
static int sd_getcolors(struct gspca_dev *gspca_dev, __s32 *val);

static const struct ctrl sd_ctrls[] = {
	{
	    {
		.id	 = V4L2_CID_BRIGHTNESS,
		.type	 = V4L2_CTRL_TYPE_INTEGER,
		.name	 = "Brightness",
		.minimum = 0,
		.maximum = 255,
		.step	 = 1,
#define BRIGHTNESS_DEF 0xd4
		.default_value = BRIGHTNESS_DEF,
	    },
	    .set = sd_setbrightness,
	    .get = sd_getbrightness,
	},
	{
	    {
		.id      = V4L2_CID_CONTRAST,
		.type    = V4L2_CTRL_TYPE_INTEGER,
		.name    = "Contrast",
		.minimum = 0x0a,
		.maximum = 0x1f,
		.step    = 1,
#define CONTRAST_DEF 0x0c
		.default_value = CONTRAST_DEF,
	    },
	    .set = sd_setcontrast,
	    .get = sd_getcontrast,
	},
	{
	    {
		.id      = V4L2_CID_SATURATION,
		.type    = V4L2_CTRL_TYPE_INTEGER,
		.name    = "Color",
		.minimum = 0,
		.maximum = 7,
		.step    = 1,
#define COLOR_DEF 3
		.default_value = COLOR_DEF,
	    },
	    .set = sd_setcolors,
	    .get = sd_getcolors,
	},
};

static const struct v4l2_pix_format vga_mode[] = {
	{176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3},
	{320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2},
	{352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1},
	{640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0},
};

/* the read bytes are found in gspca_dev->usb_buf */
static void reg_r(struct gspca_dev *gspca_dev,
		  __u16 index,
		  __u16 len)
{
	struct usb_device *dev = gspca_dev->dev;

#ifdef GSPCA_DEBUG
	if (len > USB_BUF_SZ) {
		pr_err("reg_r: buffer overflow\n");
		return;
	}
#endif
	usb_control_msg(dev,
			usb_rcvctrlpipe(dev, 0),
			0,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,
			index, gspca_dev->usb_buf, len,
			500);
	PDEBUG(D_USBI, "reg read [%02x] -> %02x ..",
			index, gspca_dev->usb_buf[0]);
}

/* the bytes to write are in gspca_dev->usb_buf */
static void reg_w_val(struct gspca_dev *gspca_dev,
			__u16 index,
			__u8 val)
{
	struct usb_device *dev = gspca_dev->dev;

	gspca_dev->usb_buf[0] = val;
	usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			0,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,
			index, gspca_dev->usb_buf, 1, 500);
}

static void reg_w(struct gspca_dev *gspca_dev,
		  __u16 index,
		  const __u8 *buffer,
		  __u16 len)
{
	struct usb_device *dev = gspca_dev->dev;

#ifdef GSPCA_DEBUG
	if (len > USB_BUF_SZ) {
		pr_err("reg_w: buffer overflow\n");
		return;
	}
	PDEBUG(D_USBO, "reg write [%02x] = %02x..", index, *buffer);
#endif
	memcpy(gspca_dev->usb_buf, buffer, len);
	usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			0,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,
			index, gspca_dev->usb_buf, len, 500);
}

static const __u8 cx_sensor_init[][4] = {
	{0x88, 0x11, 0x01, 0x01},
	{0x88, 0x12, 0x70, 0x01},
	{0x88, 0x0f, 0x00, 0x01},
	{0x88, 0x05, 0x01, 0x01},
	{}
};

static const __u8 cx11646_fw1[][3] = {
	{0x00, 0x02, 0x00},
	{0x01, 0x43, 0x00},
	{0x02, 0xA7, 0x00},
	{0x03, 0x8B, 0x01},
	{0x04, 0xE9, 0x02},
	{0x05, 0x08, 0x04},
	{0x06, 0x08, 0x05},
	{0x07, 0x07, 0x06},
	{0x08, 0xE7, 0x06},
	{0x09, 0xC6, 0x07},
	{0x0A, 0x86, 0x08},
	{0x0B, 0x46, 0x09},
	{0x0C, 0x05, 0x0A},
	{0x0D, 0xA5, 0x0A},
	{0x0E, 0x45, 0x0B},
	{0x0F, 0xE5, 0x0B},
	{0x10, 0x85, 0x0C},
	{0x11, 0x25, 0x0D},
	{0x12, 0xC4, 0x0D},
	{0x13, 0x45, 0x0E},
	{0x14, 0xE4, 0x0E},
	{0x15, 0x64, 0x0F},
	{0x16, 0xE4, 0x0F},
	{0x17, 0x64, 0x10},
	{0x18, 0xE4, 0x10},
	{0x19, 0x64, 0x11},
	{0x1A, 0xE4, 0x11},
	{0x1B, 0x64, 0x12},
	{0x1C, 0xE3, 0x12},
	{0x1D, 0x44, 0x13},
	{0x1E, 0xC3, 0x13},
	{0x1F, 0x24, 0x14},
	{0x20, 0xA3, 0x14},
	{0x21, 0x04, 0x15},
	{0x22, 0x83, 0x15},
	{0x23, 0xE3, 0x15},
	{0x24, 0x43, 0x16},
	{0x25, 0xA4, 0x16},
	{0x26, 0x23, 0x17},
	{0x27, 0x83, 0x17},
	{0x28, 0xE3, 0x17},
	{0x29, 0x43, 0x18},
	{0x2A, 0xA3, 0x18},
	{0x2B, 0x03, 0x19},
	{0x2C, 0x63, 0x19},
	{0x2D, 0xC3, 0x19},
	{0x2E, 0x22, 0x1A},
	{0x2F, 0x63, 0x1A},
	{0x30, 0xC3, 0x1A},
	{0x31, 0x23, 0x1B},
	{0x32, 0x83, 0x1B},
	{0x33, 0xE2, 0x1B},
	{0x34, 0x23, 0x1C},
	{0x35, 0x83, 0x1C},
	{0x36, 0xE2, 0x1C},
	{0x37, 0x23, 0x1D},
	{0x38, 0x83, 0x1D},
	{0x39, 0xE2, 0x1D},
	{0x3A, 0x23, 0x1E},
	{0x3B, 0x82, 0x1E},
	{0x3C, 0xC3, 0x1E},
	{0x3D, 0x22, 0x1F},
	{0x3E, 0x63, 0x1F},
	{0x3F, 0xC1, 0x1F},
	{}
};
static void cx11646_fw(struct gspca_dev*gspca_dev)
{
	int i = 0;

	reg_w_val(gspca_dev, 0x006a, 0x02);
	while (cx11646_fw1[i][1]) {
		reg_w(gspca_dev, 0x006b, cx11646_fw1[i], 3);
		i++;
	}
	reg_w_val(gspca_dev, 0x006a, 0x00);
}

static const __u8 cxsensor[] = {
	0x88, 0x12, 0x70, 0x01,
	0x88, 0x0d, 0x02, 0x01,
	0x88, 0x0f, 0x00, 0x01,
	0x88, 0x03, 0x71, 0x01, 0x88, 0x04, 0x00, 0x01,	/* 3 */
	0x88, 0x02, 0x10, 0x01,
	0x88, 0x00, 0xD4, 0x01, 0x88, 0x01, 0x01, 0x01,	/* 5 */
	0x88, 0x0B, 0x00, 0x01,
	0x88, 0x0A, 0x0A, 0x01,
	0x88, 0x00, 0x08, 0x01, 0x88, 0x01, 0x00, 0x01,	/* 8 */
	0x88, 0x05, 0x01, 0x01,
	0xA1, 0x18, 0x00, 0x01,
	0x00
};

static const __u8 reg20[] = { 0x10, 0x42, 0x81, 0x19, 0xd3, 0xff, 0xa7, 0xff };
static const __u8 reg28[] = { 0x87, 0x00, 0x87, 0x00, 0x8f, 0xff, 0xea, 0xff };
static const __u8 reg10[] = { 0xb1, 0xb1 };
static const __u8 reg71a[] = { 0x08, 0x18, 0x0a, 0x1e };	/* 640 */
static const __u8 reg71b[] = { 0x04, 0x0c, 0x05, 0x0f };
	/* 352{0x04,0x0a,0x06,0x12}; //352{0x05,0x0e,0x06,0x11}; //352 */
static const __u8 reg71c[] = { 0x02, 0x07, 0x03, 0x09 };
					/* 320{0x04,0x0c,0x05,0x0f}; //320 */
static const __u8 reg71d[] = { 0x02, 0x07, 0x03, 0x09 };	/* 176 */
static const __u8 reg7b[] = { 0x00, 0xff, 0x00, 0xff, 0x00, 0xff };

static void cx_sensor(struct gspca_dev*gspca_dev)
{
	int i = 0;
	int length;
	const __u8 *ptsensor = cxsensor;

	reg_w(gspca_dev, 0x0020, reg20, 8);
	reg_w(gspca_dev, 0x0028, reg28, 8);
	reg_w(gspca_dev, 0x0010, reg10, 8);
	reg_w_val(gspca_dev, 0x0092, 0x03);

	switch (gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv) {
	case 0:
		reg_w(gspca_dev, 0x0071, reg71a, 4);
		break;
	case 1:
		reg_w(gspca_dev, 0x0071, reg71b, 4);
		break;
	default:
/*	case 2: */
		reg_w(gspca_dev, 0x0071, reg71c, 4);
		break;
	case 3:
		reg_w(gspca_dev, 0x0071, reg71d, 4);
		break;
	}
	reg_w(gspca_dev, 0x007b, reg7b, 6);
	reg_w_val(gspca_dev, 0x00f8, 0x00);
	reg_w(gspca_dev, 0x0010, reg10, 8);
	reg_w_val(gspca_dev, 0x0098, 0x41);
	for (i = 0; i < 11; i++) {
		if (i == 3 || i == 5 || i == 8)
			length = 8;
		else
			length = 4;
		reg_w(gspca_dev, 0x00e5, ptsensor, length);
		if (length == 4)
			reg_r(gspca_dev, 0x00e8, 1);
		else
			reg_r(gspca_dev, 0x00e8, length);
		ptsensor += length;
	}
	reg_r(gspca_dev, 0x00e7, 8);
}

static const __u8 cx_inits_176[] = {
	0x33, 0x81, 0xB0, 0x00, 0x90, 0x00, 0x0A, 0x03,	/* 176x144 */
	0x00, 0x03, 0x03, 0x03, 0x1B, 0x05, 0x30, 0x03,
	0x65, 0x15, 0x18, 0x25, 0x03, 0x25, 0x08, 0x30,
	0x3B, 0x25, 0x10, 0x00, 0x04, 0x00, 0x00, 0x00,
	0xDC, 0xFF, 0xEE, 0xFF, 0xC5, 0xFF, 0xBF, 0xFF,
	0xF7, 0xFF, 0x88, 0xFF, 0x66, 0x02, 0x28, 0x02,
	0x1E, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const __u8 cx_inits_320[] = {
	0x7f, 0x7f, 0x40, 0x01, 0xf0, 0x00, 0x02, 0x01,
	0x00, 0x01, 0x01, 0x01, 0x10, 0x00, 0x02, 0x01,
	0x65, 0x45, 0xfa, 0x4c, 0x2c, 0xdf, 0xb9, 0x81,
	0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0xe2, 0xff, 0xf1, 0xff, 0xc2, 0xff, 0xbc, 0xff,
	0xf5, 0xff, 0x6d, 0xff, 0xf6, 0x01, 0x43, 0x02,
	0xd3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const __u8 cx_inits_352[] = {
	0x2e, 0x7c, 0x60, 0x01, 0x20, 0x01, 0x05, 0x03,
	0x00, 0x06, 0x03, 0x06, 0x1b, 0x10, 0x05, 0x3b,
	0x30, 0x25, 0x18, 0x25, 0x08, 0x30, 0x03, 0x25,
	0x3b, 0x30, 0x25, 0x1b, 0x10, 0x05, 0x00, 0x00,
	0xe3, 0xff, 0xf1, 0xff, 0xc2, 0xff, 0xbc, 0xff,
	0xf5, 0xff, 0x6b, 0xff, 0xee, 0x01, 0x43, 0x02,
	0xe4, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const __u8 cx_inits_640[] = {
	0x7e, 0x7e, 0x80, 0x02, 0xe0, 0x01, 0x01, 0x01,
	0x00, 0x02, 0x01, 0x02, 0x10, 0x30, 0x01, 0x01,
	0x65, 0x45, 0xf7, 0x52, 0x2c, 0xdf, 0xb9, 0x81,
	0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0xe2, 0xff, 0xf1, 0xff, 0xc2, 0xff, 0xbc, 0xff,
	0xf6, 0xff, 0x7b, 0xff, 0x01, 0x02, 0x43, 0x02,
	0x77, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void cx11646_initsize(struct gspca_dev *gspca_dev)
{
	const __u8 *cxinit;
	static const __u8 reg12[] = { 0x08, 0x05, 0x07, 0x04, 0x24 };
	static const __u8 reg17[] =
			{ 0x0a, 0x00, 0xf2, 0x01, 0x0f, 0x00, 0x97, 0x02 };

	switch (gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv) {
	case 0:
		cxinit = cx_inits_640;
		break;
	case 1:
		cxinit = cx_inits_352;
		break;
	default:
/*	case 2: */
		cxinit = cx_inits_320;
		break;
	case 3:
		cxinit = cx_inits_176;
		break;
	}
	reg_w_val(gspca_dev, 0x009a, 0x01);
	reg_w_val(gspca_dev, 0x0010, 0x10);
	reg_w(gspca_dev, 0x0012, reg12, 5);
	reg_w(gspca_dev, 0x0017, reg17, 8);
	reg_w_val(gspca_dev, 0x00c0, 0x00);
	reg_w_val(gspca_dev, 0x00c1, 0x04);
	reg_w_val(gspca_dev, 0x00c2, 0x04);

	reg_w(gspca_dev, 0x0061, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x00ca, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x00d2, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x00da, cxinit, 6);
	cxinit += 8;
	reg_w(gspca_dev, 0x0041, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x0049, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x0051, cxinit, 2);

	reg_r(gspca_dev, 0x0010, 1);
}

static const __u8 cx_jpeg_init[][8] = {
	{0xff, 0xd8, 0xff, 0xdb, 0x00, 0x84, 0x00, 0x15},	/* 1 */
	{0x0f, 0x10, 0x12, 0x10, 0x0d, 0x15, 0x12, 0x11},
	{0x12, 0x18, 0x16, 0x15, 0x19, 0x20, 0x35, 0x22},
	{0x20, 0x1d, 0x1d, 0x20, 0x41, 0x2e, 0x31, 0x26},
	{0x35, 0x4d, 0x43, 0x51, 0x4f, 0x4b, 0x43, 0x4a},
	{0x49, 0x55, 0x5F, 0x79, 0x67, 0x55, 0x5A, 0x73},
	{0x5B, 0x49, 0x4A, 0x6A, 0x90, 0x6B, 0x73, 0x7D},
	{0x81, 0x88, 0x89, 0x88, 0x52, 0x66, 0x95, 0xA0},
	{0x94, 0x84, 0x9E, 0x79, 0x85, 0x88, 0x83, 0x01},
	{0x15, 0x0F, 0x10, 0x12, 0x10, 0x0D, 0x15, 0x12},
	{0x11, 0x12, 0x18, 0x16, 0x15, 0x19, 0x20, 0x35},
	{0x22, 0x20, 0x1D, 0x1D, 0x20, 0x41, 0x2E, 0x31},
	{0x26, 0x35, 0x4D, 0x43, 0x51, 0x4F, 0x4B, 0x43},
	{0x4A, 0x49, 0x55, 0x5F, 0x79, 0x67, 0x55, 0x5A},
	{0x73, 0x5B, 0x49, 0x4A, 0x6A, 0x90, 0x6B, 0x73},
	{0x7D, 0x81, 0x88, 0x89, 0x88, 0x52, 0x66, 0x95},
	{0xA0, 0x94, 0x84, 0x9E, 0x79, 0x85, 0x88, 0x83},
	{0xFF, 0xC4, 0x01, 0xA2, 0x00, 0x00, 0x01, 0x05},
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02},
	{0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A},
	{0x0B, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01},
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
	{0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x10, 0x00},
	{0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05},
	{0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7D, 0x01},
	{0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21},
	{0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22},
	{0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23},
	{0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0, 0x24},
	{0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17},
	{0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28, 0x29},
	{0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A},
	{0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A},
	{0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A},
	{0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A},
	{0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A},
	{0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A},
	{0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99},
	{0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8},
	{0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7},
	{0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6},
	{0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5},
	{0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2, 0xE3},
	{0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1},
	{0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9},
	{0xFA, 0x11, 0x00, 0x02, 0x01, 0x02, 0x04, 0x04},
	{0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01},
	{0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04},
	{0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07},
	{0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08, 0x14},
	{0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33},
	{0x52, 0xF0, 0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16},
	{0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19},
	{0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x35, 0x36},
	{0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46},
	{0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56},
	{0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66},
	{0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76},
	{0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85},
	{0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94},
	{0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3},
	{0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2},
	{0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA},
	{0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9},
	{0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8},
	{0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7},
	{0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6},
	{0xF7, 0xF8, 0xF9, 0xFA, 0xFF, 0x20, 0x00, 0x1F},
	{0x02, 0x0C, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x11, 0x00, 0x11, 0x22, 0x00, 0x22},
	{0x22, 0x11, 0x22, 0x22, 0x11, 0x33, 0x33, 0x11},
	{0x44, 0x66, 0x22, 0x55, 0x66, 0xFF, 0xDD, 0x00},
	{0x04, 0x00, 0x14, 0xFF, 0xC0, 0x00, 0x11, 0x08},
	{0x00, 0xF0, 0x01, 0x40, 0x03, 0x00, 0x21, 0x00},
	{0x01, 0x11, 0x01, 0x02, 0x11, 0x01, 0xFF, 0xDA},
	{0x00, 0x0C, 0x03, 0x00, 0x00, 0x01, 0x11, 0x02},
	{0x11, 0x00, 0x3F, 0x00, 0xFF, 0xD9, 0x00, 0x00}	/* 79 */
};


static const __u8 cxjpeg_640[][8] = {
	{0xff, 0xd8, 0xff, 0xdb, 0x00, 0x84, 0x00, 0x10},	/* 1 */
	{0x0b, 0x0c, 0x0e, 0x0c, 0x0a, 0x10, 0x0e, 0x0d},
	{0x0e, 0x12, 0x11, 0x10, 0x13, 0x18, 0x28, 0x1a},
	{0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25, 0x1d},
	{0x28, 0x3a, 0x33, 0x3D, 0x3C, 0x39, 0x33, 0x38},
	{0x37, 0x40, 0x48, 0x5C, 0x4E, 0x40, 0x44, 0x57},
	{0x45, 0x37, 0x38, 0x50, 0x6D, 0x51, 0x57, 0x5F},
	{0x62, 0x67, 0x68, 0x67, 0x3E, 0x4D, 0x71, 0x79},
	{0x70, 0x64, 0x78, 0x5C, 0x65, 0x67, 0x63, 0x01},
	{0x10, 0x0B, 0x0C, 0x0E, 0x0C, 0x0A, 0x10, 0x0E},
	{0x0D, 0x0E, 0x12, 0x11, 0x10, 0x13, 0x18, 0x28},
	{0x1A, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25},
	{0x1D, 0x28, 0x3A, 0x33, 0x3D, 0x3C, 0x39, 0x33},
	{0x38, 0x37, 0x40, 0x48, 0x5C, 0x4E, 0x40, 0x44},
	{0x57, 0x45, 0x37, 0x38, 0x50, 0x6D, 0x51, 0x57},
	{0x5F, 0x62, 0x67, 0x68, 0x67, 0x3E, 0x4D, 0x71},
	{0x79, 0x70, 0x64, 0x78, 0x5C, 0x65, 0x67, 0x63},
	{0xFF, 0x20, 0x00, 0x1F, 0x00, 0x83, 0x00, 0x00},
	{0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00},
	{0x11, 0x22, 0x00, 0x22, 0x22, 0x11, 0x22, 0x22},
	{0x11, 0x33, 0x33, 0x11, 0x44, 0x66, 0x22, 0x55},
	{0x66, 0xFF, 0xDD, 0x00, 0x04, 0x00, 0x28, 0xFF},
	{0xC0, 0x00, 0x11, 0x08, 0x01, 0xE0, 0x02, 0x80},
	{0x03, 0x00, 0x21, 0x00, 0x01, 0x11, 0x01, 0x02},
	{0x11, 0x01, 0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x00},
	{0x00, 0x01, 0x11, 0x02, 0x11, 0x00, 0x3F, 0x00},
	{0xFF, 0xD9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}	/* 27 */
};
static const __u8 cxjpeg_352[][8] = {
	{0xff, 0xd8, 0xff, 0xdb, 0x00, 0x84, 0x00, 0x0d},
	{0x09, 0x09, 0x0b, 0x09, 0x08, 0x0D, 0x0b, 0x0a},
	{0x0b, 0x0e, 0x0d, 0x0d, 0x0f, 0x13, 0x1f, 0x14},
	{0x13, 0x11, 0x11, 0x13, 0x26, 0x1b, 0x1d, 0x17},
	{0x1F, 0x2D, 0x28, 0x30, 0x2F, 0x2D, 0x28, 0x2C},
	{0x2B, 0x32, 0x38, 0x48, 0x3D, 0x32, 0x35, 0x44},
	{0x36, 0x2B, 0x2C, 0x3F, 0x55, 0x3F, 0x44, 0x4A},
	{0x4D, 0x50, 0x51, 0x50, 0x30, 0x3C, 0x58, 0x5F},
	{0x58, 0x4E, 0x5E, 0x48, 0x4F, 0x50, 0x4D, 0x01},
	{0x0D, 0x09, 0x09, 0x0B, 0x09, 0x08, 0x0D, 0x0B},
	{0x0A, 0x0B, 0x0E, 0x0D, 0x0D, 0x0F, 0x13, 0x1F},
	{0x14, 0x13, 0x11, 0x11, 0x13, 0x26, 0x1B, 0x1D},
	{0x17, 0x1F, 0x2D, 0x28, 0x30, 0x2F, 0x2D, 0x28},
	{0x2C, 0x2B, 0x32, 0x38, 0x48, 0x3D, 0x32, 0x35},
	{0x44, 0x36, 0x2B, 0x2C, 0x3F, 0x55, 0x3F, 0x44},
	{0x4A, 0x4D, 0x50, 0x51, 0x50, 0x30, 0x3C, 0x58},
	{0x5F, 0x58, 0x4E, 0x5E, 0x48, 0x4F, 0x50, 0x4D},
	{0xFF, 0x20, 0x00, 0x1F, 0x01, 0x83, 0x00, 0x00},
	{0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00},
	{0x11, 0x22, 0x00, 0x22, 0x22, 0x11, 0x22, 0x22},
	{0x11, 0x33, 0x33, 0x11, 0x44, 0x66, 0x22, 0x55},
	{0x66, 0xFF, 0xDD, 0x00, 0x04, 0x00, 0x16, 0xFF},
	{0xC0, 0x00, 0x11, 0x08, 0x01, 0x20, 0x01, 0x60},
	{0x03, 0x00, 0x21, 0x00, 0x01, 0x11, 0x01, 0x02},
	{0x11, 0x01, 0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x00},
	{0x00, 0x01, 0x11, 0x02, 0x11, 0x00, 0x3F, 0x00},
	{0xFF, 0xD9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};
static const __u8 cxjpeg_320[][8] = {
	{0xff, 0xd8, 0xff, 0xdb, 0x00, 0x84, 0x00, 0x05},
	{0x03, 0x04, 0x04, 0x04, 0x03, 0x05, 0x04, 0x04},
	{0x04, 0x05, 0x05, 0x05, 0x06, 0x07, 0x0c, 0x08},
	{0x07, 0x07, 0x07, 0x07, 0x0f, 0x0b, 0x0b, 0x09},
	{0x0C, 0x11, 0x0F, 0x12, 0x12, 0x11, 0x0f, 0x11},
	{0x11, 0x13, 0x16, 0x1C, 0x17, 0x13, 0x14, 0x1A},
	{0x15, 0x11, 0x11, 0x18, 0x21, 0x18, 0x1A, 0x1D},
	{0x1D, 0x1F, 0x1F, 0x1F, 0x13, 0x17, 0x22, 0x24},
	{0x22, 0x1E, 0x24, 0x1C, 0x1E, 0x1F, 0x1E, 0x01},
	{0x05, 0x03, 0x04, 0x04, 0x04, 0x03, 0x05, 0x04},
	{0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x07, 0x0C},
	{0x08, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x0B, 0x0B},
	{0x09, 0x0C, 0x11, 0x0F, 0x12, 0x12, 0x11, 0x0F},
	{0x11, 0x11, 0x13, 0x16, 0x1C, 0x17, 0x13, 0x14},
	{0x1A, 0x15, 0x11, 0x11, 0x18, 0x21, 0x18, 0x1A},
	{0x1D, 0x1D, 0x1F, 0x1F, 0x1F, 0x13, 0x17, 0x22},
	{0x24, 0x22, 0x1E, 0x24, 0x1C, 0x1E, 0x1F, 0x1E},
	{0xFF, 0x20, 0x00, 0x1F, 0x02, 0x0C, 0x00, 0x00},
	{0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00},
	{0x11, 0x22, 0x00, 0x22, 0x22, 0x11, 0x22, 0x22},
	{0x11, 0x33, 0x33, 0x11, 0x44, 0x66, 0x22, 0x55},
	{0x66, 0xFF, 0xDD, 0x00, 0x04, 0x00, 0x14, 0xFF},
	{0xC0, 0x00, 0x11, 0x08, 0x00, 0xF0, 0x01, 0x40},
	{0x03, 0x00, 0x21, 0x00, 0x01, 0x11, 0x01, 0x02},
	{0x11, 0x01, 0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x00},
	{0x00, 0x01, 0x11, 0x02, 0x11, 0x00, 0x3F, 0x00},
	{0xFF, 0xD9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}	/* 27 */
};
static const __u8 cxjpeg_176[][8] = {
	{0xff, 0xd8, 0xff, 0xdb, 0x00, 0x84, 0x00, 0x0d},
	{0x09, 0x09, 0x0B, 0x09, 0x08, 0x0D, 0x0B, 0x0A},
	{0x0B, 0x0E, 0x0D, 0x0D, 0x0F, 0x13, 0x1F, 0x14},
	{0x13, 0x11, 0x11, 0x13, 0x26, 0x1B, 0x1D, 0x17},
	{0x1F, 0x2D, 0x28, 0x30, 0x2F, 0x2D, 0x28, 0x2C},
	{0x2B, 0x32, 0x38, 0x48, 0x3D, 0x32, 0x35, 0x44},
	{0x36, 0x2B, 0x2C, 0x3F, 0x55, 0x3F, 0x44, 0x4A},
	{0x4D, 0x50, 0x51, 0x50, 0x30, 0x3C, 0x58, 0x5F},
	{0x58, 0x4E, 0x5E, 0x48, 0x4F, 0x50, 0x4D, 0x01},
	{0x0D, 0x09, 0x09, 0x0B, 0x09, 0x08, 0x0D, 0x0B},
	{0x0A, 0x0B, 0x0E, 0x0D, 0x0D, 0x0F, 0x13, 0x1F},
	{0x14, 0x13, 0x11, 0x11, 0x13, 0x26, 0x1B, 0x1D},
	{0x17, 0x1F, 0x2D, 0x28, 0x30, 0x2F, 0x2D, 0x28},
	{0x2C, 0x2B, 0x32, 0x38, 0x48, 0x3D, 0x32, 0x35},
	{0x44, 0x36, 0x2B, 0x2C, 0x3F, 0x55, 0x3F, 0x44},
	{0x4A, 0x4D, 0x50, 0x51, 0x50, 0x30, 0x3C, 0x58},
	{0x5F, 0x58, 0x4E, 0x5E, 0x48, 0x4F, 0x50, 0x4D},
	{0xFF, 0x20, 0x00, 0x1F, 0x03, 0xA1, 0x00, 0x00},
	{0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00},
	{0x11, 0x22, 0x00, 0x22, 0x22, 0x11, 0x22, 0x22},
	{0x11, 0x33, 0x33, 0x11, 0x44, 0x66, 0x22, 0x55},
	{0x66, 0xFF, 0xDD, 0x00, 0x04, 0x00, 0x0B, 0xFF},
	{0xC0, 0x00, 0x11, 0x08, 0x00, 0x90, 0x00, 0xB0},
	{0x03, 0x00, 0x21, 0x00, 0x01, 0x11, 0x01, 0x02},
	{0x11, 0x01, 0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x00},
	{0x00, 0x01, 0x11, 0x02, 0x11, 0x00, 0x3F, 0x00},
	{0xFF, 0xD9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};
/* 640 take with the zcx30x part */
static const __u8 cxjpeg_qtable[][8] = {
	{0xff, 0xd8, 0xff, 0xdb, 0x00, 0x84, 0x00, 0x08},
	{0x06, 0x06, 0x07, 0x06, 0x05, 0x08, 0x07, 0x07},
	{0x07, 0x09, 0x09, 0x08, 0x0a, 0x0c, 0x14, 0x0a},
	{0x0c, 0x0b, 0x0b, 0x0c, 0x19, 0x12, 0x13, 0x0f},
	{0x14, 0x1d, 0x1a, 0x1f, 0x1e, 0x1d, 0x1a, 0x1c},
	{0x1c, 0x20, 0x24, 0x2e, 0x27, 0x20, 0x22, 0x2c},
	{0x23, 0x1c, 0x1c, 0x28, 0x37, 0x29, 0x2c, 0x30},
	{0x31, 0x34, 0x34, 0x34, 0x1f, 0x27, 0x39, 0x3d},
	{0x38, 0x32, 0x3c, 0x2e, 0x33, 0x34, 0x32, 0x01},
	{0x09, 0x09, 0x09, 0x0c, 0x0b, 0x0c, 0x18, 0x0a},
	{0x0a, 0x18, 0x32, 0x21, 0x1c, 0x21, 0x32, 0x32},
	{0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32},
	{0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32},
	{0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32},
	{0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32},
	{0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32},
	{0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32},
	{0xFF, 0xD9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}	/* 18 */
};


static void cx11646_jpegInit(struct gspca_dev*gspca_dev)
{
	int i;
	int length;

	reg_w_val(gspca_dev, 0x00c0, 0x01);
	reg_w_val(gspca_dev, 0x00c3, 0x00);
	reg_w_val(gspca_dev, 0x00c0, 0x00);
	reg_r(gspca_dev, 0x0001, 1);
	length = 8;
	for (i = 0; i < 79; i++) {
		if (i == 78)
			length = 6;
		reg_w(gspca_dev, 0x0008, cx_jpeg_init[i], length);
	}
	reg_r(gspca_dev, 0x0002, 1);
	reg_w_val(gspca_dev, 0x0055, 0x14);
}

static const __u8 reg12[] = { 0x0a, 0x05, 0x07, 0x04, 0x19 };
static const __u8 regE5_8[] =
		{ 0x88, 0x00, 0xd4, 0x01, 0x88, 0x01, 0x01, 0x01 };
static const __u8 regE5a[] = { 0x88, 0x0a, 0x0c, 0x01 };
static const __u8 regE5b[] = { 0x88, 0x0b, 0x12, 0x01 };
static const __u8 regE5c[] = { 0x88, 0x05, 0x01, 0x01 };
static const __u8 reg51[] = { 0x77, 0x03 };
#define reg70 0x03

static void cx11646_jpeg(struct gspca_dev*gspca_dev)
{
	int i;
	int length;
	__u8 Reg55;
	int retry;

	reg_w_val(gspca_dev, 0x00c0, 0x01);
	reg_w_val(gspca_dev, 0x00c3, 0x00);
	reg_w_val(gspca_dev, 0x00c0, 0x00);
	reg_r(gspca_dev, 0x0001, 1);
	length = 8;
	switch (gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv) {
	case 0:
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_640[i], length);
		}
		Reg55 = 0x28;
		break;
	case 1:
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_352[i], length);
		}
		Reg55 = 0x16;
		break;
	default:
/*	case 2: */
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_320[i], length);
		}
		Reg55 = 0x14;
		break;
	case 3:
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_176[i], length);
		}
		Reg55 = 0x0B;
		break;
	}

	reg_r(gspca_dev, 0x0002, 1);
	reg_w_val(gspca_dev, 0x0055, Reg55);
	reg_r(gspca_dev, 0x0002, 1);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0054, 0x02);
	reg_w_val(gspca_dev, 0x0054, 0x01);
	reg_w_val(gspca_dev, 0x0000, 0x94);
	reg_w_val(gspca_dev, 0x0053, 0xc0);
	reg_w_val(gspca_dev, 0x00fc, 0xe1);
	reg_w_val(gspca_dev, 0x0000, 0x00);
	/* wait for completion */
	retry = 50;
	do {
		reg_r(gspca_dev, 0x0002, 1);
							/* 0x07 until 0x00 */
		if (gspca_dev->usb_buf[0] == 0x00)
			break;
		reg_w_val(gspca_dev, 0x0053, 0x00);
	} while (--retry);
	if (retry == 0)
		PDEBUG(D_ERR, "Damned Errors sending jpeg Table");
	/* send the qtable now */
	reg_r(gspca_dev, 0x0001, 1);		/* -> 0x18 */
	length = 8;
	for (i = 0; i < 18; i++) {
		if (i == 17)
			length = 2;
		reg_w(gspca_dev, 0x0008, cxjpeg_qtable[i], length);

	}
	reg_r(gspca_dev, 0x0002, 1);	/* 0x00 */
	reg_r(gspca_dev, 0x0053, 1);	/* 0x00 */
	reg_w_val(gspca_dev, 0x0054, 0x02);
	reg_w_val(gspca_dev, 0x0054, 0x01);
	reg_w_val(gspca_dev, 0x0000, 0x94);
	reg_w_val(gspca_dev, 0x0053, 0xc0);

	reg_r(gspca_dev, 0x0038, 1);		/* 0x40 */
	reg_r(gspca_dev, 0x0038, 1);		/* 0x40 */
	reg_r(gspca_dev, 0x001f, 1);		/* 0x38 */
	reg_w(gspca_dev, 0x0012, reg12, 5);
	reg_w(gspca_dev, 0x00e5, regE5_8, 8);
	reg_r(gspca_dev, 0x00e8, 8);
	reg_w(gspca_dev, 0x00e5, regE5a, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */
	reg_w_val(gspca_dev, 0x009a, 0x01);
	reg_w(gspca_dev, 0x00e5, regE5b, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */
	reg_w(gspca_dev, 0x00e5, regE5c, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */

	reg_w(gspca_dev, 0x0051, reg51, 2);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0070, reg70);
}

static void cx11646_init1(struct gspca_dev *gspca_dev)
{
	int i = 0;

	reg_w_val(gspca_dev, 0x0010, 0x00);
	reg_w_val(gspca_dev, 0x0053, 0x00);
	reg_w_val(gspca_dev, 0x0052, 0x00);
	reg_w_val(gspca_dev, 0x009b, 0x2f);
	reg_w_val(gspca_dev, 0x009c, 0x10);
	reg_r(gspca_dev, 0x0098, 1);
	reg_w_val(gspca_dev, 0x0098, 0x40);
	reg_r(gspca_dev, 0x0099, 1);
	reg_w_val(gspca_dev, 0x0099, 0x07);
	reg_w_val(gspca_dev, 0x0039, 0x40);
	reg_w_val(gspca_dev, 0x003c, 0xff);
	reg_w_val(gspca_dev, 0x003f, 0x1f);
	reg_w_val(gspca_dev, 0x003d, 0x40);
/*	reg_w_val(gspca_dev, 0x003d, 0x60); */
	reg_r(gspca_dev, 0x0099, 1);			/* ->0x07 */

	while (cx_sensor_init[i][0]) {
		reg_w_val(gspca_dev, 0x00e5, cx_sensor_init[i][0]);
		reg_r(gspca_dev, 0x00e8, 1);		/* -> 0x00 */
		if (i == 1) {
			reg_w_val(gspca_dev, 0x00ed, 0x01);
			reg_r(gspca_dev, 0x00ed, 1);	/* -> 0x01 */
		}
		i++;
	}
	reg_w_val(gspca_dev, 0x00c3, 0x00);
}

/* this function is called at probe time */
static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);

	sd->brightness = BRIGHTNESS_DEF;
	sd->contrast = CONTRAST_DEF;
	sd->colors = COLOR_DEF;
	sd->quality = QUALITY_DEF;
	return 0;
}

/* this function is called at probe and resume time */
static int sd_init(struct gspca_dev *gspca_dev)
{
	cx11646_init1(gspca_dev);
	cx11646_initsize(gspca_dev);
	cx11646_fw(gspca_dev);
	cx_sensor(gspca_dev);
	cx11646_jpegInit(gspca_dev);
	return 0;
}

static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->height, gspca_dev->width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, sd->quality);

	cx11646_initsize(gspca_dev);
	cx11646_fw(gspca_dev);
	cx_sensor(gspca_dev);
	cx11646_jpeg(gspca_dev);
	return 0;
}

/* called on streamoff with alt 0 and on disconnect */
static void sd_stop0(struct gspca_dev *gspca_dev)
{
	int retry = 50;

	if (!gspca_dev->present)
		return;
	reg_w_val(gspca_dev, 0x0000, 0x00);
	reg_r(gspca_dev, 0x0002, 1);
	reg_w_val(gspca_dev, 0x0053, 0x00);

	while (retry--) {
/*		reg_r(gspca_dev, 0x0002, 1);*/
		reg_r(gspca_dev, 0x0053, 1);
		if (gspca_dev->usb_buf[0] == 0)
			break;
	}
	reg_w_val(gspca_dev, 0x0000, 0x00);
	reg_r(gspca_dev, 0x0002, 1);

	reg_w_val(gspca_dev, 0x0010, 0x00);
	reg_r(gspca_dev, 0x0033, 1);
	reg_w_val(gspca_dev, 0x00fc, 0xe0);
}

static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (data[0] == 0xff && data[1] == 0xd8) {

		/* start of frame */
		gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);

		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				sd->jpeg_hdr, JPEG_HDR_SZ);
		data += 2;
		len -= 2;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}

static void setbrightness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 regE5cbx[] = { 0x88, 0x00, 0xd4, 0x01, 0x88, 0x01, 0x01, 0x01 };
	__u8 reg51c[2];
	__u8 bright;
	__u8 colors;

	bright = sd->brightness;
	regE5cbx[2] = bright;
	reg_w(gspca_dev, 0x00e5, regE5cbx, 8);
	reg_r(gspca_dev, 0x00e8, 8);
	reg_w(gspca_dev, 0x00e5, regE5c, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */

	colors = sd->colors;
	reg51c[0] = 0x77;
	reg51c[1] = colors;
	reg_w(gspca_dev, 0x0051, reg51c, 2);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0070, reg70);
}

static void setcontrast(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 regE5acx[] = { 0x88, 0x0a, 0x0c, 0x01 };	/* seem MSB */
/*	__u8 regE5bcx[] = { 0x88, 0x0b, 0x12, 0x01};	 * LSB */
	__u8 reg51c[2];

	regE5acx[2] = sd->contrast;
	reg_w(gspca_dev, 0x00e5, regE5acx, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */
	reg51c[0] = 0x77;
	reg51c[1] = sd->colors;
	reg_w(gspca_dev, 0x0051, reg51c, 2);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0070, reg70);
}

static int sd_setbrightness(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->brightness = val;
	if (gspca_dev->streaming)
		setbrightness(gspca_dev);
	return 0;
}

static int sd_getbrightness(struct gspca_dev *gspca_dev, __s32 *val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	*val = sd->brightness;
	return 0;
}

static int sd_setcontrast(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->contrast = val;
	if (gspca_dev->streaming)
		setcontrast(gspca_dev);
	return 0;
}

static int sd_getcontrast(struct gspca_dev *gspca_dev, __s32 *val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	*val = sd->contrast;
	return 0;
}

static int sd_setcolors(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->colors = val;
	if (gspca_dev->streaming) {
		setbrightness(gspca_dev);
		setcontrast(gspca_dev);
	}
	return 0;
}

static int sd_getcolors(struct gspca_dev *gspca_dev, __s32 *val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	*val = sd->colors;
	return 0;
}

static int sd_set_jcomp(struct gspca_dev *gspca_dev,
			struct v4l2_jpegcompression *jcomp)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (jcomp->quality < QUALITY_MIN)
		sd->quality = QUALITY_MIN;
	else if (jcomp->quality > QUALITY_MAX)
		sd->quality = QUALITY_MAX;
	else
		sd->quality = jcomp->quality;
	if (gspca_dev->streaming)
		jpeg_set_qual(sd->jpeg_hdr, sd->quality);
	return 0;
}

static int sd_get_jcomp(struct gspca_dev *gspca_dev,
			struct v4l2_jpegcompression *jcomp)
{
	struct sd *sd = (struct sd *) gspca_dev;

	memset(jcomp, 0, sizeof *jcomp);
	jcomp->quality = sd->quality;
	jcomp->jpeg_markers = V4L2_JPEG_MARKER_DHT
			| V4L2_JPEG_MARKER_DQT;
	return 0;
}

/* sub-driver description */
static const struct sd_desc sd_desc = {
	.name = MODULE_NAME,
	.ctrls = sd_ctrls,
	.nctrls = ARRAY_SIZE(sd_ctrls),
	.config = sd_config,
	.init = sd_init,
	.start = sd_start,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
	.get_jcomp = sd_get_jcomp,
	.set_jcomp = sd_set_jcomp,
};

/* -- module initialisation -- */
static const struct usb_device_id device_table[] = {
	{USB_DEVICE(0x0572, 0x0041)},
	{}
};
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
static int sd_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	return gspca_dev_probe(intf, id, &sd_desc, sizeof(struct sd),
				THIS_MODULE);
}

static struct usb_driver sd_driver = {
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
#endif
};

module_usb_driver(sd_driver);
