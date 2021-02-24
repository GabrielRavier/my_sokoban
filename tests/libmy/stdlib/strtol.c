/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests strtol
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/cpp-like/iterator.h"
#include "my/string.h"
#include "my/inttypes.h"
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

static void do_one_test_with_endptr_choice(const char *num, int base,
    bool end_num_ptr_unchanged)
{
    char *end_num_ptr_us = (char *)0xDEADBEEF, *end_num_ptr_libc;
    intmax_t our_result, libc_result;
    int our_errno, libc_errno;

#define DO_ONE_STRTOL(our_func, libc_func) \
    errno = 0xDEADBEEF; \
    our_result = our_func(num, &end_num_ptr_us, base); \
    our_errno = errno; \
    errno = 0xDEADBEEF; \
    libc_result = libc_func(num, &end_num_ptr_libc, base); \
    libc_errno = errno; \
    cr_assert_eq(our_errno, libc_errno); \
    cr_assert_eq(our_result, libc_result); \
    if (end_num_ptr_unchanged) \
        cr_assert_eq(end_num_ptr_us, (char *)0xDEADBEEF); \
    else \
        cr_assert_eq(end_num_ptr_us, end_num_ptr_libc);

    DO_ONE_STRTOL(my_strtol, strtol);
    DO_ONE_STRTOL(my_strtoll, strtoll);
    DO_ONE_STRTOL(my_strtoimax, strtoimax);
    DO_ONE_STRTOL(my_strtoul, strtoul);
    DO_ONE_STRTOL(my_strtoull, strtoull);
    DO_ONE_STRTOL(my_strtoumax, strtoumax);
}

static void do_one_test(const char *num, int base)
{
    do_one_test_with_endptr_choice(num, base, false);
}

Test(my_strtol, opensolaris_invalid_base)
{
    do_one_test_with_endptr_choice("0", 37, true);
    do_one_test_with_endptr_choice("0", 1, true);
    do_one_test_with_endptr_choice("1231894", 37, true);
    do_one_test_with_endptr_choice("4219482", 1, true);
}

Test(my_strtol, opensolaris_basic)
{
    do_one_test("0", 2);
    do_one_test("1", 36);
    do_one_test("0x20", 16);
    do_one_test("0x20", 0);
    do_one_test("-32", 10);
    do_one_test("010", 8);
    do_one_test("010", 0);
    do_one_test("101010", 2);
    do_one_test("9223372036854775807", 10);
    do_one_test("-9223372036854775808", 10);
    do_one_test("0777777777777777777777", 8);
    do_one_test("-01000000000000000000000", 8);
    do_one_test("1000000000000000000000", 8);
    do_one_test("-1000000000000000000001", 8);
    do_one_test("baddcafe", 16);
    do_one_test("12j", 10);
    do_one_test("102", 2);
    do_one_test("-0DTrace4EverZ", 36);
    do_one_test("1985", 0);
    do_one_test("-2012", 0);
    do_one_test("", 0);
}

Test(my_strtol, netbsd_bases)
{
    do_one_test("123456789", 0);
    do_one_test("111010110111100110100010101", 2);
    do_one_test("22121022020212200", 3);
    do_one_test("13112330310111", 4);
    do_one_test("223101104124", 5);
    do_one_test("20130035113", 6);
    do_one_test("3026236221", 7);
    do_one_test("726746425", 8);
    do_one_test("277266780", 9);
    do_one_test("123456789", 10);
    do_one_test("63762A05", 11);
    do_one_test("35418A99", 12);
    do_one_test("1C767471", 13);
    do_one_test("12579781", 14);
    do_one_test("AC89BC9", 15);
    do_one_test("75BCD15", 16);
    do_one_test("1234567", 8);
    do_one_test("01234567", 8);
    do_one_test("0123456789", 10);
    do_one_test("0x75bcd15", 16);
    do_one_test("0X75bcd15", 16);
}

Test(my_strtol, netbsd_case)
{
    do_one_test("abcd", 16);
    do_one_test("     dcba", 16);
    do_one_test("abcd dcba", 16);
    do_one_test("abc0x123", 16);
    do_one_test("abcd\0x123", 16);
    do_one_test("ABCD", 16);
    do_one_test("aBcD", 16);
    do_one_test("0xABCD", 16);
    do_one_test("0xABCDX", 16);
    do_one_test("0XABCDX", 16);
}

Test(my_strtol, netbsd_range)
{
    do_one_test("20000000000", 8);
    do_one_test("2147483648", 10);
    do_one_test("80000000", 16);
    do_one_test("1000000000000000000000", 8);
    do_one_test("9223372036854775808", 10);
    do_one_test("8000000000000000", 16);
}

