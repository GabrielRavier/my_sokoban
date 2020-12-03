/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests bigint addition
*/

#include "my/bigint.h"
#include <criterion/criterion.h>
#include <limits.h>

static void do_test(int a, int b)
{
    struct my_bigint *bigint_a = my_bigint_new_from_int(a);
    struct my_bigint *bigint_b = my_bigint_new_from_int(b);
    struct my_bigint *bigint_result = my_bigint_new_from_int(a + b);
    cr_assert_eq(my_bigint_compare(my_bigint_add(bigint_a, bigint_b),
            bigint_result), 0);
    my_bigint_free(bigint_a);
    my_bigint_free(bigint_b);
    my_bigint_free(bigint_result);
}

Test(my_bigint_add, very_simple_tests)
{
    for (int i = -100; i < 100; ++i)
        for (int j = -100; j < 100; ++j)
            do_test(i, j);

    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = -100; j < 100; ++j)
            do_test(i, j);

    for (int i = -100; i < 100; ++i)
        for (int j = -10000000; j < (-10000000 + 100); ++j)
            do_test(i, j);

    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = -10000000; j < (-10000000 + 100); ++j)
            do_test(i, j);

    for (int i = 10000000; i > (10000000 - 100); --i)
        for (int j = -100; j < 100; ++j)
            do_test(i, j);

    for (int i = 10000000; i > (10000000 - 100); --i)
        for (int j = -10000000; j < (-10000000 + 100); ++j)
            do_test(i, j);

    for (int i = -100; i < 100; ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);

    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);

    for (int i = -100; i < 100; ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);

    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);

    for (int i = 10000000; i > (10000000 - 100); --i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);
}
