/*
 * strcat.c
 */

#include "../includes/string.h"

char *strcat(char *dst, const char *src) {
    strcpy(strchr(dst, '\0'), src);
    return dst;
}
