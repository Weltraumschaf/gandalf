#include <stdio.h>

#if defined(__is_gandalf_kernel)
#include "../../kernel/tty.h"
#endif

int putchar(int ic) {
    char c = (char)ic;

#if defined(__is_gandalf_kernel)
    tty_write(&c); // Kernel API call.
#else
    // FIXME: Need to implement a write system call.
    tty_write(&c);
#endif

    return ic;
}
