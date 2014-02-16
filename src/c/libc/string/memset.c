/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#include "../include/string.h"

void* memset(void* b, int c, size_t len){
    unsigned char* buf = (unsigned char*) b;

    for (size_t i = 0; i < len; i++) {
        buf[i] = (unsigned char) c;
    }

    return b;
}
