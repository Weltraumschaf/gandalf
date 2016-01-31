#pragma once

#include <stddef.h> /* for size_t */
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

extern void *mmap(void *__addr, size_t __len, int __prot, int __flags, int __fd,
                  off_t __offset);

extern int munmap(void *__addr, size_t __len) __THROW;
extern int mprotect(void *__addr, size_t __len, int __prot) __THROW;
extern int msync(void *__addr, size_t __len, int __flags) __THROW;
extern void *mremap(void *__addr, size_t __old_len, size_t __new_len,
                    unsigned long __may_move) __THROW;
extern int mincore(void *__start, size_t __len, unsigned char *__vec);

__END_DECLS
