/*
 * From klibc.
 */

#include "../include/string.h"

char *strcat(char *dst, const char *src) {
    strcpy(strchr(dst, END_OF_STRING), src);
    return dst;
}
