/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#ifndef __STRING_H_
#define __STRING_H_

#include "sys/cdefs.h"

#include <stddef.h>

__BEGIN_DECLS

/**
 * The memcmp() function compares byte string s1 against byte string s2.  Both strings are assumed to be n bytes long.
 *
 * @param string one
 * @param string two
 * @param number of bytes
 * @return zero if the two strings are identical, otherwise returns the difference between the first two differing
 *         bytes (treated as unsigned char values, so that `\200' is greater than `\0', for example).  Zero-length
 *         strings are always identical.
 */
int memcmp(const void* s1, const void* s2, size_t n);
/**
 * The memcpy() function copies n bytes from memory area src to memory area dst.  If dst and src overlap, behavior
 * is undefined.  Applications in which dst and src might overlap should use memmove(3) instead.
 *
 * @param dst target to copy src
 * @param src copied to dst
 * @param n number of bytes to copy
 * @return the original value of dst
 */
void* memcpy(void* __restrict dst, const void* __restrict src, size_t n);
/**
 * The memmove() function copies len bytes from string src to string dst.  The two strings may overlap; the copy
 * is always done in a non-destructive manner.
 *
 * @param dst target to copy src
 * @param src copied to dst
 * @param len number of bytes to copy
 * @return the original value of dst
 */
void* memmove(void* dst, const void* src, size_t len);
/**
 * he memset() function writes len bytes of value c (converted to an unsigned char) to the string b.
 *
 * @param b string to be written
 * @param c character used to write in b
 * @param len number of bytes to write
 * @return its first argument
 */
void* memset(void* b, int c, size_t len);
/**
 * The strlen() function computes the length of the string s.
 *
 * @param string to get length from
 * @return The strlen() function returns the number of characters that precede the terminating NUL character.
 */
size_t strlen(const char* string);
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
/**
 * The strcat() and strncat() functions append a copy of the null-terminated string src to the end of the
 * null-terminated string dst, then add a terminating `\0'. The string dst must have sufficient space to hold
 * the result.
 *
 * The source and destination strings should not overlap, as the behavior is undefined.
 *
 * @param dst target to append src
 * @param src appended string
 * @return the pointer to dst
 */
char *strcat(char *dst, const char *src);

__END_DECLS

#endif /* __STRING_H_ */
