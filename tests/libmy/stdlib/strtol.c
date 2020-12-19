/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_strtol
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include <errno.h>

static void do_one_test_with_endptr_choice(const char *num, int base, bool endptr_unchanged)
{
    char *end_num_ptr_us = (char *)0xDEADBEEF;
    char *end_num_ptr_libc;

    errno = -213908;

    long our_result = my_strtol(num, &end_num_ptr_us, base);
    int our_errno = errno;

    errno = -213908;

    long libc_result = strtol(num, &end_num_ptr_libc, base);
    int libc_errno = errno;

    cr_assert_eq(our_errno, libc_errno);
    cr_assert_eq(our_result, libc_result);
    if (endptr_unchanged)
        cr_assert_eq(end_num_ptr_us, (char *)0xDEADBEEF);
    else
        cr_assert_eq(end_num_ptr_us, end_num_ptr_libc);
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
