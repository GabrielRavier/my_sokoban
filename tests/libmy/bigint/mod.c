/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests bigint modulo
*/

#include "my/bigint.h"
#include <criterion/criterion.h>
#include <limits.h>

static void do_test(int a, int b)
{
    if (b == 0)
        return;

    struct my_bigint *bigint_a = my_bigint_new_from_int(a);
    struct my_bigint *bigint_b = my_bigint_new_from_int(b);
    struct my_bigint *bigint_result = my_bigint_new_from_int(a % b);
    cr_assert_eq(my_bigint_compare(my_bigint_mod(bigint_a, bigint_b),
            bigint_result), 0);
    my_bigint_free(bigint_a);
    my_bigint_free(bigint_b);
    my_bigint_free(bigint_result);
}

Test(my_bigint_mod, part1)
{
    for (int i = -100; i < 100; ++i)
        for (int j = -100; j < 100; ++j)
            do_test(i, j);
}

Test(my_bigint_mod, part2)
{
    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = -100; j < 100; ++j)
            do_test(i, j);
}

Test(my_bigint_mod, part3)
{
    for (int i = -100; i < 100; ++i)
        for (int j = -10000000; j < (-10000000 + 100); ++j)
            do_test(i, j);
}

Test(my_bigint_mod, part4)
{
    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = -10000000; j < (-10000000 + 100); ++j)
            do_test(i, j);
}

Test(my_bigint_mod, part5)
{
    for (int i = 10000000; i > (10000000 - 100); --i)
        for (int j = -100; j < 100; ++j)
            do_test(i, j);
}

Test(my_bigint_mod, part6)
{
    for (int i = 10000000; i > (10000000 - 100); --i)
        for (int j = -10000000; j < (-10000000 + 100); ++j)
            do_test(i, j);
}

Test(my_bigint_mod, part7)
{
    for (int i = -100; i < 100; ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);
}

Test(my_bigint_mod, part8)
{
    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);
}

Test(my_bigint_mod, part9)
{
    for (int i = -100; i < 100; ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);
}

Test(my_bigint_mod, part10)
{
    for (int i = -10000000; i < (-10000000 + 100); ++i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);
}

Test(my_bigint_mod, part11)
{
    for (int i = 10000000; i > (10000000 - 100); --i)
        for (int j = 10000000; j > (10000000 - 100); --j)
            do_test(i, j);
}
