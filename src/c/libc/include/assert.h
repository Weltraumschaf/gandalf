#pragma once

__BEGIN_DECLS

/**
 * The assert() macro is used to test for errors. If exp evaluates to zero,
 * assert() writes information to stderr and exits the program. If the macro
 * NDEBUG is defined, the assert() macros will be ignored.
 *
 * @param exp any expression
 */
void assert(exp);

__END_DECLS
