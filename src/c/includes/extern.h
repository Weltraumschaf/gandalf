/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * klibc/extern.h
 */

#ifndef _KLIBC_EXTERN_H
#define _KLIBC_EXTERN_H

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define __alias(x) __attribute__((weak, alias(x)))

#endif				/* _KLIBC_EXTERN_H */
