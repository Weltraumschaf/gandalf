/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strlcat.c
 */

#include "../includes/string.h"
#include "../includes/compiler.h"

size_t strlcat(char *dst, const char *src, size_t size) {
    size_t bytes = 0;
    char *q = dst;
    const char *p = src;
    char ch;

    while (bytes < size && *q) {
        q++;
        bytes++;
    }

    if (bytes == size) {
        return (bytes + strlen(src));
    }

    while ((ch = *p++)) {
        if (bytes + 1 < size) {
            *q++ = ch;
        }

        bytes++;
    }

    *q = '\0';
    return bytes;
}
