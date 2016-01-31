#pragma once

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

#define SDTIO_HAS_FILE_IO 0

/**
 * Indicates end of file.
 */
#define EOF = -1

// typedef struct __stdio_file FILE;
//
// struct __stdio_file {
//    int fd;
//    int flags;
//    uint32_t bs; /* read: bytes in buffer */
//    uint32_t bm; /* position in buffer */
//    uint32_t buflen; /* length of buf */
//    char *buf;
//    struct __stdio_file *next; /* for fflush */
//    pid_t popen_kludge;
//    unsigned char ungetbuf;
//    char ungotten;
//};
//
// extern FILE *stdin, *stdout, *stderr;

/**
 * The printf utility formats and prints its arguments, after the first, under
 * control of the format.
 * The format is a character string which contains three types of objects: plain
 * characters, which are
 * simply copied to standard output, character escape sequences which are
 * converted and copied to the
 * standard output, and format specifications, each of which causes printing of
 * the next successive argument.
 *
 * @param format the format stirng
 * @return
 */
int printf(const char *restrict format, ...);
// int fprintf(FILE * __restrict stream, const char * __restrict format, ...);
/**
 * The putchar() function is identical to putc() with an output stream of
 * stdout.
 *
 * @param ic character to put
 * @return the character written
 */
int putchar(int ic);
/**
 * The function puts() writes the string and a terminating newline character, to
 * the stream stdout.
 *
 * @param string to be written
 * @return a nonnegative integer on success and EOF on error
 */
int puts(const char *string);
/**
 * Same as println(), but without additional new line at the end of string
 * appended.
 *
 * @param string
 */
void print(const char *string);
/**
 * Same as puts().
 *
 * @param string to be written
 */
void println(const char *string);

__END_DECLS
