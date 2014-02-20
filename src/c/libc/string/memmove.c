/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#include <string.h>

void* memmove(void* dst, const void* src, size_t len) {
    unsigned char* _dst = (unsigned char*) dst;
    const unsigned char* _src = (const unsigned char*) src;

    if (_dst < _src) {
        for (size_t i = 0; i < len; i++) {
            _dst[i] = _src[i];
        }
    } else {
        for (size_t i = len; i != 0; i--) {
            _dst[i - 1] = _src[i - 1];
        }
    }

    return dst;
}
