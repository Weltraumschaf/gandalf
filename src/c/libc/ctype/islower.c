#include <ctype.h>

int islower(int ch) {
    return (unsigned)ch - 'a' < 26;
}
