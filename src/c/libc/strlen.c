/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strlen()
 */

#include "../includes/string.h"

size_t strlen(const char *s) {
    const char *ss = s;

    while (*ss) {
        ss++;
    }

    return ss - s;
}
