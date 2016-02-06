#include <ctype.h>

int ispunct(int ch) {
    return isgraph(ch) && !isalnum(ch);
}
