#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void __assert_fail(const char *expression, const char *file, unsigned int line,
                   const char *function);

void __assert_fail(const char *expression, const char *file, unsigned int line,
                   const char *function) {
    fprintf(stderr, "Assertion failed: %s (%s: %s: %d)\n", expression, file,
            function, line);
    fflush(NULL);
    abort();
}
