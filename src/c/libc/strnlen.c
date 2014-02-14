/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strnlen()
 */

#include "../includes/string.h"

size_t strnlen(const char *s, size_t maxlen) {
    const char *ss = s;

    /* Important: the maxlen test must precede the reference through ss;
       since the byte beyond the maximum may segfault */
    while ((maxlen > 0) && *ss) {
        ss++;
        maxlen--;
    }
    return ss - s;
}
