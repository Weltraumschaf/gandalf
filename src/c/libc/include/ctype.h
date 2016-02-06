#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * The function isalnum() returns non-zero if its argument is a numeric digit or
 * a letter of the alphabet. Otherwise, zero is returned.
 */
int isalnum(int ch);

/**
 * The function isalpha() returns non-zero if its argument is a letter of the
 * alphabet. Otherwise, zero is returned.
 */
int isalpha(int ch);

/**
 * The iscntrl() function returns non-zero if its argument is a control
 * character (between 0 and 0x1F or equal to 0x7F). Otherwise, zero is returned.
 */
int iscntrl(int ch);

/**
 * The function isdigit() returns non-zero if its argument is a digit between 0
 * and 9. Otherwise, zero is returned.
 */
int isdigit(int ch);

/**
 * The function isgraph() returns non-zero if its argument is any printable
 * character other than a space (if you can see the character, then isgraph()
 * will return a non-zero value). Otherwise, zero is returned.
 */
int isgraph(int ch);

/**
 * The islower() function returns non-zero if its argument is a lowercase
 * letter. Otherwise, zero is returned.
 */
int islower(int ch);

/**
 * The function isprint() returns non-zero if its argument is a printable
 * character (including a space). Otherwise, zero is returned.
*/
int isprint(int ch);

/**
 * The ispunct() function returns non-zero if its argument is a printing
 * character but neither alphanumeric nor a space. Otherwise, zero is returned.
 */
int ispunct(int ch);

/**
 * The isspace() function returns non-zero if its argument is some sort of space
 * (i.e. single space, tab, vertical tab, form feed, carriage return, or
 * newline). Otherwise, zero is returned.
 */
int isspace(int ch);

/**
 * The isupper() function returns non-zero if its argument is an uppercase
 * letter. Otherwise, zero is returned.
 */
int isupper(int ch);

/**
 * The function isxdigit() returns non-zero if its argument is a hexidecimal
 * digit (i.e. A-F, a-f, or 0-9). Otherwise, zero is returned.
 */
int isxdigit(int ch);

/**
 * The function tolower() returns the lowercase version of the character ch.
 */
int tolower(int ch);

/**
 * The toupper() function returns the uppercase version of the character ch.
 */
int toupper(int ch);

__END_DECLS
