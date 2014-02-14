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
