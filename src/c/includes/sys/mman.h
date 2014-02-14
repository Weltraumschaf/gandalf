/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on
 * learning to make a kernel.
 */

/*
 * sys/mman.h
 */

#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H

#include "../extern.h"
#include "types.h"
#include "../linux/asm/mman.h"

#define MAP_FAILED ((void *)-1)

__extern void *mmap(void *, size_t, int, int, int, off_t);
__extern int munmap(void *, size_t);
__extern void *mremap(void *, size_t, size_t, unsigned long);
__extern int shm_open(const char *, int, mode_t);
__extern int shm_unlink(const char *);
__extern int msync(const void *, size_t, int);
__extern int mprotect(const void *, size_t, int);
__extern int mlockall(int);
__extern int munlockall(void);
__extern int mlock(const void *, size_t);
__extern int munlock(const void *, size_t);

#endif				/* _SYS_MMAN_H */
