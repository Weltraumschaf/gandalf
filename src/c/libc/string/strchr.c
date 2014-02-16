/*
 * From klibc.
 */

#include "../include/string.h"

char *strchr(const char *haystack, int needle) {
    while (*haystack != (char) needle) {
        if (!*haystack) {
            return NULL;
        }

        haystack++;
    }

    return (char *) haystack;
}
