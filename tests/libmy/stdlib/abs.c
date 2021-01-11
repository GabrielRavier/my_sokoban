/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests abs
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include <limits.h>

static void do_test(int x)
{
    cr_assert_eq(my_abs(x), abs(x));
}

Test(my_abs, freebsd_basic)
{
    do_test(0);
    do_test(+0);
    do_test(-0);
    do_test(-0x1010);
    do_test(INT_MAX);
    do_test(-INT_MAX);
}

Test(my_abs, llvm_basic)
{
    do_test(1);
    do_test(2);
    do_test(0x7FFFFFFE);
    do_test(0x7FFFFFFF);
    do_test(0x80000001);
    do_test(0x80000002);
    do_test(0xFFFFFFFE);
    do_test(0xFFFFFFFF);
}

Test(my_abs, gcc_testsuite)
{
    do_test(12);
    do_test(-1);
    do_test(INT_MIN + 1);
    do_test(SCHAR_MIN + 1);
    do_test(SCHAR_MAX);
    do_test(SHRT_MAX);
    do_test(SHRT_MIN + 1);
}

Test(my_abs, cloudlibc_example)
{
    do_test(42);
    do_test(-42);
}

Test(my_abs, qemu_cris)
{
    do_test(0xFFFF);
    do_test(-31);
}

Test(my_abs, z88dk)
{
    do_test(-30000);
    do_test(-456);
    do_test(133);
    do_test(30000);
}
