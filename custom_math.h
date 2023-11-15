#include <stdio.h>

// Mathematical constants
#define CUSTOM_E 2.7182818284590452353602874713527L
#define CUSTOM_PI 3.14159265358979323846
#define CUSTOM_ATAN_ONE_PLUS 0.78539816339744816797718840
#define CUSTOM_ATAN_ONE_MINUS -0.7853981633974483
#define CUSTOM_LDBL_EPSILON 1.0E-18L
#define CUSTOM_NAN (0.0 / 0.0)
#define CUSTOM_INF_POS (+1.0 / 0.0)
#define CUSTOM_INF_NEG (-1.0 / 0.0)
#define CUSTOM_TRG_PRC 1e-6L  // accuracy of trigonometric functions
#define CUSTOM_PRC 1e-16      // test accuracy

// Check NaN value
#define CUSTOM_IS_NAN(X) (X != X)

/**
 * @brief Returns the absolute value of an integer number.
 *
 * The custom_abs function computes the absolute value of an integer number x.
 *
 * @param x The number to compute the absolute value of.
 * @return The absolute value of x.
 */
int custom_abs(int x);
/**
 * @brief Returns the absolute value of a double number.
 *
 * The custom_fabs function computes the absolute value of a double number x.
 *
 * @param x The number to compute the absolute value of.
 * @return The absolute value of x.
 */
long double custom_fabs(double x);
/**
 * @brief Returns the absolute value of a long double number.
 *
 * The custom_fabsl function computes the absolute value of a long double number x.
 *
 * @param x The number to compute the absolute value of.
 * @return The absolute value of x.
 */
long double custom_fabsl(long double x);
/**
 * @brief Calculates the factorial of a non-negative integer x.
 *
 * The custom_factorial function computes the product of all positive integers up
 * to x. If x is less than 0, the function returns NaN.
 *
 * @param x The value to calculate the factorial of.
 * @return The factorial of x, or NaN if x is negative.
 */
long double custom_factorial(int x);
/**
 * @brief Calculates the largest integer value less than or equal to x.
 *
 * The custom_floor function rounds x downward, returning the largest integral
 * value that is not greater than x.
 *
 * @param x The value to round down.
 * @return The largest integral value not greater than x.
 */
long double custom_floor(double x);
/**
 * @brief Calculates the smallest integer value greater than or equal to x.
 *
 * The custom_ceil function rounds x upward, returning the smallest integral value
 * that is not less than x.
 *
 * @param x The value to round up.
 * @return The smallest integral value not less than x.
 */
long double custom_ceil(double x);
/**
 * @brief Computes the floating-point remainder of the division of two numbers.
 *
 * The custom_fmod function computes the remainder of dividing x by y. The return
 * value is x - n * y, where n is the quotient of x divided by y, rounded
 * towards zero to an integer.
 *
 * @param x The numerator of the division.
 * @param y The denominator of the division.
 * @return The remainder of the division.
 */
long double custom_fmod(double x, double y);
/**
 * @brief Raises a base to an exponent power.
 *
 * The function computes the power of a given base raised to a given exponent.
 * Special cases for base or exponent being 0, 1, or infinity are handled
 * explicitly. If the exponent is an integer, the power is calculated using
 * exponentiation by squaring. For non-integer exponents, the function falls
 * back to using the exp and log functions.
 *
 * @param base The base.
 * @param exp The exponent.
 * @return The result of raising `base` to the power of `exp`.
 */
long double custom_pow(double base, double exp);
/**
 * @brief Calculates the arccosine of a number.
 *
 * This function computes the arccosine of `x` by reducing the problem to the
 * calculation of the arcsine. The arccosine is calculated as π/2 minus the
 * arcsine of `x`.
 *
 * @param x The number to calculate the arccosine for. Must be in the range [-1,
 * 1].
 * @return The arccosine of `x`.
 */
long double custom_acos(double x);
/**
 * @brief Calculates the arcsine of a number.
 *
 * The function computes the arcsine of `x` using a Taylor series expansion.
 * It only accepts input values in the range [-1, 1]. For values -1 and 1,
 * it returns -π/2 and π/2, respectively.
 *
 * @param x The number to calculate the arcsine for. Must be in the range [-1,
 * 1].
 * @return The arcsine of `x`.
 */
