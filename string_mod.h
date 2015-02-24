#ifndef __ASM_ARM_STRING_MOD_H
#define __ASM_ARM_STRING_MOD_H

#ifdef	__aarch64__
typedef unsigned long		__kernel_size_t;
typedef long			__kernel_ssize_t;
typedef long			__kernel_ptrdiff_t;
#else
typedef unsigned int		__kernel_size_t;
typedef int			__kernel_ssize_t;
typedef int			__kernel_ptrdiff_t;
#endif

extern void * memcpy(void *, const void *, __kernel_size_t);
extern void * memset(void *, int, __kernel_size_t);

#endif /* __ASM_ARM_STRING_MOD_H */
