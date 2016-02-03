#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/**
 * Indicates end of file.
 */
#define EOF = -1

/**
 * Seek from beginning of file.
 */
#define SEEK_SET 0
/**
 * Seek from current position.
 */
#define SEEK_CUR 1
/**
 * Seek from end of file.
 */
#define SEEK_END 2

/**
 * Indicates full buffering.
 */
#define _IONBF 0
/**
 * Which means line buffering.
 */
#define _IOLBF 1
/**
 * Which means no buffering.
 */
#define _IOFBF 2

struct __stdio_file;
typedef struct __stdio_file FILE;

extern FILE *stdin, *stdout, *stderr;

/**
 * The clearerr function resets the error flags and EOF indicator for the given
 * stream. When an error occurs, you can use perror() to figure out which error
 * actually occurred.
 */
void clearerr(FILE *stream);

/**
 * The function fclose() closes the given file stream, deallocating any buffers
 * associated with that stream. fclose() returns 0 upon success, and EOF
 * otherwise.
 */
int fclose(FILE *stream);

/**
 * The function feof() returns a nonzero value if the end of the given file
 * stream has been reached.
 */
int feof(FILE *stream);

/**
 * The ferror() function looks for errors with stream, returning zero if no
 * errors have occured, and non-zero if there is an error. In case of an error,
 * use perror() to determine which error has occured.
 */
int ferror(FILE *stream);

/**
 * If the given file stream is an output stream, then fflush() causes the output
 * buffer to be written to the file. If the given stream is of the input type,
 * then fflush() causes the input buffer to be cleared. fflush() is useful when
 * debugging, if a program segfaults before it has a chance to write output to
 * the screen. Calling fflush( stdout ) directly after debugging output will
 * ensure that your output is displayed at the correct time.
 */
int fflush(FILE *stream);

/**
 * The fgetc() function returns the next character from stream, or EOF if the
 * end of file is reached or if there is an error.
 */
int fgetc(FILE *stream);

/**
 * The fgetpos() function stores the file position indicator of the given file
 * stream in the given position variable. The position variable is of type
 * fpos_t (which is defined in stdio.h) and is an object that can hold every
 * possible position in a FILE. fgetpos() returns zero upon success, and a
 * non-zero value upon failure.
 */
int fgetpos(FILE *stream, fpos_t *position);

/**
 * The function fgets() reads up to num - 1 characters from the given file
 * stream and dumps them into str. The string that fgets() produces is always
 * NULL-terminated. fgets() will stop when it reaches the end of a line, in
 * which case str will contain that newline character. Otherwise, fgets() will
 * stop when it reaches num - 1 characters or encounters the EOF character.
 * fgets() returns str on success, and NULL on an error.
 */
char *fgets(char *str, int num, FILE *stream);

/**
 * The fopen() function opens a file indicated by fname and returns a stream
 * associated with that file. If there is an error, fopen() returns NULL. mode
 * is used to determine how the file will be treated (i.e. for input, output,
 * etc)
 *
 * Mode 	Meaning
 * "r" 	Open a text file for reading
 * "w" 	Create a text file for writing
 * "a" 	Append to a text file
 * "rb" 	Open a binary file for reading
 * "wb" 	Create a binary file for writing
 * "ab" 	Append to a binary file
 * "r+" 	Open a text file for read/write
 * "w+" 	Create a text file for read/write
 * "a+" 	Open a text file for read/write
 * "rb+" 	Open a binary file for read/write
 * "wb+" 	Create a binary file for read/write
 * "ab+" 	Open a binary file for read/write
 */
FILE *fopen(const char *fname, const char *mode);

/**
 * The fprintf() function sends information (the arguments) according to the
 * specified format to the file indicated by stream. fprintf() works just like
 * printf() as far as the format goes. The return value of fprintf() is the
 * number of characters outputted, or a negative number if an error occurs. An
 * example:
 * @code
 * char name[20] = "Mary";
 * FILE *out;
 * out = fopen( "output.txt", "w" );
 * if( out != NULL )
 *   fprintf( out, "Hello %s\n", name );
 * @endcode
 */
int fprintf(FILE *stream, const char *format, ...);

/**
 * The function fputc() writes the given character ch to the given output
 * stream. The return value is the character, unless there is an error, in which
 * case the return value is EOF.
 */
int fputc(int ch, FILE *stream);

