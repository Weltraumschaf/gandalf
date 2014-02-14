/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strlcpy.c
 */

#include "../includes/string.h"
#include "../includes/compiler.h"

size_t strlcpy(char *dst, const char *src, size_t size) {
    size_t bytes = 0;
    char *q = dst;
    const char *p = src;
    char ch;

    while ((ch = *p++)) {
        if (bytes + 1 < size) {
            *q++ = ch;
        }

        bytes++;
    }

    /* If size == 0 there is no space for a final null... */
    if (size) {
        *q = '\0';
    }

    return bytes;
}
