/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares math-related functions from libmy
*/

#pragma once

#include "my/config.h"
#include <math.h>
#include <stdbool.h>

float my_fabsf(float x) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_fpclassify_double(double x);
int my_fpclassify_float(float x);
int my_fpclassify_long_double(long double x);
#define my_fpclassify(x) _Generic((x),             \
        default: my_fpclassify_double,          \
        long double: my_fpclassify_long_double, \
        float: my_fpclassify_float              \
        )(x)
#define my_isnan(x) (my_fpclassify(x) == FP_NAN)
#define my_isinf(x) (my_fpclassify(x) == FP_INFINITE)
