/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#include <string.h>

void* memcpy(void* __restrict dst, const void* __restrict src, size_t n) {
    unsigned char* _dst = (unsigned char*) dst;
    const unsigned char* _src = (const unsigned char*) src;

    for (size_t i = 0; i < n; i++) {
        _dst[i] = _src[i];
    }

    return dst;
}
