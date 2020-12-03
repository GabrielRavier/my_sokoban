/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memmem
*/

#include "my/string.h"
#include <criterion/criterion.h>
#include <string.h>

static void do_one_test(const void *haystack, size_t haystack_length, const void *needle, size_t needle_length)
{
    cr_assert_eq(my_memmem(haystack, haystack_length, needle, needle_length), memmem(haystack, haystack_length, needle, needle_length));
}

Test(my_memmem, netbsd_basic)
{
    do_one_test("0123456789", 10, "", 0);
    do_one_test("", 0, "", 0);
    do_one_test("", 0, "0123", 4);
    do_one_test("0", 1, "0123", 4);
    do_one_test("0123456789", 10, "0123", 4);
    do_one_test("0123456789", 10, "456", 3);
    do_one_test("0123456789", 10, "789", 3);
    do_one_test("0123456789", 10, "0", 1);
    do_one_test("0123456789", 10, "9", 1);
    do_one_test("0123456789", 10, "abc", 3);
    do_one_test("0123456789", 10, "654", 3);
    do_one_test("0123456789", 10, "89abc", 5);
}
