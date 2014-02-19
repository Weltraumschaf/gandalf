#ifndef __STDIO_H_
#define __STDIO_H_

#include "../../include/sys/cdefs.h"

__BEGIN_DECLS

/**
 * Indicates end of file.
 */
#define EOF = -1

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
/**
 * The putchar() function is identical to putc() with an output stream of stdout.
 *
 * @param ic character to put
 * @return the character written
 */
int putchar(int ic);
/**
 * The function puts() writes the string and a terminating newline character, to the stream stdout.
 *
 * @param string to be written
 * @return a nonnegative integer on success and EOF on error
 */
int puts(const char* string);
/**
 * Same as println(), but without additional new line at the end of string appended.
 *
 * @param string
 */
void print(const char* string);
/**
 * Same as puts().
 *
 * @param string to be written
 */
void println(const char* string);

__END_DECLS

#endif /* __STDIO_H_ */