/**
 * The fputs() function writes an array of characters pointed to by str to the
 * given output stream. The return value is non-negative on success, and EOF on
 * failure.
 */
int fputs(const char *str, FILE *stream);

/**
 * The function fread() reads num number of objects (where each object is size
 * bytes) and places them into the array pointed to by buffer. The data comes
 * from the given input stream. The return value of the function is the number
 * of things read. You can use feof() or ferror() to figure out if an error
 * occurs.
 */
int fread(void *buffer, size_t size, size_t num, FILE *stream);

/**
 * The freopen() function is used to reassign an existing stream to a different
 * file and mode. After a call to this function, the given file stream will
 * refer to fname with access given by mode. The return value of freopen() is
 * the new stream, or NULL if there is an error.
 */
FILE *freopen(const char *fname, const char *mode, FILE *stream);

/**
 * The function fscanf() reads data from the given file stream in a manner
 * exactly like scanf(). The return value of fscanf() is the number of variables
 * that are actually assigned values, or EOF if no assignments could be made.
 */
int fscanf(FILE *stream, const char *format, ...);

/**
 * The function fseek() sets the file position data for the given stream. The
 * origin value should have one of the following values (defined in stdio.h):
 *
 * Name 	    Explanation
 * SEEK_SET 	Seek from the start of the file
 * SEEK_CUR 	Seek from the current location
 * SEEK_END 	Seek from the end of the file
 *
 * fseek() returns zero upon success, non-zero on failure. You can use fseek()
 * to move beyond a file, but not before the beginning. Using fseek() clears the
 * EOF flag associated with that stream.
 */
int fseek(FILE *stream, long offset, int origin);

/**
 * The fsetpos() function moves the file position indicator for the given stream
 * to a location specified by the position object. fpos_t is defined in stdio.h.
 * The return value for fsetpos() is zero upon success, non-zero on failure.
 */
int fsetpos(FILE *stream, const fpos_t *position);

/**
 * The ftell() function returns the current file position for stream, or -1 if
 * an error occurs.
 */
long ftell(FILE *stream);

/**
 * The fwrite() function writes, from the array buffer, count objects of size
 * size to stream. The return value is the number of objects written.
 */
int fwrite(const void *buffer, size_t size, size_t count, FILE *stream);

/**
 * The getc() function returns the next character from stream, or EOF if the end
 * of file is reached. getc() is identical to fgetc(). For example:
 * @code
 * int ch;
 * FILE *input = fopen( "stuff", "r" );
 *
 * ch = getc( input );
 * while( ch != EOF ) {
 *   printf( "%c", ch );
 *   ch = getc( input );
 * }
 * @endcode
 */
int getc(FILE *stream);

/**
 * The getchar() function returns the next character from stdin, or EOF if the
 * end of file is reached.
 */
int getchar(void);

/**
 * The gets() function reads characters from stdin and loads them into str,
 * until a newline or EOF is reached. The newline character is translated into a
 * null termination. The return value of gets() is the read-in string, or NULL
 * if there is an error.
 *
 * Note that gets() does not perform bounds checking, and thus risks overrunning
 * str. For a similar (and safer) function that includes bounds checking, see
 * fgets().
*/
char *gets(char *str);

