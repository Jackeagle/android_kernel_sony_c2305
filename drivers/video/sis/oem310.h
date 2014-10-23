/* $XFree86$ */
/* $XdotOrg$ */
/*
 * OEM Data for 315/330/340 series
 *
 * Copyright (C) 2001-2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation; either version 2 of the named License,
 * * or any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to endorse or promote products
 * *    derived from this software without specific prior written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: 	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

static const unsigned char SiS310_LCDDelayCompensation_301[] =	    		/* 301 */
{
	0x00,0x00,0x00,    /*   800x600 */
	0x0b,0x0b,0x0b,    /*  1024x768 */
	0x08,0x08,0x08,    /* 1280x1024 */
	0x00,0x00,0x00,    /*   640x480 (unknown) */
	0x00,0x00,0x00,    /*  1024x600 (unknown) */
	0x00,0x00,0x00,    /*  1152x864 (unknown) */
	0x08,0x08,0x08,    /*  1280x960 (guessed) */
	0x00,0x00,0x00,    /*  1152x768 (unknown) */
	0x08,0x08,0x08,    /* 1400x1050 */
	0x08,0x08,0x08,    /*  1280x768  (guessed) */
	0x00,0x00,0x00,    /* 1600x1200 */
	0x00,0x00,0x00,    /*   320x480 (unknown) */
	0x00,0x00,0x00,
	0x00,0x00,0x00,
	0x00,0x00,0x00
};

/* This is contained in 650+301B BIOSes, but it is wrong - so we don't use it */
static const unsigned char SiS310_LCDDelayCompensation_650301LV[] =	   	/* 650 + 30xLV */
{
	0x01,0x01,0x01,    /*   800x600 */
	0x01,0x01,0x01,    /*  1024x768 */
	0x01,0x01,0x01,    /* 1280x1024 */
	0x01,0x01,0x01,    /*   640x480 (unknown) */
	0x01,0x01,0x01,    /*  1024x600 (unknown) */
	0x01,0x01,0x01,    /*  1152x864 (unknown) */
	0x01,0x01,0x01,    /*  1280x960 (guessed) */
	0x01,0x01,0x01,    /*  1152x768 (unknown) */
	0x01,0x01,0x01,    /* 1400x1050 */
	0x01,0x01,0x01,    /*  1280x768  (guessed) */
	0x01,0x01,0x01,    /* 1600x1200 */
	0x02,0x02,0x02,
	0x02,0x02,0x02,
	0x02,0x02,0x02,
	0x02,0x02,0x02
};

static const unsigned char SiS310_LCDDelayCompensation_651301LV[] =	  	/* M650/651 301LV */
{
	0x33,0x33,0x33,    /*   800x600 (guessed) - new: PanelType, not PanelRes ! */
	0x33,0x33,0x33,    /*  1024x768 */
	0x33,0x33,0x33,    /* 1280x1024 */
	0x33,0x33,0x33,    /*   640x480 (unknown) */
	0x33,0x33,0x33,    /*  1024x600 (unknown) */
	0x33,0x33,0x33,    /*  1152x864 (unknown) */
	0x33,0x33,0x33,    /*  1280x960 (guessed) */
	0x33,0x33,0x33,    /*  1152x768 (unknown) */
	0x33,0x33,0x33,    /* 1400x1050 */
	0x33,0x33,0x33,    /*  1280x768  (guessed) */
	0x33,0x33,0x33,    /* 1600x1200 */
	0x33,0x33,0x33,
	0x33,0x33,0x33,
	0x33,0x33,0x33,
	0x33,0x33,0x33
};

static const unsigned char SiS310_LCDDelayCompensation_651302LV[] =	   	/* M650/651 302LV */
{
	0x33,0x33,0x33,    /*   800x600 (guessed) */
	0x33,0x33,0x33,    /*  1024x768 */
	0x33,0x33,0x33,    /* 1280x1024 */
	0x33,0x33,0x33,    /*   640x480 (unknown) */
	0x33,0x33,0x33,    /*  1024x600 (unknown) */
	0x33,0x33,0x33,    /*  1152x864 (unknown) */
	0x33,0x33,0x33,    /*  1280x960 (guessed) */
	0x33,0x33,0x33,    /*  1152x768 (unknown) */
	0x33,0x33,0x33,    /* 1400x1050 */
	0x33,0x33,0x33,    /*  1280x768  (guessed) */
	0x33,0x33,0x33,    /* 1600x1200 */
	0x33,0x33,0x33,
	0x33,0x33,0x33,
	0x33,0x33,0x33,
	0x33,0x33,0x33
};

