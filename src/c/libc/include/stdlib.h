#pragma once

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

/**
 * The abort() function causes abnormal program termination to occur.
 */
void abort();

/**
 * The abs() function returns the absolute value of num.
 *
 * @param num any integer
 * @return not negative
 */
int abs(int num);

/**
 * The function atexit() causes the function pointed to by func to be called
 * when the program terminates. You can make multiple calls to atexit() (at
 * least 32, depending on your compiler) and those functions will be called in
 * reverse order of their establishment.
 *
 * @param func fucntion to be called
 * @return The return value of atexit() is zero upon success, and non-zero on
 * failure.
 */
int atexit(void (*func)(void));

/**
 * The function atof() converts str into a double, then returns that value. str
 * must start with a valid number, but can be terminated with any non-numerical
 * character, other than "E" or "e".
 */
double atof(const char *str);

/**
 * The atoi() function converts str into an integer, and returns that integer.
 * str should start with whitespace or some sort of number, and atoi() will stop
 * reading from str as soon as a non-numerical character has been read.
 */
int atoi(const char *str);

/**
 * The function atol() converts str into a long, then returns that value. atol()
 * will read from str until it finds any character that should not be in a long.
 * The resulting truncated value is then converted and returned.
 */
long atol(const char *str);

/**
 * The bsearch() function searches buf[0] to buf[num-1] for an item that matches
 * key, using a binary search. The function compare should return negative if
 * its first argument is less than its second, zero if equal, and positive if
 * greater. The items in the array buf should be in ascending order. The return
 * value of bsearch() is a pointer to the matching item, or NULL if none is
 * found.
 */
void *bsearch(const void *key, const void *buf, size_t num, size_t size,
              int (*compare)(const void *, const void *));

/**
 * The calloc() function returns a pointer to space for an array of num objects,
 * each of size size. The newly allocated memory is initialized to zero.
 *
 * calloc() returns NULL if there is an error.
*/
void *calloc(size_t num, size_t size);

/**
 * The ceil() function returns the smallest integer no less than num.
 */
double ceil(double num);

/**
 * The function div() returns the quotient and remainder of the operation
 * numerator / denominator. The div_t structure is defined in stdlib.h, and has
 * at least:
 * @code
 * int quot;   // The quotient
 * int rem;    // The remainder
 * @endcode
 */
div_t div(int numerator, int denominator);

/**
 * The exit() function stops the program. exit_code is passed on to be the
 * return value of the program, where usually zero indicates success and
 * non-zero indicates an error.
 */
void exit(int exit_code);

/**
 * The free() function deallocates the space pointed to by ptr, freeing it up
 * for future use. ptr must have been used in a previous call to malloc(),
 * calloc(), or realloc(). An example:
 * @code
 * typedef struct data_type {
 *   int age;
 *   char name[20];
 * } data;
 *
 * data *willy;
 * willy = (data*) malloc( sizeof(*willy) );
 * ...
 * free( willy );
 * @endcode
 */
void free(void *ptr);

/**
 * The function getenv() returns environmental information associated with name,
 * and is very implementation dependent. NULL is returned if no information
 * about name is available.
 */
char *getenv(const char *name);

/**
 * The function labs() returns the absolute value of num.
 */
long labs(long num);

/**
 * The ldiv() function returns the quotient and remainder of the operation
 * numerator / denominator.
 */
ldiv_t ldiv(long numerator, long denominator);

/**
 * The function malloc() returns a pointer to a chunk of memory of size size, or
 * NULL if there is an error. The memory pointed to will be on the heap, not the
 * stack, so make sure to free it when you are done with it. An example:
 *
 * @code
 * typedef struct data_type {
 *   int age;
 *   char name[20];
 * } data;
 *
 * data *bob;
 * bob = (data*) malloc( sizeof(data) );
 * if( bob != NULL ) {
 *   bob->age = 22;
 *   strcpy( bob->name, "Robert" );
 *   printf( "%s is %d years old\n", bob->name, bob->age );
 * }
 * free( bob );
 * @endcode
 */
void *malloc(size_t size);

/**
 * The qsort() function sorts buf (which contains num items, each of size size)
 * using Quicksort. The compare function is used to compare the items in buf.
 * compare should return negative if the first argument is less than the second,
 * zero if they are equal, and positive if the first argument is greater than
 * the second. qsort() sorts buf in ascending order.
 *
 * For example, the following bit of code uses qsort() to sort an array of
 * integers:
 * @code
 * int compare_ints( const void* a, const void* b ) {
 *   int* arg1 = (int*) a;
 *   int* arg2 = (int*) b;
 *   if( *arg1 < *arg2 ) return -1;
 *   else if( *arg1 == *arg2 ) return 0;
 *   else return 1;
 * }
 *
 * int array[] = { -2, 99, 0, -743, 2, 3, 4 };
 * int array_size = 7;
 *
 * ...
 *
 * printf( "Before sorting: " );
 * for( int i = 0; i < array_size; i++ ) {
 *   printf( "%d ", array[i] );
 * }
 * printf( "\n" );
 *
 * qsort( array, array_size, sizeof(int), compare_ints );
 *
 * printf( "After sorting: " );
 * for( int i = 0; i < array_size; i++ ) {
 *   printf( "%d ", array[i] );
 * }
 * printf( "\n" );
 * @endcode
 * When run, this code displays the following output:
 *  Before sorting: -2 99 0 -743 2 3 4
 * After sorting: -743 -2 0 2 3 4 99
 */
void qsort(void *buf, size_t num, size_t size,
           int (*compare)(const void *, const void *));

/**
 * The function rand() returns a pseudorandom integer between zero and RAND_MAX.
 * An example:
 * @code
 * srand( time(NULL) );
 * for( i = 0; i < 10; i++ )
 *   printf( "Random number #%d: %d\n", i, rand() );
 * @endcode
 */
int rand();

/**
 * The realloc() function changes the size of the object pointed to by ptr to
 * the given size. size can be any size, larger or smaller than the original.
 * The return value is a pointer to the new space, or NULL if there is an error.
 */
void *realloc(void *ptr, size_t size);

/**
 * The function srand() is used to seed the random sequence generated by rand().
 * For any given seed, rand() will generate a specific "random" sequence over
 * and over again.
 * @code
 * srand( time(NULL) );
 * for( i = 0; i < 10; i++ )
 *   printf( "Random number #%d: %d\n", i, rand() );
 * @endcode
 */
void srand(unsigned seed);

/**
 * The function strtod() returns whatever it encounters first in start as a
 * double. end is set to point at whatever is left in start after that double.
 * If overflow occurs, strtod() returns either HUGE_VAL or -HUGE_VAL.
 */
double strtod(const char *start, char **end);

/**
 * The strtol() function returns whatever it encounters first in start as a
 * long, doing the conversion to base if necessary. end is set to point to
 * whatever is left in start after the long. If the result can not be
 * represented by a long, then strtol() returns either LONG_MAX or LONG_MIN.
 * Zero is returned upon error.
 */
long strtol(const char *start, char **end, int base);

/**
 * The function strtoul() behaves exactly like strtol(), except that it returns
 * an unsigned long rather than a mere long.
 */
unsigned long strtoul(const char *start, char **end, int base);

/**
 * The system() function runs the given command by passing it to the default
 * command interpreter.
 *
 * The return value is usually zero if the command executed without errors. If
 * command is NULL, system() will test to see if there is a command interpreter
 * available. Non-zero will be returned if there is a command interpreter
 * available, zero if not.
*/
int system(const char *command);

__END_DECLS