/**
 * The printf() function prints output to stdout, according to format and other
 arguments passed to printf(). The string format consists of two types of items
 - characters that will be printed to the screen, and format commands that
 define how the other arguments to printf() are displayed. Basically, you
 specify a format string that has text in it, as well as "special" characters
 that map to the other arguments of printf(). For example, this code
 * @code
 * char name[20] = "Bob";
 * int age = 21;
 * printf( "Hello %s, you are %d years old\n", name, age );
 * @endcode
 * displays the following output:
 *
 * "Hello Bob, you are 21 years old"
 *
 *The %s means, "insert the first argument, a string, right here." The %d
 indicates that the second argument (an integer) should be placed there. There
 are different %-codes for different variable types, as well as options to limit
 the length of the variables and whatnot.
 *
 * Code 	Format
 * %c 	character
 * %d 	signed integers
 * %i 	signed integers
 * %e 	scientific notation, with a lowercase "e"
 * %E 	scientific notation, with a uppercase "E"
 * %f 	floating point
 * %g 	use %e or %f, whichever is shorter
 * %G 	use %E or %f, whichever is shorter
 * %o 	octal
 * %s 	a string of characters
 * %u 	unsigned integer
 * %x 	unsigned hexadecimal, with lowercase letters
 * %X 	unsigned hexadecimal, with uppercase letters
 * %p 	a pointer
 * %n 	the argument shall be a pointer to an integer into which is placed
 the number of characters written so far
 * %% 	a '%' sign
 *
 * An integer placed between a % sign and the format command acts as a minimum
 field width specifier, and pads the output with spaces or zeros to make it long
 enough. If you want to pad with zeros, place a zero before the minimum field
 width specifier:
 * @code
 * %012d
 * @endcode
 *
 * You can also include a precision modifier, in the form of a .N where N is
 some number, before the format command:
 * @code
   %012.4d
 * @endcode
 *
 * The precision modifier has different meanings depending on the format command
 being used:
 *
 * - With %e, %E, and %f, the precision modifier lets you specify the number of
 decimal places desired. For example, %12.6f will display a floating number at
 least 12 digits wide, with six decimal places.
 * - With %g and %G, the precision modifier determines the maximum number of
 significant digits displayed.
 * - With %s, the precision modifer simply acts as a maximumfield length, to
 complement the minimum field length that precedes the period.
 *
 * All of printf()'s output is right-justified, unless you place a minus sign
 right after the % sign. For example,
 * @code
 * %-12.4f
 * @endcode
 *
 * will display a floating point number with a minimum of 12 characters, 4
 decimal places, and left justified. You may modify the %d, %i, %o, %u, and %x
 type specifiers with the letter l and the letter h to specify long and short
 data types (e.g. %hd means a short integer). The %e, %f, and %g type specifiers
 can have the letter l before them to indicate that a double follows. The %g,
 %f, and %e type specifiers can be preceded with the character '#' to ensure
 that the decimal point will be present, even if there are no decimal digits.
 The use of the '#' character with the %x type specifier indicates that the
 hexidecimal number should be printed with the '0x' prefix. The use of the '#'
 character with the %o type specifier indicates that the octal value should be
 displayed with a 0 prefix.
 *
 * Inserting a plus sign '+' into the type specifier will force positive values
 to be preceded by a '+' sign. Putting a space character ' ' there will force
 positive values to be preceded by a single space character.
 *
 * You can also include constant escape sequences in the output string.
 *
 * The return value of printf() is the number of characters printed, or a
 negative number if an error occurred.
 */
int printf(const char *format, ...);

/**
 * The putc() function writes the character ch to stream. The return value is
 * the character written, or EOF if there is an error. For example:
 * @code
 * int ch;
 * FILE *input, *output;
 * input = fopen( "tmp.c", "r" );
 * output = fopen( "tmpCopy.c", "w" );
 * ch = getc( input );
 * while( ch != EOF ) {
 *   putc( ch, output );
 *   ch = getc( input );
 * }
 * fclose( input );
 * fclose( output );
 * @endcode
 *
 * generates a copy of the file tmp.c called tmpCopy.c.
 */
int putc(int ch, FILE *stream);

/**
 * The putchar() function writes ch to stdout. The code
 * @code
 * putchar( ch );
 * @endcode
 * is the same as
 * @code
 * putc( ch, stdout );
 * @endcode
 * The return value of putchar() is the written character, or EOF if there is an
 * error.
 */
int putchar(int ch);

/**
 * The function puts() writes str to stdout. puts() returns non-negative on
 * success, or EOF on failure.
 */
int puts(const char *str);

/**
 * The function rename() changes the name of the file oldfname to newfname. The
 * return value of rename() is zero upon success, non-zero on error.
 */
int rename(const char *oldfname, const char *newfname);

/**
 * The function rewind() moves the file position indicator to the beginning of
 * the specified stream, also clearing the error and EOF flags associated with
 * that stream.
 */
void rewind(FILE *stream);