long double custom_asin(double x);
/**
 * @brief Calculates the arctangent of a number.
 *
 * The function returns the arctangent of `x` using an iterative algorithm.
 * Special cases are handled for inputs of positive and negative infinity,
 * returning π/2 and -π/2, respectively. For `x` equal to 1 or -1, predefined
 * constants are returned.
 *
 * @param x The number to calculate the arctangent for.
 * @return The arctangent of `x`.
 */
long double custom_atan(double x);
/**
 * @brief Calculates the cosine of an angle in radians.
 *
 * This function uses the Taylor series expansion to approximate the cosine of
 * `x`. The angle `x` is normalized to the range [0, 2π] using the modulo
 * operation before the calculation begins.
 *
 * @param x The angle in radians.
 * @return The cosine of `x`.
 */
long double custom_cos(double x);
/**
 * @brief Calculates the sine of an angle in radians.
 *
 * This function uses the Taylor series expansion to approximate the sine of
 * `x`. The angle `x` is reduced to the range of [-π, π] using the modulo
 * operation before the calculation begins.
 *
 * @param x The angle in radians.
 * @return The sine of `x`.
 */
long double custom_sin(double x);
/**
 * @brief Calculates the exponential function of a number.
 *
 * This function computes the value of e (Euler's number) raised to the power of
 * `x`. It uses a series expansion to calculate the exponential, which is a sum
 * of terms x^i / i!, from i = 0 to infinity.
 *
 * @param x The exponent to raise e to. Can be any real number.
 * @return The value of e^x. If `x` is positive infinity, returns positive
 * infinity. If `x` is 0, returns 1. If `x` is negative infinity, returns 0. If
 * `x` is NaN, returns NaN.
 *
 * @note For positive infinity, the result is defined as positive infinity. For
 * zero, it returns 1, which is the mathematical limit of e^x as x approaches 0.
 *       For negative infinity, the result is defined as 0.
 */
long double custom_exp(double x);
/**
 * @brief Calculates the natural logarithm of a number.
 *
 * This function calculates the natural logarithm of `x` using Newton's method,
 * which is an iterative numerical process. The logarithm is the inverse
 * operation of exponentiation, and this function specifically computes the
 * base-e logarithm, commonly known as ln(x).
 *
 * @param x The number to calculate the natural logarithm for. The value must be
 * positive.
 * @return The natural logarithm of `x`. If `x` is negative, the function
 * returns NaN. For `x` equal to 0, it returns negative infinity, and for `x`
 * equal to 1, it returns 0.
 *
 * @note The function uses a predefined number of maximum iterations,
 * `max_iterations`, and an epsilon value, `custom_LDBL_EPSILON`, to control the
 * precision of the computation.
 */
long double custom_log(double x);
/**
 * @brief Calculates the square root of a number.
 *
 * This function uses Newton's method to calculate the square root of `x`.
 * Newton's method is an iterative numerical method that converges to the square
 * root of `x`.
 *
 * @param x The number for which the square root is calculated. The value must
 * be non-negative.
 * @return The square root of `x`. If `x` is negative, returns NaN.
 *
 * @note If a negative number is passed, the function will return NaN, which
 * conforms to the IEEE standard for floating-point numbers.
 * @warning If the argument `x` is NaN or infinity, the function will simply
 * return that argument back.
 */
long double custom_sqrt(double x);
/**
 * @brief Calculates the tangent of an angle.
 *
 * This function computes the tangent of `x`, which is the ratio of the sine of
 * `x` to the cosine of `x`. The angle `x` is given in radians. The function
 * uses the custom_sin and custom_cos functions to determine the sine and cosine of
 * `x` and then calculates their ratio to find the tangent.
 *
 * @param x The angle in radians for which the tangent is calculated. The value
 * is reduced to an equivalent angle between -π and π using the custom_fmod
 * function.
 * @return The tangent of `x`. If `x` is an odd multiple of π/2, where the
 * cosine of `x` is zero, the function returns NaN to represent the mathematical
 * infinity.
 *
 * @note The function expects the angle `x` to be in radians, not degrees.
 * @warning If the argument `x` is NaN or if cosine of `x` is zero, the function
 * will return NaN. This is in accordance with the mathematical definition of
 * tangent, which is undefined at odd multiples of π/2.
 */
long double custom_tan(double x);
int custom_trg_norm(long double *phi);