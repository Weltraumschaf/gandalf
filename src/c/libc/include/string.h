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
/**
 * The stpcpy() and functions copy the string src to dst (including the terminating `\0' character).
 *
 * @param dst target to copy the string
 * @param src thecooied string
 * @return a pointer to the terminating `\0' character of dst.  If stpncpy() does not terminate dst with a NUL
 *         character, it instead returns a pointer to dst[n] (which does not necessarily refer to a valid memory
 *         location.)
 */
char *strcpy(char *dst, const char *src);
/**
 * The strchr() function locates the first occurrence of needle (converted to a char) in the string pointed to by
 * haystack. The terminating null character is considered to be part of the string; therefore if needle is `\0',
 * the functions locate the terminating `\0'.
 *
 * @param haystack string to search in
 * @param needle character to look for
 * @return a pointer to the located character, or NULL if the character does not appear in the string
 */
char *strchr(const char *haystack, int needle);

__END_DECLS

#endif /* __STRING_H_ */