/**
 * The scanf() function reads input from stdin, according to the given format,
 * and stores the data in the other arguments. It works a lot like printf(). The
 * format string consists of control characters, whitespace characters, and
 * non-whitespace characters. The control characters are preceded by a % sign,
 * and are as follows:
 * Control Character    Explanation
 * %c                   a single character
 * %d                   a decimal integer
 * %i                   an integer
 * %e, %f, %g           a floating-point number
 * %o                   an octal number
 * %s                   a string
 * %x                   a hexadecimal number
 * %p                   a pointer
 * %n                   an integer equal to the number of characters read so far
 * %u                   an unsigned integer
 * %[]                  a set of characters
 * %%                   a percent sign
 *
 * scanf() reads the input, matching the characters from format. When a control
 * character is read, it puts the value in the next variable. Whitespace (tabs,
 * spaces, etc) are skipped. Non-whitespace characters are matched to the input,
 * then discarded. If a number comes between the % sign and the control
 * character, then only that many characters will be converted into the
 * variable. If scanf() encounters a set of characters, denoted by the %[]
 * control character, then any characters found within the brackets are read
 * into the variable. The return value of scanf() is the number of variables
 * that were successfully assigned values, or EOF if there is an error.
 *
 * This code snippet repeatedly uses scanf() to read integers and floats from
 * the user. Note that the variable arguments to scanf() are passed in by
 * reference, as denoted by the ampersand (&) preceding each variable:
 * @code
 *  int i;
 *  float f;
 *
 *  while( 1 ) {
 *    printf( "Enter an integer: " );
 *    scanf( "%d", &i );
 *
 *    printf( "Enter a float: " );
 *    scanf( "%f", &f );
 *
 *    printf( "You entered %d and then %f\n", i, f );
 *  }
 * @endcode
 *
 */
int scanf(const char *format, ...);

/**
 * The setbuf() function sets stream to use buffer, or, if buffer is null, turns
 * off buffering. If a non-standard buffer size is used, it should be BUFSIZ
 * characters long.
 */
void setbuf(FILE *stream, char *buffer);

/**
 * The function setvbuf() sets the buffer for stream to be buffer, with a size
 *of size. mode can be:
 *
 *- _IOFBF, which indicates full buffering
 *- _IOLBF, which means line buffering
 *- _IONBF, which means no buffering
 */
int setvbuf(FILE *stream, char *buffer, int mode, size_t size);

/**
 * The perror() function prints str and an implementation-defined error message
 * corresponding to the global variable errno. For example:
 * @code
 * char* input_filename = "not_found.txt";
 * FILE* input = fopen( input_filename, "r" );
 * if( input == NULL ) {
 *   char error_msg[255];
 *   sprintf( error_msg, "Error opening file '%s'", input_filename );
 *   perror( error_msg );
 *   exit( -1 );
 * }
 * @endcode
 * The the file called not_found.txt is not found, this code will produce the
 * following output:
 *
 * "Error opening file 'not_found.txt': No such file or directory"
 */
void perror(const char *str);

/**
 * The remove() function erases the file specified by fname. The return value of
 * remove() is zero upon success, and non-zero if there is an error.
 */
int remove(const char *fname);

/**
 * The sprintf() function is just like printf(), except that the output is sent
 * to buffer. The return value is the number of characters written. For example:
 *
 * @code
 * char string[50];
 * int file_number = 0;
 *
 * sprintf( string, "file.%d", file_number );
 * file_number++;
 * output_file = fopen( string, "w" );
 * @endcode
 *
 * Note that sprintf() does the opposite of a function like atoi() -- where
 * atoi() converts a string into a number, sprintf() can be used to convert a
 * number into a string.
 *
 * For example, the following code uses sprintf() to convert an integer into a
 * string of characters:
 * @code
 * char result[100];
 * int num = 24;
 * sprintf( result, "%d", num );
 * @endcode
 *
 * This code is similar, except that it converts a floating-point number into an
 * array of characters:
 * @code
 * char result[100];
 * float fnum = 3.14159;
 * sprintf( result, "%f", fnum );
 * @endcode
 */
int sprintf(char *buffer, const char *format, ...);

/**
 * The function sscanf() is just like scanf(), except that the input is read
 * from buffer.
 */
int sscanf(const char *buffer, const char *format, ...);

/**
 * The function tempfile() opens a temporary file with an unique filename and
 * returns a pointer to that file. If there is an error, null is returned.
 */
FILE *tmpfile(void);

/**
 * The tmpnam() function creates an unique filename and stores it in name.
 * tmpnam() can be called up to TMP_MAX times.
 */
char *tmpnam(char *name);

/**
 * The function ungetc() puts the character ch back in stream.
 */
int ungetc(int ch, FILE *stream);

///// Own:

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
