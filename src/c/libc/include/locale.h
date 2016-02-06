#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

#define LC_CTYPE 0
#define LC_NUMERIC 1
#define LC_TIME 2
#define LC_COLLATE 3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_ALL 6
#define LC_PAPER 7
#define LC_NAME 8
#define LC_ADDRESS 9
#define LC_TELEPHONE 10
#define LC_MEASUREMENT 11
#define LC_IDENTIFICATION 12

/**
 * The setlocale() function is used to set and retrieve the current locale. If
 * locale is NULL, the current locale is returned. Otherwise, locale is used to
 * set the locale for the given category.
 *
 * category can have the following values:
 * Value        Description
 * LC_ALL       All of the locale
 * LC_TIME      Date and time formatting
 * LC_NUMERIC   Number formatting
 * LC_COLLATE   String collation and regular expression matching
 * LC_CTYPE     Regular expression matching, conversion, case-sensitive
 * comparison, wide character functions, and character classification.
 * LC_MONETARY  For monetary formatting
 * LC_MESSAGES  For natural language messages
 */
char *setlocale(int category, const char *locale);

__END_DECLS