static const unsigned char SiS310_LCDDelayCompensation_3xx301B[] =	   	/* 30xB */
{
	0x01,0x01,0x01,    /*   800x600 */
	0x0C,0x0C,0x0C,    /*  1024x768 */
	0x0C,0x0C,0x0C,    /* 1280x1024 */
	0x08,0x08,0x08,    /*   640x480 */
	0x0C,0x0C,0x0C,    /*  1024x600 (guessed) */
	0x0C,0x0C,0x0C,    /*  1152x864 (guessed) */
	0x0C,0x0C,0x0C,    /*  1280x960 (guessed) */
	0x0C,0x0C,0x0C,    /*  1152x768 (guessed) */
	0x0C,0x0C,0x0C,    /* 1400x1050 (guessed) */
	0x0C,0x0C,0x0C,    /*  1280x768 (guessed) */
	0x0C,0x0C,0x0C,    /* 1600x1200 (guessed) */
	0x02,0x02,0x02,
	0x02,0x02,0x02,
	0x02,0x02,0x02,
	0x02,0x02,0x02
};

static const unsigned char SiS310_LCDDelayCompensation_3xx301LV[] =	   	/* 315+30xLV */
{
	0x01,0x01,0x01,    /*   800x600 */
	0x04,0x04,0x04,    /*  1024x768 (A531/BIOS 1.14.05f: 4 - works with 6 */
	0x0C,0x0C,0x0C,    /* 1280x1024 */
	0x08,0x08,0x08,    /*   640x480 */
	0x0C,0x0C,0x0C,    /*  1024x600 (guessed) */
	0x0C,0x0C,0x0C,    /*  1152x864 (guessed) */
	0x0C,0x0C,0x0C,    /*  1280x960 (guessed) */
	0x0C,0x0C,0x0C,    /*  1152x768 (guessed) */
	0x0C,0x0C,0x0C,    /* 1400x1050 (guessed) */
	0x0C,0x0C,0x0C,    /*  1280x768 (guessed) */
	0x0C,0x0C,0x0C,    /* 1600x1200 (guessed) */
	0x02,0x02,0x02,
	0x02,0x02,0x02,
	0x02,0x02,0x02,
	0x02,0x02,0x02
};

static const unsigned char SiS310_TVDelayCompensation_301[] = 		/* 301 */
{
	0x02,0x02,    /* NTSC Enhanced, Standard */
	0x02,0x02,    /* PAL */
	0x08,0x0b     /* HiVision */
};

static const unsigned char SiS310_TVDelayCompensation_301B[] =		/* 30xB, 30xLV */
{
	0x03,0x03,
	0x03,0x03,
	0x03,0x03
};

static const unsigned char SiS310_TVDelayCompensation_740301B[] =	/* 740 + 30xB (30xLV?) */
{
	0x05,0x05,
	0x05,0x05,
	0x05,0x05
};

static const unsigned char SiS310_TVDelayCompensation_651301LV[] =	/* M650, 651, 301LV */
{
	0x33,0x33,
	0x33,0x33,
	0x33,0x33
};

static const unsigned char SiS310_TVDelayCompensation_651302LV[] =	/* M650, 651, 302LV */
{
	0x33,0x33,
	0x33,0x33,
	0x33,0x33
};

static const unsigned char SiS_TVDelay661_301[] =			/* 661, 301 */
{
	0x44,0x44,
	0x44,0x44,
	0x00,0x00,
	0x44,0x44,
	0x44,0x44,
	0x44,0x44
};

static const unsigned char SiS_TVDelay661_301B[] =			/* 661, 301B et al */
{
	0x44,0x44,
	0x44,0x44,
	0x00,0x00,
	0x44,0x44,
	0x44,0x44,
	0x44,0x44
};

static const unsigned char SiS310_TVDelayCompensation_LVDS[] =		/* LVDS */
{
	0x0a,0x0a,
	0x0a,0x0a,
	0x0a,0x0a
};

static const unsigned char SiS310_TVAntiFlick1[6][2] =
{
	{0x4,0x0},
	{0x4,0x8},
	{0x0,0x0},
	{0x0,0x0},
	{0x0,0x0},
	{0x0,0x0}
};

static const unsigned char SiS310_TVEdge1[6][2] =
{
	{0x0,0x4},
	{0x0,0x4},
	{0x0,0x0},
	{0x0,0x0},
	{0x0,0x0},
	{0x0,0x0}
};

