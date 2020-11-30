/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memmove
*/

#include "my/string.h"
#include <criterion/criterion.h>
#include <string.h>

// Are tested overlapping moves of 0...MAX bytes
#define MAX 128

static void retval_test_memmove(unsigned char *destination, const unsigned char *source, size_t n)
{
    cr_assert_eq(my_memmove(destination, source, n), destination);
}

static void fill(unsigned char destination[MAX * 3])
{
    for (size_t i = 0; i < MAX * 3; ++i)
        destination[i] = (10 + i) % MAX;
}

Test(my_memmove, non_overlap)
{
    unsigned char from_test[MAX * 3];
    unsigned char to_test[MAX * 3];
    unsigned char from_known[MAX * 3];
    unsigned char to_known[MAX * 3];

    for (size_t i = 0; i < MAX; ++i) {
        fill(from_test);
        fill(to_test);
        retval_test_memmove(to_test + MAX, from_test + MAX + 1, i);

        fill(from_known);
        fill(to_known);
        memmove(to_known + MAX, from_known + MAX + 1, i);

        cr_assert_eq(my_memcmp(to_known, to_test, sizeof(to_known)), 0);
    }
}

Test(my_memmove, overlap_from_before)
{
    unsigned char to_test[MAX * 3];
    unsigned char to_known[MAX * 3];

    for (size_t i = 0; i < MAX; ++i)
        for (size_t j = 0; j < i; ++j) {
            fill(to_test);
            retval_test_memmove(to_test + MAX * 2 - i, to_test + MAX * 2 - i - j, i);
      
            fill(to_known);
            memmove(to_known + MAX * 2 - i, to_known + MAX * 2 - i - j, i);

            cr_assert_eq(my_memcmp(to_known, to_test, sizeof(to_known)), 0);
        }
}

Test(my_memmove, overlap_from_after)
{
    unsigned char to_test[MAX * 3];
    unsigned char to_known[MAX * 3];

    for (size_t i = 0; i < MAX; ++i)
        for (size_t j = 0; j < i; ++j) {
            fill(to_test);
            retval_test_memmove(to_test + MAX, to_test + MAX + j, i);
      
            fill(to_known);
            memmove(to_known + MAX, to_known + MAX + j, i);

            cr_assert_eq(my_memcmp(to_known, to_test, sizeof(to_known)), 0);
        }
}
