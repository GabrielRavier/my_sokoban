/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fpclassify
*/

#include "../tests_header.h"
#include "random_floats.h"
#include "my/math.h"
#include "my/cpp-like/iterator.h"
#include <float.h>

static void do_one_test(long double x)
{
    cr_assert_eq(my_fpclassify(x), fpclassify(x));
    cr_assert_eq(my_fpclassify((double)x), fpclassify((double)x));
    cr_assert_eq(my_fpclassify((float)x), fpclassify((float)x));
}

Test(my_fpclassify, random_floats)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(RANDOM_FLOATS); ++i) {
        do_one_test(RANDOM_FLOATS[i]);
        do_one_test(-RANDOM_FLOATS[i]);
    }
}
