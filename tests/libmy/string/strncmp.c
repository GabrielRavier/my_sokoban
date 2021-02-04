/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines strncmp
*/

#include "my/string.h"
#include "../tests_header.h"
#include <string.h>

int sign(int x)
{
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

static void do_one_test(const char *s1, const char *s2, size_t n)
{
    cr_assert_eq(sign(my_strncmp(s1, s2, n)), sign(strncmp(s1, s2, n)));
    cr_assert_eq(sign(my_strncmp(s2, s1, n)), sign(strncmp(s2, s1, n)));
}

Test(my_strncmp, gnulib)
{
    do_one_test("", "", 0);
    do_one_test("", "", 1);
    do_one_test("", "", 1000000);

    do_one_test("", "foo", 0);
    do_one_test("", "foo", 1);
    do_one_test("", "foo", 2);
    do_one_test("", "foo", 3);
    do_one_test("", "foo", 4);
    do_one_test("", "foo", 5);
    do_one_test("", "foo", 1000000);

    do_one_test("foo", "foo", 0);
    do_one_test("foo", "foo", 1);
    do_one_test("foo", "foo", 2);
    do_one_test("foo", "foo", 3);
    do_one_test("foo", "foo", 4);
    do_one_test("foo", "foo", 5);
    do_one_test("foo", "foo", 1000000);

    do_one_test("foo", "bar", 0);
    do_one_test("foo", "bar", 1);
    do_one_test("foo", "bar", 2);
    do_one_test("foo", "bar", 3);
    do_one_test("foo", "bar", 4);
    do_one_test("foo", "bar", 5);
    do_one_test("foo", "bar", 1000000);

    do_one_test("foo", "foobar", 0);
    do_one_test("foo", "foobar", 1);
    do_one_test("foo", "foobar", 2);
    do_one_test("foo", "foobar", 3);
    do_one_test("foo", "foobar", 4);
    do_one_test("foo", "foobar", 5);
    do_one_test("foo", "foobar", 6);
    do_one_test("foo", "foobar", 7);
    do_one_test("foo", "foobar", 8);
    do_one_test("foo", "foobar", 1000000);

    do_one_test("oomph", "oops", 0);
    do_one_test("oomph", "oops", 1);
    do_one_test("oomph", "oops", 2);
    do_one_test("oomph", "oops", 3);
    do_one_test("oomph", "oops", 4);
    do_one_test("oomph", "oops", 5);
    do_one_test("oomph", "oops", 6);
    do_one_test("oomph", "oops", 1000000);
}
