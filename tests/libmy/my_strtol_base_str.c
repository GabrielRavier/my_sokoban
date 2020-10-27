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
#include <limits.h>

static void test_strtol(const char *string, const char *base,
    long expected_result, ssize_t length)
{
    char *end_pointer;
    cr_assert_eq(my_strtol_base_str(string, &end_pointer, base),
        expected_result);
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

Test(my_strtol_base_str, simple_tests)
{
    char buffer[32];
    for (long i = 0; i <= 100; ++i) {
        sprintf(buffer, "%ld", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%lx", i);
        test_strtol_base16(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%lo", i);
        test_strtol_base8(buffer, i, my_strlen(buffer));
    }
    for (long i = 0; i >= -100; --i) {
        sprintf(buffer, "%ld", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "-%lx", -i);
        test_strtol_base16(buffer, i, my_strlen(buffer));
        sprintf(buffer, "-%lo", -i);
        test_strtol_base8(buffer, i, my_strlen(buffer));
    }
    for (long i = LONG_MAX; i >= (LONG_MAX - 100); --i) {
        sprintf(buffer, "%ld", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%lx", i);
        test_strtol_base16(buffer, i, my_strlen(buffer));
        sprintf(buffer, "%lo", i);
        test_strtol_base8(buffer, i, my_strlen(buffer));
    }
    for (long i = LONG_MIN; i <= (LONG_MIN + 100); ++i) {
        sprintf(buffer, "%ld", i);
        test_strtol_base10(buffer, i, my_strlen(buffer));
        sprintf(buffer, "-%lx", -(unsigned long)i);
        test_strtol_base16(buffer, i, my_strlen(buffer));
        sprintf(buffer, "-%lo", -(unsigned long)i);
        test_strtol_base8(buffer, i, my_strlen(buffer));
    }
    test_strtol_base10(" +12afdopwqk", 12, 4);
    test_strtol_base10("", 0, 0);
    test_strtol_base10("-", 0, 0);
    test_strtol_base10("+", 0, 0);
    test_strtol_base10("    ", 0, 0);
    test_strtol_base10("0", 0, 1);
    test_strtol_base10("0 ", 0, 1);
    test_strtol_base10(" 0", 0, 2);
    test_strtol_base10("\t0", 0, 2);
    test_strtol_base10(" \t0", 0, 3);
    test_strtol_base10(" \t 0", 0, 4);
    test_strtol_base10("0x0", 0, 1);
    test_strtol_base10("0000", 0, 4);
    test_strtol_base10("+0", 0, 2);
    test_strtol_base10("-0", 0, 2);
    test_strtol_base10("*", 0, 0);
    test_strtol_base10("5 *", 5, 1);
    test_strtol_base10("+ 5 *", 0, 0);
}
