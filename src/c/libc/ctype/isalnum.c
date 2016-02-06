#include <ctype.h>

int isalnum(int ch) {
    return isalpha(ch) || isdigit(ch);
}
