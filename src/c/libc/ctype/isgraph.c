#include <ctype.h>

int isgraph(int ch) {
    return (unsigned)ch - 0x21 < 0x5e;
}
