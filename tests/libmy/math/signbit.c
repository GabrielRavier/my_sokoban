/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests signbit
*/

#include "../tests_header.h"
#include "my/math.h"
#include <math.h>
#include <float.h>
#include <stdbool.h>

static void do_test(long double x)
{
    double x_double = x;
    float x_float = x;
    cr_assert_eq((bool)my_signbit(x), (bool)signbit(x));
    cr_assert_eq((bool)my_signbit(x_double), (bool)signbit(x_double));
    cr_assert_eq((bool)my_signbit(x_float), (bool)signbit(x_float));
}

Test(my_signbit, gnulib)
{
    do_test(3.141l);
    do_test(3.141e30l);
    do_test(3.141e-30l);
    do_test(-2.718l);
    do_test(-2.718e30l);
    do_test(-2.718e-30l);
    do_test(0.0l);
    do_test(-0.0l);
    do_test(1.l);
    do_test(-1.l);
    do_test(INFINITY);
    do_test(-INFINITY);
    do_test(NAN);
    do_test(SNANL);
}

Test(my_signbit, limits)
{
    do_test(FLT_MIN);
    do_test(DBL_MIN);
    do_test(LDBL_MIN);
    do_test(FLT_TRUE_MIN);
    do_test(DBL_TRUE_MIN);
    do_test(LDBL_TRUE_MIN);
    do_test(FLT_MAX);
    do_test(DBL_MAX);
    do_test(LDBL_MAX);
    do_test(FLT_EPSILON);
    do_test(DBL_EPSILON);
    do_test(LDBL_EPSILON);
    do_test(-FLT_MIN);
    do_test(-DBL_MIN);
    do_test(-LDBL_MIN);
    do_test(-FLT_TRUE_MIN);
    do_test(-DBL_TRUE_MIN);
    do_test(-LDBL_TRUE_MIN);
    do_test(-FLT_MAX);
    do_test(-DBL_MAX);
    do_test(-LDBL_MAX);
    do_test(-FLT_EPSILON);
    do_test(-DBL_EPSILON);
    do_test(-LDBL_EPSILON);
}

