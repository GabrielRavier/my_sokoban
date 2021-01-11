/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines fpclassify. We assume IEEE-754, but ¯\_(ツ)_/¯
*/

#include "my/math.h"
#include "my/internal/math.h"
#include <math.h>
#include <stdint.h>

int my_fpclassify_double(double x)
{
    const union my_ieee754_double_parts u = {.as_double = x};

    if (u.exponent == 0)
        return ((u.mantissa || u.exponent) ? FP_SUBNORMAL : FP_ZERO);
    if (u.exponent == 0x7FF)
        return (u.mantissa ? FP_NAN : FP_INFINITE);
    return (FP_NORMAL);
}

int my_fpclassify_float(float x)
{
    const union my_ieee754_float_parts u = {.as_float = x};
    int32_t int_x = (int32_t)u.as_u32;

    int_x &= 0x7FFFFFFF;
    return ((int_x == 0) ? FP_ZERO :
        (int_x < 0x800000) ? FP_SUBNORMAL :
        (int_x >= 0x7F800000) ?
        ((int_x > 0x7F800000) ? FP_NAN : FP_INFINITE) : FP_NORMAL);
}

// Assumes x86 80-bit long double format
int my_fpclassify_long_double(long double x)
{
    const union my_ieee754_long_double_parts u = {.as_long_double = x};

    if (((uint32_t)u.exponent | u.mantissa) == 0)
        return (FP_ZERO);
    if (u.exponent == 0 && (u.mantissa & 0x80000000) == 0)
        return (FP_SUBNORMAL);
    if (u.exponent == 0x7FFF)
        return ((u.mantissa & 0x7FFFFFFFFFFFFFFF) != 0 ? FP_NAN : FP_INFINITE);
    return (FP_NORMAL);
}
