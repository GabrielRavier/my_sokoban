/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests my_fabs
*/

#include "../tests_header.h"
#include "random_floats.h"
#include "float_bit_equality.h"
#include "data/fabs.h"
#include "my/math.h"
#include "my/cpp-like/iterator.h"
#include <math.h>
#include <stddef.h>

static void do_test(long double x)
{
    double x_double = x;
    float x_float = x;
    long double result_us = my_fabsl(x);
    long double result_them = fabsl(x);
    double result_us_double = my_fabs(x_double);
    double result_them_double = fabs(x_double);
    float result_us_float = my_fabsf(x_float);
    float result_them_float = fabsf(x_float);

    cr_assert_eq(long_double_bit_eq(result_us, result_them), 1);
    cr_assert_eq(double_bit_eq(result_us_double, result_them_double), 1);
    cr_assert_eq(float_bit_eq(result_us_float, result_them_float), 1);
}

Test(my_fabs, random_floats)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(RANDOM_FLOATS); ++i) {
        do_test(RANDOM_FLOATS[i]);
        do_test(-RANDOM_FLOATS[i]);
        do_test(RANDOM_FLOATS[i] * 10);
        do_test(-RANDOM_FLOATS[i] * 10);
    }
    for (size_t i = 0; i < 100000; ++i) {
        union {
            long double val;
            unsigned char bytes[sizeof(long double)];
        } u;
        for (size_t i = 0; i < sizeof(u.bytes); ++i)
            u.bytes[i] = rand();
        do_test(u.val);
    }
}

Test(my_fabs, bionic)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(G_FABS_INTEL_DATA); ++i)
        do_test(G_FABS_INTEL_DATA[i].input);
    for (size_t i = 0; i < MY_ARRAY_SIZE(G_FABSF_INTEL_DATA); ++i)
        do_test(G_FABSF_INTEL_DATA[i].input);
}
