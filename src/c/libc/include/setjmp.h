#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * The function longjmp() causes the program to start executing code at the
 * point of the last call to setjmp(). envbuf is usually set through a call to
 * setjmp(). status becomes the return value of setjmp() and can be used to
 * figure out where longjmp() came from. status should not be set to zero.
 */
void longjmp(jmp_buf envbuf, int status);

/**
 * The setjmp() function saves the system stack in envbuf for use by a later
 * call to longjmp(). When you first call setjmp(), its return value is zero.
 * Later, when you call longjmp(), the second argument of longjmp() is what the
 * return value of setjmp() will be. Confused? Read about longjmp().
 */
int setjmp(jmp_buf envbuf);

__END_DECLS
