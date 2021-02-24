/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests signbit
*/

#include "../tests_header.h"
#include "random_floats.h"
#include "my/math.h"
#include "my/cpp-like/iterator.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

static void do_one_test(long double x)
{
    double x_double = (double)x;
    float x_float = (float)x;
    cr_assert_eq((bool)my_signbit(x), (bool)signbit(x));
    cr_assert_eq((bool)my_signbit(x_double), (bool)signbit(x_double));
    cr_assert_eq((bool)my_signbit(x_float), (bool)signbit(x_float));
}

Test(my_signbit, random_floats)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(RANDOM_FLOATS); ++i) {
        do_one_test(RANDOM_FLOATS[i]);
        do_one_test(-RANDOM_FLOATS[i]);
    }
    for (size_t i = 0; i < 100000; ++i) {
        union {
            long double val;
            unsigned char bytes[sizeof(long double)];
        } u;
        for (size_t j = 0; j < sizeof(u.bytes); ++j)
            u.bytes[j] = rand();
        do_one_test(u.val);
    }
}
