#ifndef __STDIO_H_
#define __STDIO_H_
 
#include "sys/cdefs.h"
 
__BEGIN_DECLS
 
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
 
__END_DECLS
 
#endif /* __STDIO_H_ */
