struct alphatrack_icmd {
	unsigned char cmd[12];
};

struct alphatrack_ocmd {
	unsigned char cmd[8];
};

/* These are unused by the present driver but provide documentation for the
 * userspace API.
 */
enum LightID {
	LIGHT_EQ = 0,
	LIGHT_OUT,
	LIGHT_F2,
	LIGHT_SEND,
	LIGHT_IN,
	LIGHT_F1,
	LIGHT_PAN,
	LIGHT_UNDEF1,
	LIGHT_UNDEF2,
	LIGHT_SHIFT,
	LIGHT_TRACKMUTE,
	LIGHT_TRACKSOLO,
	LIGHT_TRACKREC,
	LIGHT_READ,
	LIGHT_WRITE,
	LIGHT_ANYSOLO,
	LIGHT_AUTO,
	LIGHT_F4,
	LIGHT_RECORD,
	LIGHT_WINDOW,
	LIGHT_PLUGIN,
	LIGHT_F3,
	LIGHT_LOOP
};

#define BUTTONMASK_BATTERY     0x00004000
#define BUTTONMASK_BACKLIGHT   0x00008000
#define BUTTONMASK_FASTFORWARD 0x04000000
#define BUTTONMASK_TRACKMUTE   0x00040000
#define BUTTONMASK_TRACKSOLO   0x00800000
#define BUTTONMASK_TRACKLEFT   0x80000000
#define BUTTONMASK_RECORD      0x02000000
#define BUTTONMASK_SHIFT       0x20000000
#define BUTTONMASK_PUNCH       0x00800000
#define BUTTONMASK_TRACKRIGHT  0x00020000
#define BUTTONMASK_REWIND      0x01000000
#define BUTTONMASK_STOP        0x10000000
#define BUTTONMASK_LOOP        0x00010000
#define BUTTONMASK_TRACKREC    0x00001000
#define BUTTONMASK_PLAY        0x08000000
#define BUTTONMASK_TOUCH1      0x00000008
#define BUTTONMASK_TOUCH2      0x00000010
#define BUTTONMASK_TOUCH3      0x00000020

#define BUTTONMASK_PRESS1      0x00000009
#define BUTTONMASK_PRESS2      0x00008010
#define BUTTONMASK_PRESS3      0x00002020

/* last 3 bytes are the slider position
 * 40 is the actual slider moving, the most sig bits, and 3 lsb
 */

#define BUTTONMASK_FLIP         0x40000000
#define BUTTONMASK_F1           0x00100000
#define BUTTONMASK_F2           0x00400000
#define BUTTONMASK_F3           0x00200000
#define BUTTONMASK_F4           0x00080000
#define BUTTONMASK_PAN          0x00000200
#define BUTTONMASK_SEND         0x00000800
#define BUTTONMASK_EQ           0x00004000
#define BUTTONMASK_PLUGIN       0x00000400
#define BUTTONMASK_AUTO         0x00000100

/* #define BUTTONMASK_FOOTSWITCH FIXME */