Test(my_strtol, netbsd_sign)
{
    do_one_test("1", 0);
    do_one_test(" 2", 0);
    do_one_test("  3", 0);
    do_one_test(" -3", 0);
    do_one_test("--1", 0);
    do_one_test("+-2", 0);
    do_one_test("++3", 0);
    do_one_test("+9", 0);
    do_one_test("+123", 0);
    do_one_test("-1 3", 0);
    do_one_test("-1.3", 0);
    do_one_test("-  3", 0);
    do_one_test("+33.", 0);
    do_one_test("30x0", 0);
}

Test(my_strtol, bionic)
{
    do_one_test_with_endptr_choice("123", -1, true);
    do_one_test_with_endptr_choice("123", 1, true);
    do_one_test_with_endptr_choice("123", 37, true);
    do_one_test("-123", 10);
    do_one_test("+123", 10);
    do_one_test("0xy", 16);
    do_one_test("0xy", 0);
    do_one_test("0xab", 0);
    do_one_test("0Xab", 0);
    do_one_test("0xAB", 0);
    do_one_test("0XAB", 0);
    do_one_test("0xAb", 0);
    do_one_test("0XAb", 0);
    do_one_test("0666", 0);

    intmax_t minimums[] = {
        SCHAR_MIN, SHRT_MIN, INT_MIN, LONG_MIN, LLONG_MIN, INTMAX_MIN,
        SCHAR_MAX, SHRT_MAX, INT_MAX, LONG_MAX, LLONG_MAX, INTMAX_MAX,
        UCHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX, UINTMAX_MAX,
        0, 1, -1, 2, -2
     };
    for (size_t i = 0; i < MY_ARRAY_SIZE(minimums); ++i) {
        char buffer[300];
        cr_assert_geq(snprintf(buffer, sizeof(buffer), "%jd", minimums[i]), 0);
        do_one_test(buffer, 0);
        ++buffer[my_strlen(buffer) - 1];
        do_one_test(buffer, 0);
        cr_assert_geq(snprintf(buffer, sizeof(buffer), "%jx", (uintptr_t)minimums[i]), 0);
        do_one_test(buffer, 0);
        cr_assert_geq(snprintf(buffer, sizeof(buffer), "%jX", (uintptr_t)minimums[i]), 0);
        do_one_test(buffer, 0);
        cr_assert_geq(snprintf(buffer, sizeof(buffer), "%jo", (uintptr_t)minimums[i]), 0);
        do_one_test(buffer, 0);
    }

    do_one_test("2190839021839012389021839123309218390218390128390218390128390218390128390128309128390218390812093812093821abc", 0);
    do_one_test("-2190839021839012389021839123309218390218390128390218390128390218390128390128309128390218390812093812093821abc", 0);
}

Test(my_strtol, skiboot)
{
    do_one_test("0x800", 0);
    do_one_test("0x0x800", 0);
    do_one_test_with_endptr_choice("z", -1, true);
    do_one_test_with_endptr_choice("11111", 1, true);
    do_one_test_with_endptr_choice("z", 37, true);
    do_one_test("z", 36);
    do_one_test("-Y", 36);
    do_one_test("42, and stuff.", 10);
    do_one_test("0", 10);
    do_one_test("1", 10);
    do_one_test(" 123456", 10);
    do_one_test("-72", 10);
    do_one_test("9999999999", 10);
    do_one_test("hello!123", 10);
    do_one_test("42isthemagicnumber", 10);
    do_one_test(" 123456", 0);
    do_one_test("Y", 36);
}

Test(my_strtol, plauger)
{
    do_one_test("-a0", 11);
    do_one_test("54", 4);
    do_one_test("0xFfg", 16);
}

Test(my_strtol, escape)
{
    do_one_test("1234", 10);
    do_one_test(" \t12", 0);
    do_one_test("+234", 10);
    do_one_test("-1234", 10);
    do_one_test("55", 8);
    do_one_test("055", 0);
    do_one_test("AbC", 16);
    do_one_test("0xaBC", 0);
    do_one_test("0x8000000000000000", 16);
    do_one_test("0x80000000", 16);
    do_one_test("aiz", 36);
    do_one_test("01101", 2);
    do_one_test("0", 7);
    do_one_test("-1", 7);
}

Test(my_strtol, wine_msvcrt)
{
    do_one_test("-1234", 0);
    do_one_test("1234", 0);
    do_one_test("2147483647L", 0);
    do_one_test("-2147483648L", 0);
    do_one_test("4294967295UL", 0);
    do_one_test("9223372036854775807L", 0);
    do_one_test("-2", 0);
    do_one_test("-4294967294", 0);
    do_one_test("-4294967295", 0);
    do_one_test("-4294967296", 0);
    do_one_test("-0x", 0);
}
