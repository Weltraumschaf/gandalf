/*
 * From klibc.
 */

#include "../include/sys/cdefs.h"

char *strchr(const char *haystack, int needle) {
    while (*haystack != (char) needle) {
        if (!*haystack) {
            return NULL;
        }

        haystack++;
    }

    return (char *) haystack;
}
