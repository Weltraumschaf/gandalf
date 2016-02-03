#pragma once

__BEGIN_DECLS

/**
 * The function asctime() converts the time in the struct 'ptr' to a character
 * string of the following format:
 * day month date hours:minutes:seconds year
 *
 * @param ptr givne time
 * @return time as string
 */
char *asctime(const struct tm *ptr);

/**
 * The clock() function returns the processor time since the program started, or
 * -1 if that information is unavailable. To convert the return value to
 * seconds, divide it by CLOCKS_PER_SEC. (Note: if your compiler is POSIX
 * compliant, then CLOCKS_PER_SEC is always defined as 1000000.)
 */
clock_t clock(void);

/**
 * The ctime() function converts the calendar time time to local time of the
 * format: day month date hours:minutes:seconds year
 *
 * using ctime() is equivalent to asctime( localtime( tp ) );
 */
char *ctime(const time_t *time);

/**
 * The function difftime() returns time2 - time1, in seconds.
 */
double difftime(time_t time2, time_t time1);

/**
 * The gmtime() function returns the given time in Coordinated Universal Time
 * (usually Greenwich mean time), unless it's not supported by the system, in
 * which case NULL is returned. Watch out for static return.
 */
struct tm *gmtime(const time_t *time);

/**
 * The function localtime() converts calendar time time into local time. Watch
 * out for the static return.
 */
struct tm *localtime(const time_t *time);

/**
 * The mktime() function converts the local time in time to calendar time, and
 * returns it. If there is an error, -1 is returned.
 */
time_t mktime(struct tm *time);

/**
 * The function strftime() formats date and time information from time to a
 * format specified by fmt, then stores the result in str (up to maxsize
 * characters). Certain codes may be used in fmt to specify different types of
 * time:
 *
 * Code     Meaning
 * %a       abbreviated weekday name (e.g. Fri)
 * %A       full weekday name (e.g. Friday)
 * %b       abbreviated month name (e.g. Oct)
 * %B       full month name (e.g. October)
 * %c       the standard date and time string
 * %d       day of the month, as a number (1-31)
 * %H       hour, 24 hour format (0-23)
 * %I       hour, 12 hour format (1-12)
 * %j       day of the year, as a number (1-366)
 * %m       month as a number (1-12). Note: some versions of Microsoft Visual
 *          C++ may use values that range from 0-11.
 * %M       minute as a number (0-59)
 * %p       locale's equivalent of AM or PM
 * %S       second as a number (0-59)
 * %U       week of the year, (0-53), where week 1 has the first Sunday
 * %w       weekday as a decimal (0-6), where Sunday is 0
 * %W       week of the year, (0-53), where week 1 has the first Monday
 * %x       standard date string
 * %X       standard time string
 * %y       year in decimal, without the century (0-99)
 * %Y       year in decimal, with the century
 * %Z       time zone name
 * %%       a percent sign
 *
 * The strftime() function returns the number of characters put into str, or
 * zero if an error occurs.
 */
size_t strftime(char *str, size_t maxsize, const char *fmt, struct tm *time);

/**
 * The function time() returns the current time, or -1 if there is an error. If
 * the argument 'time' is given, then the current time is stored in 'time'.
 */
time_t time(time_t *time);

__END_DECLS
