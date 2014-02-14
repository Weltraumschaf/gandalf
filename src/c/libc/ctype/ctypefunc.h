/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * ctype/ctype.h
 *
 * Common header for out-of-line ctype functions
 */

#define __CTYPE_NO_INLINE
#include "../../includes/ctype.h"

#define CTYPEFUNC(X)				\
  int X(int c) {				\
    return __ctype_##X(c);			\
  }
