#include "../include/string.h"

size_t strlen(const char* string) {
    size_t length;

    for(length = 0; *string != '\0'; ++string) {
        ++length;
    }

    return length;
}
