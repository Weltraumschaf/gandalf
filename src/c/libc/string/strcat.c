#include "../include/string.h"

char *strcat(char *dst, const char *src) {
    strcpy(strchr(dst, NULL), src);
    return dst;
}
