#include <ctype.h>

int isalpha(int ch) {
    return ((unsigned)ch | 32) - 'a' < 26;
}
