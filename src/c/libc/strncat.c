/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

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
