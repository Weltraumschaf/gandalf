/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

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
