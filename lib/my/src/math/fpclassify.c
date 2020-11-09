/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_fpclassify. We assume IEEE-754, but ¯\_(ツ)_/¯
*/

#include "my/math.h"
#include <math.h>
#include <stdint.h>

int my_fpclassify_double(double x)
{
    const union {
        double as_double;
        uint64_t as_int;
    } u = {.as_double = x};
    int32_t exponent = u.as_int >> 52 & 0x7FF;

    if (exponent == 0)
        return u.as_int << 1 ? FP_SUBNORMAL : FP_ZERO;
    if (exponent == 0x7FF)
        return u.as_int << 12 ? FP_NAN : FP_INFINITE;
    return FP_NORMAL;
}

int my_fpclassify_float(float x)
{
    const union {
        float as_float;
        uint32_t as_int;
    } u = {.as_float = x};
    int32_t exponent = u.as_int >> 23 & 0xFF;

    if (exponent == 0)
        return u.as_int << 1 ? FP_SUBNORMAL : FP_ZERO;
    if (exponent == 0x7FF)
        return u.as_int << 9 ? FP_NAN : FP_INFINITE;
    return FP_NORMAL;
}

// Assumes x86 80-bit long double format
int my_fpclassify_long_double(long double x)
{
    union {
        long double as_long_double;
        struct {
            uint32_t lsw;
            uint32_t msw;
            int32_t sign_exponent:16;
        };
    } u = {.as_long_double = x};

    u.sign_exponent &= 0x7FFF;
    if ((u.sign_exponent | u.lsw | u.msw) == 0)
        return FP_ZERO;
    else if (u.sign_exponent == 0 && (u.lsw & 0x80000000) == 0)
        return FP_SUBNORMAL;
    if (u.sign_exponent == 0x7FFF)
        return ((u.msw & 0x7FFFFFFF) | u.lsw) != 0 ? FP_NAN : FP_INFINITE;
    return FP_NORMAL;
}
