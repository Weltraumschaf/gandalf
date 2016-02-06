#pragma once

__BEGIN_DECLS

#undef assert

/**
 * The assert() macro is used to test for errors. If expression evaluates to
 * zero,
 * assert() writes information to stderr and exits the program. If the macro
 * NDEBUG is defined, the assert() macros will be ignored.
 *
 * @param exp any expression
 */

#ifdef NDEBUG
#define assert(expression) (void)0
#else
#define assert(expression)                                                     \
    ((void)((expression) ||                                                    \
            (__assert_fail(#expression, __FILE__, __LINE__, __func__), 0)))
#endif

__END_DECLS
