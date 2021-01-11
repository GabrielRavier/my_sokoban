/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fabs
*/

#include "my/math.h"
#include "my/internal/math.h"
#include <stdint.h>

double my_fabs(double x)
{
    union my_ieee754_double_parts u = {.as_double = x};

    u.sign = false;
    return u.as_double;
}

float my_fabsf(float x)
{
    union my_ieee754_float_parts u = {.as_float = x};

    u.sign = false;
    return u.as_float;
}

long double my_fabsl(long double x)
{
    union my_ieee754_long_double_parts u = {.as_long_double = x};

    u.sign = false;
    return u.as_long_double;
}
