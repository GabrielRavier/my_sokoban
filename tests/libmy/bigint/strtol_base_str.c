/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_strtol_base_str
*/

#include "my/bigint.h"
#include <criterion/criterion.h>
#include "my/stdlib.h"
#include "my/string.h"
#include <stdio.h>
#include <limits.h>

static void test_strtol(const char *string, const char *base,
    long expected_result, ssize_t length)
{
    char *end_pointer;
    struct my_bigint *converted_number =
        my_bigint_strtol_base_str(string, &end_pointer, base);
    cr_assert_eq(my_bigint_compare_int(converted_number, expected_result), 0);
    cr_assert_eq(end_pointer - string, length);
}

static void test_strtol_base10(const char *string, long expected_result,
    size_t length)
{
    test_strtol(string, "0123456789", expected_result, length);
}

static void test_strtol_base16(const char *string, long expected_result,
    size_t length)
{
    test_strtol(string, "0123456789abcdef", expected_result, length);
}

static void test_strtol_base8(const char *string, long expected_result,
    size_t length)
{
    test_strtol(string, "01234567", expected_result, length);
}

Test(my_bigint_strtol_base_str, simple_tests)
{
    char buffer[32];
    for (int i = 0; i <= 100; ++i) {
        sprintf(buffer, "%d", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%x", i);
        test_strtol_base16(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%o", i);
        test_strtol_base8(buffer, i, my_strlen(buffer));
    }
    for (int i = INT_MAX; i >= (INT_MAX - 100); --i) {
        sprintf(buffer, "%d", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%x", i);
        test_strtol_base16(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%o", i);
        test_strtol_base8(buffer, i, my_strlen(buffer));
    }
    test_strtol_base10("", 0, 0);
    test_strtol_base10("-", 0, 0);
    test_strtol_base10("+", 0, 0);
    test_strtol_base10("    ", 0, 0);
    test_strtol_base10("0", 0, 1);
    test_strtol_base10("0 ", 0, 1);
    test_strtol_base10("0x0", 0, 1);
    test_strtol_base10("0000", 0, 4);
    test_strtol_base10("*", 0, 0);
    test_strtol_base10("5 *", 5, 1);
}
