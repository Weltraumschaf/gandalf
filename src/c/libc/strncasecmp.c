/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strncasecmp.c
 */

#include "../includes/string.h"
#include "../includes/ctype.h"

int strncasecmp(const char *s1, const char *s2, size_t n) {
    const unsigned char *c1 = (const unsigned char *) s1;
    const unsigned char *c2 = (const unsigned char *) s2;
    unsigned char ch;
    int d = 0;

    while (n--) {
        /* toupper() expects an unsigned char (implicitly cast to int)
           as input, and returns an int, which is exactly what we want. */
        d = toupper(ch = *c1++) - toupper(*c2++);

        if (d || !ch) {
            break;
        }
    }

    return d;
}
