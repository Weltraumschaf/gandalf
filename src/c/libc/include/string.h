/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#ifndef __STRING_H_
#define __STRING_H_

#include "sys/cdefs.h"

#include <stddef.h>

__BEGIN_DECLS

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
char *strcpy(char *dst, const char *src);

__END_DECLS

#endif /* __STRING_H_ */
