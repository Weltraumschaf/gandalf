/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on
 * learning to make a kernel.
 */

/*
 * sys/time.h
 */

#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include "../extern.h"
#include <stddef.h>
#include "types.h"
#include "../linux/time.h"

/* The 2.6.20 Linux headers always #define FD_ZERO __FD_ZERO, etc, in
   <linux/time.h> but not all architectures define the
   double-underscore ones, except __NFDBITS, __FD_SETSIZE and
   __FDSET_LONGS which are defined in <linux/posix_types.h>.

   Unfortunately, some architectures define the double-underscore ones
   as inlines, so we can't use a simple #ifdef test.  Thus, the only
   safe option remaining is to #undef the top-level macros. */

#undef FD_ZERO
#undef FD_SET
#undef FD_CLR
#undef FD_ISSET

__extern void *memset(void *, int, size_t);
static inline void FD_ZERO(fd_set *__fdsetp)
{
	memset(__fdsetp, 0, sizeof(fd_set));
}
static inline void FD_SET(int __fd, fd_set *__fdsetp)
{
	__fdsetp->fds_bits[__fd/BITS_PER_LONG] |=
		(1UL << (__fd % BITS_PER_LONG));
}
static inline void FD_CLR(int __fd, fd_set *__fdsetp)
{
	__fdsetp->fds_bits[__fd/BITS_PER_LONG] &=
		~(1UL << (__fd % BITS_PER_LONG));
}
static inline int FD_ISSET(int __fd, fd_set *__fdsetp)
{
	return (__fdsetp->fds_bits[__fd/BITS_PER_LONG] >>
		(__fd % BITS_PER_LONG)) & 1;
}

__extern int gettimeofday(struct timeval *, struct timezone *);
__extern int settimeofday(const struct timeval *, const struct timezone *);
__extern int getitimer(int, struct itimerval *);
__extern int setitimer(int, const struct itimerval *, struct itimerval *);
__extern int utimes(const char *, const struct timeval *);

#endif				/* _SYS_TIME_H */
