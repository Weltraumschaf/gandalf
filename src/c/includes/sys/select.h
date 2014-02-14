/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on
 * learning to make a kernel.
 */

/*
 * sys/select.h
 */

#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include "../extern.h"
#include "time.h"
#include "types.h"
#include "../signal.h"

__extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
__extern int pselect(int, fd_set *, fd_set *, fd_set *,
		     const struct timespec *, const sigset_t *);

#endif				/* _SYS_SELECT_H */
