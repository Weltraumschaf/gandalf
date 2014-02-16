#include <stdbool.h>
#include <stdarg.h>
#include "../include/stdio.h"
#include "../include/string.h"

#if defined(__is_myos_kernel)
#include "../../kernel/tty.h"
#endif

static void print_string(const char* data, size_t data_length) {
    for (size_t i = 0; i < data_length; i++) {
        putchar((int) ((const unsigned char*) data)[i]);
    }
}

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while (*format != END_OF_STRING) {
        if (*format != '%') {
print_c:
            amount = 1;
            while (format[amount] && format[amount] != '%') {
                amount++;
            }

            print_string(format, amount);
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format;

        if (*(++format) == '%') {
            goto print_c;
        }

        if (rejected_bad_specifier) {
incomprehensible_conversion:
            rejected_bad_specifier = true;
            format = format_begun_at;
            goto print_c;
        }

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            print_string(&c, sizeof (c));
        } else if (*format == 's') {
            format++;
            const char* s = va_arg(parameters, const char*);
            print_string(s, strlen(s));
        } else {
            goto incomprehensible_conversion;
        }
    }

    va_end(parameters);

    return written;
}
