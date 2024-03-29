#ifndef _ASM_M32R_TYPES_H
#define _ASM_M32R_TYPES_H

#include <asm-generic/int-ll64.h>

/*
 * These aren't exported outside the kernel to avoid name space clashes
 */
#ifdef __KERNEL__

#define BITS_PER_LONG 32

#endif /* __KERNEL__ */

#endif /* _ASM_M32R_TYPES_H */
