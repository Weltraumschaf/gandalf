/*
 * From klibc.
 */

/**
 * The stpcpy() and functions copy the string src to dst (including the terminating `\0' character).
 *
 * @param dst target to copy the string
 * @param src thecooied string
 * @return a pointer to the terminating `\0' character of dst.  If stpncpy() does not terminate dst with a NUL
 *         character, it instead returns a pointer to dst[n] (which does not necessarily refer to a valid memory
 *         location.)
 */
char *strcpy(char *dst, const char *src) {
    char *q = dst;
    const char *p = src;
    char ch;

    do {
        *q++ = ch = *p++;
    } while (ch);

    return dst;
}