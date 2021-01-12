/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Compares floating-point values to determine whether they have the exact same bit values
*/

#pragma once

#include "my/internal/math.h"

bool float_bit_eq(float a, float b)
{
    return ((union my_ieee754_float_parts){.as_float = a}).as_u32 == ((union my_ieee754_float_parts){.as_float = b}).as_u32;
}

bool double_bit_eq(double a, double b)
{
    return ((union my_ieee754_double_parts){.as_double = a}).as_u64 == ((union my_ieee754_double_parts){.as_double = b}).as_u64;
}

bool long_double_bit_eq(long double a, long double b)
{
    union my_ieee754_long_double_parts a_u = {.as_long_double = a};
    union my_ieee754_long_double_parts b_u = {.as_long_double = b};
    return a_u.mantissa == b_u.mantissa && a_u.exponent == b_u.exponent && a_u.sign == b_u.sign;
}
