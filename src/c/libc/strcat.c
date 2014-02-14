/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided 
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on 
 * learning to make a kernel.
 */

/*
 * strcat.c
 */

#include "../includes/string.h"

char *strcat(char *dst, const char *src) {
    strcpy(strchr(dst, '\0'), src);
    return dst;
}
