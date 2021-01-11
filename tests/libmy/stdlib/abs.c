/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests abs
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include <limits.h>

static void test_abs(int x)
{
    cr_assert_eq(my_abs(x), abs(x));
}

Test(my_abs, freebsd_basic)
{
    test_abs(0);
    test_abs(+0);
    test_abs(-0);
    test_abs(-0x1010);
    test_abs(INT_MAX);
    test_abs(-INT_MAX);
}

Test(my_abs, llvm_basic)
{
    test_abs(1);
    test_abs(2);
    test_abs(0x7FFFFFFE);
    test_abs(0x7FFFFFFF);
    test_abs(0x80000001);
    test_abs(0x80000002);
    test_abs(0xFFFFFFFE);
    test_abs(0xFFFFFFFF);
}

Test(my_abs, gcc_testsuite)
{
    test_abs(12);
    test_abs(-1);
    test_abs(INT_MIN + 1);
    test_abs(SCHAR_MIN + 1);
    test_abs(SCHAR_MAX);
    test_abs(SHRT_MAX);
    test_abs(SHRT_MIN + 1);
}

Test(my_abs, cloudlibc_example)
{
    test_abs(42);
    test_abs(-42);
}

Test(my_abs, qemu_cris)
{
    test_abs(0xFFFF);
    test_abs(-31);
}

Test(my_abs, z88dk)
{
    test_abs(-30000);
    test_abs(-456);
    test_abs(133);
    test_abs(30000);
}
