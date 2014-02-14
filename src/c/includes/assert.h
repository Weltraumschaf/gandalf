/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on
 * learning to make a kernel.
 */

/*
 * assert.h
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#include "compiler.h"

#ifdef NDEBUG

/*
 * NDEBUG doesn't just suppress the faulting behavior of assert(),
 * but also all side effects of the assert() argument.  This behavior
 * is required by the C standard, and allows the argument to reference
 * variables that are not defined without NDEBUG.
 */
#define assert(x) ((void)(0))

#else

extern __noreturn __assert_fail(const char *, const char *, unsigned int);

#define assert(x) ((x) ? (void)0 : __assert_fail(#x, __FILE__, __LINE__))

#endif

#endif				/* _ASSERT_H */
