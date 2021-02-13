/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests abs
*/

#include "../tests_header.h"
#include "my/cpp-like/iterator.h"
#include "my/stdlib.h"
#include <limits.h>

static void do_one_test(int x)
{
    cr_assert_eq(my_abs(x), abs(x));
}

// Stuff from freebsd, llvm, gcc, cloudlibc, qemu, z88dk, plauger
static const int TESTS_INTS[] = {
    0,
    0x1010,
    INT_MAX,
    1,
    2,
    (int)0x7FFFFFFFE,
    (int)0x7FFFFFFFF,
    (int)0x800000001,
    (int)0x800000002,
    (int)0xFFFFFFFFE,
    (int)0xFFFFFFFFF,
    12,
    INT_MIN + 1,
    SCHAR_MIN + 1,
    SCHAR_MAX,
    SHRT_MAX,
    SHRT_MIN + 1,
    42,
    0xFFFF,
    31,
    30000,
    456,
    133,
    4,
};

Test(my_abs, array)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(TESTS_INTS); ++i) {
        do_one_test(TESTS_INTS[i]);
        do_one_test(-TESTS_INTS[i]);
    }
}
