#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * The acos() function returns the arc cosine of arg, which will be in the range
 * [0, pi].
 *
 * @param arg Should be between -1 and 1,
 * @return If arg is outside this range, acos() returns NAN and raises a
 * floating-point exception.
 */
double acos(double arg);

/**
 * The asin() function returns the arc sine of arg, which will be in the range
 * [-pi/2, +pi/2].
 *
 * @param arg should be between -1 and 1.
 * @return If arg is outside this range, asin() returns NAN and raises a
 * floating-point exception.
 */
double asin(double arg);

/**
 *The function atan() returns the arc tangent of arg, which will be in the range
 *[-pi/2, +pi/2].
 */
double atan(double arg);

/**
 * The atan2() function computes the arc tangent of y/x, using the signs of the
 * arguments to compute the quadrant of the return value.
 *
 * Note the order of the arguments passed to this function.
 */
double atan2(double y, double x);

/**
 * The cos() function returns the cosine of arg, where arg is expressed in
 * radians. The return value of cos() is in the range [-1,1]. If arg is
 * infinite, cos() will return NAN and raise a floating-point exception.
 */
double cos(double arg);

/**
 * The function cosh() returns the hyperbolic cosine of arg.
 */
double cosh(double arg);

/**
 * The exp() function returns e (2.7182818) raised to the argth power.
 */
double exp(double arg);

/**
 * The function fabs() returns the absolute value of arg.
 */
double fabs(double arg);

/**
 * The function floor() returns the largest integer not greater than arg. For
 * example,
 */
double floor(double arg);

/**
 * The fmod() function returns the remainder of x/y.
 */
double fmod(double x, double y);

/**
 * The function frexp() is used to decompose num into two parts: a mantissa
 * between 0.5 and 1 (returned by the function) and an exponent returned as exp.
 * Scientific notation works like this:
 * @code
 * num = mantissa * (2 ^ exp)
 * @endcode
 */
double frexp(double num, int *exp);

/**
 * The ldexp() function returns num * (2 ^ exp). And get this: if an overflow
 * occurs, HUGE_VAL is returned.
 */
double ldexp(double num, int exp);

/**
 * The function log() returns the natural (base e) logarithm of num. There's a
 * domain error if num is negative, a range error if num is zero.
 *
 * In order to calculate the logarithm of x to an arbitrary base b, you can use:
 *
 * @code
 * double answer = log(x) / log(b);
 * @endcode
 */
double log(double num);

/**
 * The log10() function returns the base 10 (or common) logarithm for num.
 * There's a domain error if num is negative, a range error if num is zero.
 */
double log10(double num);

/**
 * The function modf() splits num into its integer and fraction parts. It
 * returns the fractional part and loads the integer part into i.
 */
double modf(double num, double *i);

/**
 * The pow() function returns base raised to the expth power. There's a domain
 * error if base is zero and exp is less than or equal to zero. There's also a
 * domain error if base is negative and exp is not an integer. There's a range
 * error if an overflow occurs.
 */
double pow(double base, double exp);

/**
 * The function round() rounds x to the nearest integer, but round halfway cases
 * away from zero.
 * @code
 * double d = round(x);
 * int i = (int) round(x);
 * @endcode
 */
double round(double x);

/**
 * The function sin() returns the sine of arg, where arg is given in radians.
 * The return value of sin() will be in the range [-1,1]. If arg is infinite,
 * sin() will return NAN and raise a floating-point exception.
 */
double sin(double arg);

/**
 * The function sinh() returns the hyperbolic sine of arg.
 */
double sinh(double arg);

/**
 * The sqrt() function returns the square root of num. If num is negative, a
 * domain error occurs.
 */
double sqrt(double num);

/**
 * The tan() function returns the tangent of arg, where arg is given in radians.
 * If arg is infinite, tan() will return NAN and raise a floating-point
 * exception.
 */
double tan(double arg);

/**
 * The function tanh() returns the hyperbolic tangent of arg.
 */
double tanh(double arg);

__END_DECLS
