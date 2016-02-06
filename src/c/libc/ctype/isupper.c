#include <ctype.h>

int isupper(int ch) {
    return (unsigned)ch - 'A' < 26;
}
