/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#pragma once

#include <sys/cdefs.h>
#include <stddef.h> /* for size_t */

__BEGIN_DECLS

/**
 * The memchr() function looks for the first occurrence of ch within count
 * characters in the array pointed to by buffer. The return value points to the
 * location of the first occurrence of ch, or NULL if ch isn't found. For
 * example:
 * @code
 * char names[] = "Alan Bob Chris X Dave";
 * if( memchr(names,'X',strlen(names)) == NULL )
 *   printf( "Didn't find an X\n" );
 * else
 *   printf( "Found an X\n" );
 * @endcode
 */
void *memchr(const void *buffer, int ch, size_t count);

/**
 * The function memcmp() compares the first count characters of buffer1 and
 * buffer2. The return values are as follows:
 *
 * Value            Explanation
 * less than 0      buffer1 is less than buffer2
 * equal to 0       buffer1 is equal to buffer2
 * greater than 0   buffer1 is greater than buffer2
 */
int memcmp(const void *buffer1, const void *buffer2, size_t count);

/**
 * The function memcpy() copies count characters from the array from to the
 * array to. The return value of memcpy() is to. The behavior of memcpy() is
 * undefined if to and from overlap.
 */
void *memcpy(void *to, const void *from, size_t count);

/**
 * The memmove() function is identical to memcpy(), except that it works even if
 * to and from overlap.
 */
void *memmove(void *to, const void *from, size_t count);

/**
 * The function memset() copies ch into the first count characters of buffer,
and returns buffer. memset() is useful for intializing a section of memory to
some value. For example, this command:
 * @code
 * memset( the_array, '\0', sizeof(the_array) );
 * @endcode
.*.is a very efficient way to set all values of the_array to zero.
 *
 * The table below compares two different methods for initializing an array of
characters: a for-loop versus memset(). As the size of the data being
initialized increases, memset() clearly gets the job done much more quickly:
 *
 * Input size   Initialized with a for-loop     Initialized with memset()
 * 1000         0.016                           0.017
 * 10000        0.055                           0.013
 * 100000 	    0.443                           0.029
 * 1000000 	    4.337                           0.291
 */
void *memset(void *buffer, int ch, size_t count);

/**
 * The strcat() function concatenates str2 onto the end of str1, and returns
 * str1. For example:
 * @code
 * printf( "Enter your name: " );
 * scanf( "%s", name );
 * title = strcat( name, " the Great" );
 * printf( "Hello, %s\n", title );
 * @endcode
 * Note that strcat() does not perform bounds checking, and thus risks
 * overrunning str1 or str2. For a similar (and safer) function that includes
 * bounds checking, see strncat().
 */
char *strcat(char *str1, const char *str2);

/**
 * The function strchr() returns a pointer to the first occurence of ch in str,
 * or NULL if ch is not found.
 */
char *strchr(const char *str, int ch);

/**
 * The function strcmp() compares str1 and str2, then returns:
 *
 * Return value     Explanation
 * less than 0      ''str1'' is less than ''str2''
 * equal to 0       ''str1'' is equal to ''str2''
 * greater than 0   ''str1'' is greater than ''str2''
 *
 * For example:
 * @code
 * printf( "Enter your name: " );
 * scanf( "%s", name );
 * if( strcmp( name, "Mary" ) == 0 ) {
 *   printf( "Hello, Dr. Mary!\n" );
 * }
 * @endcode
 * Note that if str1 or str2 are missing a null-termination character, then
 * strcmp() may not produce valid results. For a similar (and safer) function
 * that includes explicit bounds checking, see strncmp().
 */
int strcmp(const char *str1, const char *str2);

/**
 * The strcoll() function compares str1 and str2, much like strcmp(). However,
 * strcoll() performs the comparison using the locale specified by the (Standard
 * C Date & Time) setlocale() function.
 */
int strcoll(const char *str1, const char *str2);

