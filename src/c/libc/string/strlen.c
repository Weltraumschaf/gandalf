/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#include <string.h>

size_t strlen(const char* string) {
    size_t length;

    for(length = 0; *string != END_OF_STRING; ++string) {
        ++length;
    }

    return length;
}
