#ifndef __STDIO_H_
#define __STDIO_H_

#include "sys/cdefs.h"

__BEGIN_DECLS

/**
 * The printf utility formats and prints its arguments, after the first, under control of the format.
 * The format is a character string which contains three types of objects: plain characters, which are
 * simply copied to standard output, character escape sequences which are converted and copied to the
 * standard output, and format specifications, each of which causes printing of the next successive argument.
 *
 * @param format the format stirng
 * @return
 */
int printf(const char* restrict format, ...);
int putchar(int ic);
int puts(const char* string);
void print(const char* string);
void println(const char* string);

__END_DECLS

#endif /* __STDIO_H_ */
