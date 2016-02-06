#include <stdio.h>

#include "../../kernel/tty.h"

int putchar(int ic) {
    char c = (char)ic;

    tty_write(&c);

    return ic;
}
