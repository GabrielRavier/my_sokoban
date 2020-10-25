/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_strtol_base_str
*/

#include <criterion/criterion.h>
#include "my/stdlib.h"
#include "my/string.h"
#include <stdio.h>

static void test_strtol(const char *string, const char *base, long expected_result, ssize_t length)
{
    char *end_pointer;
    cr_assert_eq(my_strtol_base_str(string, &end_pointer, base), expected_result);
    cr_assert_eq(end_pointer - string, length);
}

static void test_strtol_base10(const char *string, long expected_result, size_t length)
{
    test_strtol(string, "0123456789", expected_result, length);
}

Test(my_strtol_base_str, simple_tests)
{
    char buffer[16];

    for (long i = 0; i < 100; ++i) {
        sprintf(buffer, "%ld", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%lx", i);
        test_strtol(buffer, "0123456789abcdef", i, my_strlen(buffer));
    }
    test_strtol_base10(" +12afdopwqk", 12, 4);
}