static const unsigned char SiS310_TVYFilter1[5][8][4] =
{
   {
	{0x00,0xf4,0x10,0x38},	/* NTSC */
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x25,0x18},
	{0xf1,0x04,0x1f,0x18},
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x25,0x18},
	{0xee,0x0c,0x22,0x08},
	{0xeb,0x15,0x25,0xf6}
   },
   {
	{0x00,0xf4,0x10,0x38},	/* PAL */
	{0x00,0xf4,0x10,0x38},
	{0xf1,0xf7,0x1f,0x32},
	{0xf3,0x00,0x1d,0x20},
	{0x00,0xf4,0x10,0x38},
	{0xf1,0xf7,0x1f,0x32},
	{0xf3,0x00,0x1d,0x20},
	{0xfc,0xfb,0x14,0x2a}
   },
   {
	{0x00,0x00,0x00,0x00},	/* HiVision */
	{0x00,0xf4,0x10,0x38},
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x25,0x18},
	{0xf7,0x06,0x19,0x14},
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x25,0x18},
	{0xee,0x0c,0x22,0x08}
   },
   {
	{0x00,0xf4,0x10,0x38},	/* PAL-M */
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x10,0x18},
	{0xf7,0x06,0x19,0x14},
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x25,0x18},
	{0xeb,0x04,0x25,0x18},
	{0xeb,0x15,0x25,0xf6}
   },
   {
	{0x00,0xf4,0x10,0x38},	/* PAL-N */
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x10,0x18},
	{0xf7,0x06,0x19,0x14},
	{0x00,0xf4,0x10,0x38},
	{0xeb,0x04,0x25,0x18},
	{0xeb,0x04,0x25,0x18},
	{0xeb,0x15,0x25,0xf6}
   }
};

static const unsigned char SiS310_TVYFilter2[5][9][7] =
{
   {
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},	/* NTSC */
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0x01,0x01,0xFC,0xF8,0x08,0x26,0x38},
	{0xFF,0xFF,0xFC,0x00,0x0F,0x22,0x28}
   },
   {
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},   /* PAL */
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0x01,0x01,0xFC,0xF8,0x08,0x26,0x38},
	{0xFF,0xFF,0xFC,0x00,0x0F,0x22,0x28}
   },
   {
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},	/* HiVision */
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22},
	{0x00,0x00,0x00,0xF4,0xFF,0x1C,0x22}
   },
   {
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46}, 	/* PAL-M */
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0x01,0x01,0xFC,0xF8,0x08,0x26,0x38},
	{0xFF,0xFF,0xFC,0x00,0x0F,0x22,0x28}
   },
   {
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},	/* PAL-N */
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0xFF,0x03,0x02,0xF6,0xFC,0x27,0x46},
	{0x01,0x02,0xFE,0xF7,0x03,0x27,0x3C},
	{0x01,0x01,0xFC,0xF8,0x08,0x26,0x38},
	{0xFF,0xFF,0xFC,0x00,0x0F,0x22,0x28}
   }
};

static const unsigned char SiS310_TVPhaseIncr1[3][2][4] =
{
   {
	{0x21,0xed,0xba,0x08},
	{0x21,0xed,0xba,0x08}
   },
   {
	{0x2a,0x05,0xe3,0x00},
	{0x2a,0x05,0xe3,0x00}
   },
   {
	{0x2a,0x05,0xd3,0x00},
	{0x2a,0x05,0xd3,0x00}
   }
};

static const unsigned char SiS310_TVPhaseIncr2[3][2][4] =
{
   {
	{0x21,0xf0,0x7b,0xd6},
	{0x21,0xf0,0x7b,0xd6}
   },
   {
	{0x2a,0x0a,0x41,0xe9},
	{0x2a,0x0a,0x41,0xe9}
   },
   {
	{0x2a,0x05,0xd3,0x00},
	{0x2a,0x05,0xd3,0x00}
   }
};

/**************************************************************/
/* CUSTOM TIMING DATA --------------------------------------- */
/**************************************************************/

/* Inventec / Compaq Presario 3045US, 3017 */

static const struct SiS_LCDData SiS310_ExtCompaq1280x1024Data[] =
{
	{  211,  60,1024, 501,1688,1066},
	{  211,  60,1024, 508,1688,1066},
	{  211,  60,1024, 501,1688,1066},
	{  211,  60,1024, 508,1688,1066},
	{   32,  15,1696, 501,1696,1066},
	{  212,  75,1024, 621,1696,1066},
	{    4,   3,1696, 810,1696,1066},
	{    1,   1,1696,1066,1696,1066}
};

/* Asus A2xxxH _2 */

static const struct SiS_Part2PortTbl SiS310_CRT2Part2_Asus1024x768_3[] =
{
	{{0x25,0x13,0xc9,0x25,0xff,0x59,0x45,0x09,0x07,0xf9,0x09,0x24}},
	{{0x2c,0x13,0x9a,0x25,0xff,0x59,0x45,0x09,0x07,0xf9,0x09,0x24}},
	{{0x25,0x13,0xc9,0x25,0xff,0x59,0x45,0x09,0x07,0xf9,0x09,0x24}},
	{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{{0x38,0x13,0x13,0x25,0xff,0x59,0x45,0x09,0x07,0xf9,0x09,0x24}},
	{{0x38,0x13,0x16,0x25,0xff,0x5a,0x45,0x0a,0x07,0xfa,0x0a,0x24}},
	{{0x36,0x13,0x13,0x25,0xff,0x5a,0x45,0x0a,0x07,0xfa,0x0a,0x24}},
	{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{{0x25,0x13,0xc9,0x25,0xff,0x59,0x45,0x09,0x07,0xf9,0x09,0x24}}
};




