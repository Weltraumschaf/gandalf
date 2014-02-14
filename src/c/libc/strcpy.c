/*
 * strcpy.c
 *
 * strcpy()
 */

#include "../includes/string.h"

char *strcpy(char *dst, const char *src) {
    char *q = dst;
    const char *p = src;
    char ch;

    do {
        *q++ = ch = *p++;
    } while (ch);

    return dst;
}
