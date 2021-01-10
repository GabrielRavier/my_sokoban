/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares math-related functions from libmy
*/

#pragma once

#include "features.h"
#include <math.h>
#include <stdbool.h>

// Absolute value of
float my_fabsf(float x) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;

int my_fpclassify_double(double x) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_fpclassify_float(float x) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_fpclassify_long_double(long double x) MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_CONST;

// Get the classification of x
#define my_fpclassify(x) _Generic((x),          \
        default: my_fpclassify_double,          \
        long double: my_fpclassify_long_double, \
        float: my_fpclassify_float              \
        )(x)

// Determine whether x is "Not a Number"
#define my_isnan(x) (my_fpclassify(x) == FP_NAN)

// Determine whether x is either positive or negative infinity
#define my_isinf(x) (my_fpclassify(x) == FP_INFINITE)