/**
 * The strcpy() function copies characters in the string from to the string to,
 * including the null termination. The return value is to.
 *
 * Note that strcpy() does not perform bounds checking, and thus risks
 * overrunning from or to. For a similar (and safer) function that includes
 * bounds checking, see strncpy().
 */
char *strcpy(char *to, const char *from);

/**
 * The function strcspn() returns the index of the first character in str1 that
 * matches any of the characters in str2.
 */
size_t strcspn(const char *str1, const char *str2);

/**
 * The function strerror() returns an implementation defined string
 * corresponding to num.
 */
char *strerror(int num);

/**
 * The strlen() function returns the length of str (determined by the number of
 * characters before null termination).
 */
size_t strlen(const char *str);

/**
 * The function strncat() concatenates at most count characters of str2 onto
 * str1, adding a null termination. The resulting string is returned.
 */
char *strncat(char *str1, const char *str2, size_t count);

/**
 * The strncmp() function compares at most count characters of str1 and str2.
 * The return value is as follows:
 *
 * Return value     Explanation
 * less than 0      ''str1'' is less than ''str2''
 * equal to 0       ''str1'' is equal to ''str2''
 * greater than 0   ''str1'' is greater than str2''
 *
 * If there are less than count characters in either string, then the comparison
 * will stop after the first null termination is encountered.
 */
int strncmp(const char *str1, const char *str2, size_t count);

/**
 * The strncpy() function copies at most count characters of from to the string
 * to. If from has less than count characters, the remainder is padded with '\0'
 * characters. The return value is the resulting string.
 */
char *strncpy(char *to, const char *from, size_t count);

/**
 * The function strpbrk() returns a pointer to the first ocurrence in str1 of
 * any character in str2, or NULL if no such characters are present.
 */
char *strpbrk(const char *str1, const char *str2);

/**
 * The function strrchr() returns a pointer to the last occurrence of ch in str,
 * or NULL if no match is found.
 */
char *strrchr(const char *str, int ch);

/**
 * The strspn() function returns the index of the first character in str1 that
 * doesn't match any character in str2.
 */
size_t strspn(const char *str1, const char *str2);

/**
 * The function strstr() returns a pointer to the first occurrence of str2 in
 * str1, or NULL if no match is found. If the length of str2 is zero, then
 * strstr() will simply return str1.
 *
 * For example, the following code checks for the existence of one string within
 * another string:
 * @code
 * char* str1 = "this is a string of characters";
 * char* str2 = "a string";
 * char* result = strstr( str1, str2 );
 * if( result == NULL ) printf( "Could not find '%s' in '%s'\n", str2, str1 );
 * else printf( "Found a substring: '%s'\n", result );
 * @endcode
 *
 * When run, the above code displays this output:
 * @code
 * Found a substring: 'a string of characters'
 * @endcode
 */
char *strstr(const char *str1, const char *str2);

/**
 * The strtok() function returns a pointer to the next "token" in str1, where
 * str2 contains the delimiters that determine the token. strtok() returns NULL
 * if no token is found. In order to convert a string to tokens, the first call
 * to strtok() should have str1 point to the string to be tokenized. All calls
 * after this should have str1 be NULL.
 *
 * For example:
 * @code
 * char str[] = "now # is the time for all # good men to come to the # aid of
 * their country";
 * char delims[] = "#";
 * char *result = NULL;
 * result = strtok( str, delims );
 * while( result != NULL ) {
 *     printf( "result is \"%s\"\n", result );
 *     result = strtok( NULL, delims );
 * }
 * @endcode
 *
 * The above code will display the following output:
 * @code
 * result is "now "
 * result is " is the time for all "
 * result is " good men to come to the "
 * result is " aid of their country"
 * @endcode
 */
char *strtok(char *str1, const char *str2);

/**
 * The strxfrm() function manipulates the first num characters of str2 and
 * stores them in str1. The result is such that if a strcoll() is performed on
 * str1 and the old str2, you will get the same result as with a strcmp().
 */
size_t strxfrm(char *str1, const char *str2, size_t num);

__END_DECLS
