/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests my_fabs
*/

#include "../tests_header.h"
#include "random_floats.h"
#include "my/math.h"
#include "my/string.h"
#include "my/cpp-like/iterator.h"
#include <math.h>
#include <float.h>
#include <stdint.h>

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

    cr_assert_eq(my_memcmp(&result_us, &result_them, sizeof(long double)), 0);
    cr_assert_eq(my_memcmp(&result_us_double, &result_them_double, sizeof(double)), 0);
    cr_assert_eq(my_memcmp(&result_us_float, &result_them_float, sizeof(float)), 0);
}

Test(my_fabs, gnulib)
{
    do_test(0.6l);
    do_test(-0.6l);
    do_test(NAN);
    do_test(.0l);
    do_test(-.0l);
    do_test(INFINITY);
    do_test(-INFINITY);
    for (size_t i = 0; i < MY_ARRAY_SIZE(random_floats); ++i) {
        long double x = random_floats[i] * 10;
        do_test(x);
        do_test(-x);
    }
}

static const long double BIONIC_INTEL_DATA[] = {
    0x1.p-10,
    0x1.p-1074,
    0.0,
    0x1.p-1074,
    0x1.fffffffffffff0p999,
    0x1.p1000,
    0x1.00000000000010p1000,
    0x1.fffffffffffff0p199,
    0x1.fffffffffffffp199,
    0x1.p200,
    0x1.0p200,
    0x1.00000000000010p200,
    0x1.0000000000001p200,
    0x1.fffffffffffff0p99,
    0x1.fffffffffffffp99,
    0x1.p100,
    0x1.0p100,
    0x1.00000000000010p100,
    0x1.0000000000001p100,
    0x1.fffffffffffff0p19,
    0x1.fffffffffffffp19,
    0x1.p20,
    0x1.0p20,
    0x1.00000000000010p20,
    0x1.0000000000001p20,
    0x1.fffffffffffff0p14,
    0x1.fffffffffffffp14,
    0x1.p15,
    0x1.0p15,
    0x1.00000000000010p15,
    0x1.0000000000001p15,
    0x1.fffffffffffff0p9,
    0x1.fffffffffffffp9,
    0x1.p10,
    0x1.0p10,
    0x1.00000000000010p10,
    0x1.0000000000001p10,
    0x1.fffffffffffff0p8,
    0x1.fffffffffffffp8,
    0x1.p9,
    0x1.0p9,
    0x1.00000000000010p9,
    0x1.0000000000001p9,
    0x1.fffffffffffff0p6,
    0x1.fffffffffffffp6,
    0x1.p7,
    0x1.0p7,
    0x1.00000000000010p7,
    0x1.0000000000001p7,
    0x1.fffffffffffff0p4,
    0x1.fffffffffffffp4,
    0x1.p5,
    0x1.0p5,
    0x1.00000000000010p5,
    0x1.0000000000001p5,
    0x1.fffffffffffff0p3,
    0x1.fffffffffffffp3,
    0x1.p4,
    0x1.0p4,
    0x1.00000000000010p4,
    0x1.0000000000001p4,
    0x1.fffffffffffff0p2,
    0x1.fffffffffffffp2,
    0x1.p3,
    0x1.0p3,
    0x1.00000000000010p3,
    0x1.0000000000001p3,
    0x1.fffffffffffff0p1,
    0x1.fffffffffffffp1,
    0x1.p2,
    0x1.0p2,
    0x1.00000000000010p2,
    0x1.0000000000001p2,
    0x1.fffffffffffff0p0,
    0x1.fffffffffffffp0,
    0x1.p1,
    0x1.0p1,
    0x1.00000000000010p1,
    0x1.0000000000001p1,
    0x1.fffffffffffff0p-1,
    0x1.fffffffffffffp-1,
    0x1.p0,
    0x1.0p0,
    0x1.00000000000010p0,
    0x1.0000000000001p0,
    0x1.fffffffffffff0p-2,
    0x1.fffffffffffffp-2,
    0x1.p-1,
    0x1.0p-1,
    0x1.00000000000010p-1,
    0x1.0000000000001p-1,
    0x1.fffffffffffff0p-3,
    0x1.fffffffffffffp-3,
    0x1.p-2,
    0x1.0p-2,
    0x1.00000000000010p-2,
    0x1.0000000000001p-2,
    0x1.fffffffffffff0p-4,
    0x1.fffffffffffffp-4,
    0x1.p-3,
    0x1.0p-3,
    0x1.00000000000010p-3,
    0x1.0000000000001p-3,
    0x1.fffffffffffff0p-5,
    0x1.fffffffffffffp-5,
    0x1.p-4,
    0x1.0p-4,
    0x1.00000000000010p-4,
    0x1.0000000000001p-4,
    0x1.fffffffffffff0p-6,
    0x1.fffffffffffffp-6,
    0x1.p-5,
    0x1.0p-5,
    0x1.00000000000010p-5,
    0x1.0000000000001p-5,
    0x1.fffffffffffff0p-8,
    0x1.fffffffffffffp-8,
    0x1.p-7,
    0x1.0p-7,
    0x1.00000000000010p-7,
    0x1.0000000000001p-7,
    0x1.fffffffffffff0p-10,
    0x1.fffffffffffffp-10,
    0x1.p-9,
    0x1.0p-9,
    0x1.00000000000010p-9,
    0x1.0000000000001p-9,
    0x1.fffffffffffff0p-11,
    0x1.fffffffffffffp-11,
    0x1.p-10,
    0x1.0p-10,
    0x1.00000000000010p-10,
    0x1.0000000000001p-10,
    0x1.fffffffffffff0p-16,
    0x1.fffffffffffffp-16,
    0x1.p-15,
    0x1.0p-15,
    0x1.00000000000010p-15,
    0x1.0000000000001p-15,
    0x1.fffffffffffff0p-21,
    0x1.fffffffffffffp-21,
    0x1.p-20,
    0x1.0p-20,
    0x1.00000000000010p-20,
    0x1.0000000000001p-20,
    0x1.fffffffffffff0p-101,
    0x1.fffffffffffffp-101,
    0x1.p-100,
    0x1.0p-100,
    0x1.00000000000010p-100,
    0x1.0000000000001p-100,
    0x1.fffffffffffff0p-201,
    0x1.fffffffffffffp-201,
    0x1.p-200,
    0x1.0p-200,
    0x1.00000000000010p-200,
    0x1.0000000000001p-200,
    0x1.fffffffffffff0p-1001,
    0x1.fffffffffffffp-1001,
    0x1.p-1000,
    0x1.0p-1000,
    0x1.00000000000010p-1000,
    0x1.0000000000001p-1000,
    0x1.fffffffffffff0p1023,
    -0x1.fffffffffffffp1023,
    0x1.fffffffffffff0p1023,
    0x1.fffffffffffffp1023,
    HUGE_VAL,
    -HUGE_VAL,
    0x1.fffffffffffff0p1023,
    0x1.fffffffffffffp1023,
    0x1.fffffffffffff0p1023,
    -0x1.fffffffffffffp1023,
    0x1.ffffffffffffe0p1023,
    0x1.ffffffffffffep1023,
    0x1.ffffffffffffe0p1023,
    -0x1.ffffffffffffep1023,
    0x1.921fb54442d180p1,
    0x1.921fb54442d18p1,
    0x1.921fb54442d180p1,
    -0x1.921fb54442d18p1,
    0x1.921fb54442d180p0,
    0x1.921fb54442d18p0,
    0x1.921fb54442d180p0,
    -0x1.921fb54442d18p0,
    0x1.00000000000010p0,
    0x1.0000000000001p0,
    0x1.00000000000010p0,
    -0x1.0000000000001p0,
    0x1.p0,
    0x1.0p0,
    0x1.p0,
    -0x1.0p0,
    0x1.fffffffffffff0p-1,
    0x1.fffffffffffffp-1,
    0x1.fffffffffffff0p-1,
    -0x1.fffffffffffffp-1,
    0x1.921fb54442d180p-1,
    0x1.921fb54442d18p-1,
    0x1.921fb54442d180p-1,
    -0x1.921fb54442d18p-1,
    0x1.00000000000010p-1022,
    0x1.0000000000001p-1022,
    0x1.00000000000010p-1022,
    -0x1.0000000000001p-1022,
    0x1.p-1022,
    0x1.0p-1022,
    0x1.p-1022,
    -0x1.0p-1022,
    0x1.ffffffffffffe0p-1023,
    0x1.ffffffffffffep-1023,
    0x1.ffffffffffffe0p-1023,
    -0x1.ffffffffffffep-1023,
    0x1.ffffffffffffc0p-1023,
    0x1.ffffffffffffcp-1023,
    0x1.ffffffffffffc0p-1023,
    -0x1.ffffffffffffcp-1023,
    0x1.p-1073,
    0x1.0p-1073,
    0x1.p-1073,
    -0x1.0p-1073,
    0x1.p-1074,
    0x1.0p-1074,
    0x1.p-1074,
    -0x1.0p-1074,
    0.0,
    0.0,
    0.0,
    -0.0,
};

Test(my_fabs, bionic_intel_data)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(BIONIC_INTEL_DATA); ++i)
        do_test(BIONIC_INTEL_DATA[i]);
}

Test(my_fabs, glibc)
{
    do_test(-NAN);
    do_test(SNANL);
    do_test(-SNANL);
    do_test(4.9406564584124654e-324l);
    do_test(DBL_MIN);
    do_test(DBL_MAX);
    do_test(LDBL_MIN);
    do_test(LDBL_MAX);
    do_test(-4.9406564584124654e-324l);
    do_test(-DBL_MIN);
    do_test(-DBL_MAX);
    do_test(-LDBL_MIN);
    do_test(-LDBL_MAX);
    do_test(38.l);
}

Test(my_fabs, nlibc)
{
    do_test(-5.l);
    do_test(-.0l);
    do_test(100.l);
    do_test(-100.l);
    do_test(-100.5l);
}

Test(my_fabs, limits)
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
