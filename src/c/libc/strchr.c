/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strchr.c
 */

#include "../includes/string.h"
#include "../includes/compiler.h"

char *strchr(const char *s, int c) {
    while (*s != (char) c) {
        if (!*s)
            return NULL;
        s++;
    }

    return (char *) s;
}

__ALIAS(char *, index, (const char *, int), strchr)
