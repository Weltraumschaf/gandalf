/*
 * strncat.c
 */

#include "../includes/string.h"
#include "../includes/compiler.h"

char *strncat(char *dst, const char *src, size_t n) {
    char *q = strchr(dst, '\0');
    const char *p = src;
    char ch;

    while (n--) {
        *q++ = ch = *p++;

        if (!ch) {
            return dst;
        }
    }

    *q = '\0';

    return dst;
}
