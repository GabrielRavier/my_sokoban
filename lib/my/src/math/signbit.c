/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines signbit
*/

#include "my/math.h"
#include "my/internal/math.h"
#include <stdint.h>

int my_signbit_double(double x)
{
    return (((union my_ieee754_double_parts){.as_double = x}).sign);
}

int my_signbit_float(float x)
{
    return (((union my_ieee754_float_parts){.as_float = x}).sign);
}

int my_signbit_long_double(long double x)
{
    return (((union my_ieee754_long_double_parts){.as_long_double = x}).sign);
}
