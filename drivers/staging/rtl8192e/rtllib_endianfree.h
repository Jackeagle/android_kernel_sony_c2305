#ifndef __INC_ENDIANFREE_H
#define __INC_ENDIANFREE_H

/*
 *	Call endian free function when
 *		1. Read/write packet content.
 *		2. Before write integer to IO.
 *		3. After read integer from IO.
 */

#define __MACHINE_LITTLE_ENDIAN 1234    /* LSB first: i386, vax */
#define __MACHINE_BIG_ENDIAN    4321    /* MSB first: 68000, ibm, net, ppc */

#define BYTE_ORDER __MACHINE_LITTLE_ENDIAN

#if BYTE_ORDER == __MACHINE_LITTLE_ENDIAN
#define EF1Byte(_val)			((u8)(_val))
#define EF2Byte(_val)			((u16)(_val))
#define EF4Byte(_val)			((u32)(_val))

#else
#define EF1Byte(_val)			((u8)(_val))
#define EF2Byte(_val)			\
	(((((u16)(_val))&0x00ff)<<8)|((((u16)(_val))&0xff00)>>8))
#define EF4Byte(_val)			\
	(((((u32)(_val))&0x000000ff)<<24)|\
	((((u32)(_val))&0x0000ff00)<<8)|\
	((((u32)(_val))&0x00ff0000)>>8)|\
	((((u32)(_val))&0xff000000)>>24))
#endif

#define ReadEF1Byte(_ptr)		EF1Byte(*((u8 *)(_ptr)))
#define ReadEF2Byte(_ptr)		EF2Byte(*((u16 *)(_ptr)))
#define ReadEF4Byte(_ptr)		EF4Byte(*((u32 *)(_ptr)))

#define WriteEF1Byte(_ptr, _val)	(*((u8 *)(_ptr))) = EF1Byte(_val)
#define WriteEF2Byte(_ptr, _val)	(*((u16 *)(_ptr))) = EF2Byte(_val)
#define WriteEF4Byte(_ptr, _val)	(*((u32 *)(_ptr))) = EF4Byte(_val)
#if BYTE_ORDER == __MACHINE_LITTLE_ENDIAN
#define H2N1BYTE(_val)	((u8)(_val))
#define H2N2BYTE(_val)	(((((u16)(_val))&0x00ff)<<8)|\
			((((u16)(_val))&0xff00)>>8))
#define H2N4BYTE(_val)	(((((u32)(_val))&0x000000ff)<<24)|\
			((((u32)(_val))&0x0000ff00)<<8)	|\
			((((u32)(_val))&0x00ff0000)>>8)	|\
			((((u32)(_val))&0xff000000)>>24))
#else
#define H2N1BYTE(_val)			((u8)(_val))
#define H2N2BYTE(_val)			((u16)(_val))
#define H2N4BYTE(_val)			((u32)(_val))
#endif

#if BYTE_ORDER == __MACHINE_LITTLE_ENDIAN
#define N2H1BYTE(_val)	((u8)(_val))
#define N2H2BYTE(_val)	(((((u16)(_val))&0x00ff)<<8)|\
			((((u16)(_val))&0xff00)>>8))
#define N2H4BYTE(_val)	(((((u32)(_val))&0x000000ff)<<24)|\
			((((u32)(_val))&0x0000ff00)<<8)	|\
			((((u32)(_val))&0x00ff0000)>>8)	|\
			((((u32)(_val))&0xff000000)>>24))
#else
#define N2H1BYTE(_val)			((u8)(_val))
#define N2H2BYTE(_val)			((u16)(_val))
#define N2H4BYTE(_val)			((u32)(_val))
#endif

#define BIT_LEN_MASK_32(__BitLen) (0xFFFFFFFF >> (32 - (__BitLen)))
#define BIT_OFFSET_LEN_MASK_32(__BitOffset, __BitLen)			\
	(BIT_LEN_MASK_32(__BitLen) << (__BitOffset))

#define LE_P4BYTE_TO_HOST_4BYTE(__pStart) (EF4Byte(*((u32 *)(__pStart))))

#define LE_BITS_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
	( \
	  (LE_P4BYTE_TO_HOST_4BYTE(__pStart) >> (__BitOffset)) \
	  & \
	  BIT_LEN_MASK_32(__BitLen) \
	)

#define LE_BITS_CLEARED_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
	( \
	  LE_P4BYTE_TO_HOST_4BYTE(__pStart) \
	  & \
	  (~BIT_OFFSET_LEN_MASK_32(__BitOffset, __BitLen)) \
	)

#define SET_BITS_TO_LE_4BYTE(__pStart, __BitOffset, __BitLen, __Value) \
	*((u32 *)(__pStart)) = \
	EF4Byte( \
	LE_BITS_CLEARED_TO_4BYTE(__pStart, __BitOffset, __BitLen) \
	| \
	((((u32)__Value) & BIT_LEN_MASK_32(__BitLen)) << (__BitOffset)) \
	);


#define BIT_LEN_MASK_16(__BitLen) \
	(0xFFFF >> (16 - (__BitLen)))

#define BIT_OFFSET_LEN_MASK_16(__BitOffset, __BitLen) \
	(BIT_LEN_MASK_16(__BitLen) << (__BitOffset))

#define LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
	(EF2Byte(*((u16 *)(__pStart))))

#define LE_BITS_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
	( \
	  (LE_P2BYTE_TO_HOST_2BYTE(__pStart) >> (__BitOffset)) \
	  & \
	  BIT_LEN_MASK_16(__BitLen) \
	)

#define LE_BITS_CLEARED_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
	( \
	  LE_P2BYTE_TO_HOST_2BYTE(__pStart) \
	  & \
	  (~BIT_OFFSET_LEN_MASK_16(__BitOffset, __BitLen)) \
	)

#define SET_BITS_TO_LE_2BYTE(__pStart, __BitOffset, __BitLen, __Value) \
	*((u16 *)(__pStart)) = \
	EF2Byte( \
		LE_BITS_CLEARED_TO_2BYTE(__pStart, __BitOffset, __BitLen) \
		| ((((u16)__Value) & BIT_LEN_MASK_16(__BitLen)) <<	\
		(__BitOffset)) \
	);

#define BIT_LEN_MASK_8(__BitLen) \
	(0xFF >> (8 - (__BitLen)))

#define BIT_OFFSET_LEN_MASK_8(__BitOffset, __BitLen) \
	(BIT_LEN_MASK_8(__BitLen) << (__BitOffset))

#define LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
	(EF1Byte(*((u8 *)(__pStart))))

#define LE_BITS_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
	( \
	  (LE_P1BYTE_TO_HOST_1BYTE(__pStart) >> (__BitOffset)) \
	  & \
	  BIT_LEN_MASK_8(__BitLen) \
	)

#define LE_BITS_CLEARED_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
	( \
	  LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
	  & \
	  (~BIT_OFFSET_LEN_MASK_8(__BitOffset, __BitLen)) \
	)

#define SET_BITS_TO_LE_1BYTE(__pStart, __BitOffset, __BitLen, __Value)	\
	*((u8 *)(__pStart)) = EF1Byte(					\
		LE_BITS_CLEARED_TO_1BYTE(__pStart, __BitOffset, __BitLen) \
		| ((((u8)__Value) & BIT_LEN_MASK_8(__BitLen)) <<	\
		(__BitOffset))						\
	);

#define	N_BYTE_ALIGMENT(__Value, __Aligment)			\
	 ((__Aligment == 1) ? (__Value) : (((__Value + __Aligment - 1) / \
	__Aligment) * __Aligment))
#endif
