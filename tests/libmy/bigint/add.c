/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests bigint addition
*/

#include "my/bigint.h"
#include <criterion/criterion.h>

static void do_test(int a, int b, int result)
{
    struct my_bigint *bigint_a = my_bigint_new_from_int(a);
    struct my_bigint *bigint_b = my_bigint_new_from_int(b);
    struct my_bigint *bigint_result = my_bigint_new_from_int(result);
    cr_assert_eq(my_bigint_compare(my_bigint_add(bigint_a, bigint_b), bigint_result), 0);
}

Test(my_bigint_add, very_simple_tests)
{
    do_test(0, 0, 0);
    do_test(0, 5, 5);
    do_test(5, 0, 5);
    do_test(5, 5, 10);
    do_test(5, 6, 11);
    do_test(6, 5, 11);
    do_test(0, 6, 6);
    do_test(6, 0, 6);
    do_test(-5, 0, -5);
    do_test(-5, 5, 0);
    do_test(-5, 6, 1);
    do_test(-6, 5, -1);
    do_test(-6, 0, -6);
    do_test(0, -5, -5);
    do_test(5, -5, 0);
    do_test(5, -6, -1);
    do_test(6, -5, 1);
    do_test(0, -6, -6);
}
