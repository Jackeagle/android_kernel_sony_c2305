#ifndef __PARISC_SPECIAL_INSNS_H
#define __PARISC_SPECIAL_INSNS_H

#define mfctl(reg)	({		\
	unsigned long cr;		\
	__asm__ __volatile__(		\
		"mfctl " #reg ",%0" :	\
		 "=r" (cr)		\
	);				\
	cr;				\
})

#define mtctl(gr, cr) \
	__asm__ __volatile__("mtctl %0,%1" \
		: /* no outputs */ \
		: "r" (gr), "i" (cr) : "memory")

/* these are here to de-mystefy the calling code, and to provide hooks */
/* which I needed for debugging EIEM problems -PB */
#define get_eiem() mfctl(15)
static inline void set_eiem(unsigned long val)
{
	mtctl(val, 15);
}

#define mfsp(reg)	({		\
	unsigned long cr;		\
	__asm__ __volatile__(		\
		"mfsp " #reg ",%0" :	\
		 "=r" (cr)		\
	);				\
	cr;				\
})

#define mtsp(gr, cr) \
	__asm__ __volatile__("mtsp %0,%1" \
		: /* no outputs */ \
		: "r" (gr), "i" (cr) : "memory")

#endif /* __PARISC_SPECIAL_INSNS_H */
