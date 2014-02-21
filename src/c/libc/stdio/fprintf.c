#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE * __restrict stream, const char * __restrict format, ...) {
    va_list parameters;
    va_start(stream, parameters, format);

    int written = 0;

    va_end(parameters);

    return written;
}
