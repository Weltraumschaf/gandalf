/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strrchr.c
 */

#include "../includes/string.h"
#include "../includes/compiler.h"

char *strrchr(const char *s, int c) {
    const char *found = NULL;

    while (*s) {
        if (*s == (char) c)
            found = s;
        s++;
    }

    return (char *) found;
}

__ALIAS(char *, rindex, (const char *, int), strrchr)
