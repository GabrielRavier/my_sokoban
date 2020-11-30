/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memcmp
*/

#include "my/string.h"
#include <criterion/criterion.h>

Test(my_memcmp, very_simple)
{
    cr_assert_eq(my_memcmp("a", "b", 0), 0);
    cr_assert_eq(my_memcmp("", "", 0), 0);
}

Test(my_memcmp, basic_fuzz)
{
    unsigned char data1[256], data2[256];

    for (size_t i = 0; i < 256; ++i)
        data1[i] = data2[i] = i ^ 0x55;
    for (size_t i = 1; i < 256; ++i)
        cr_assert_eq(my_memcmp(data1, data2, i), 0);
    for (size_t i = 1; i < 256; ++i)
        cr_assert_eq(my_memcmp(data1 + i, data2 + i, 256 - i), 0);
}

Test(my_memcmp, more_fuzz)
{
    unsigned char data1[256], data2[256];

    for (size_t i = 0; i < 256; ++i) {
        data1[i] = i;
        data2[i] = i ^ 0x55;
    }
    for (size_t i = 1; i < 256; ++i)
        cr_assert_neq(my_memcmp(data1, data2, i), 0);
    for (size_t i = 1; i < 256; ++i)
        cr_assert_neq(my_memcmp(data1 + i, data2 + i, 256 - i), 0);
}

Test(my_memcmp, really_more_fuzz)
{
    unsigned char data1[256], data2[256];

    my_memset(data1, 'a', sizeof(data1));
    my_memset(data2, 'a', sizeof(data2));
    data1[128] = 0xFF;
    data2[128] = 0;
    for (size_t i = 1; i < 66; ++i) {
        cr_assert_eq(my_memcmp(data1 + 128, data2 + 128, i), 0xFF);
        cr_assert_eq(my_memcmp(data2 + 128, data1 + 128, i), -0xFF);
        cr_assert_eq(my_memcmp(data1 + 129 - i, data2 + 129 - i, i), 0xFF);
        cr_assert_eq(my_memcmp(data2 + 129 - i, data1 + 129 - i, i), -0xFF);
        cr_assert_eq(my_memcmp(data1 + 129 - i, data2 + 129 - i, i * 2), 0xFF);
        cr_assert_eq(my_memcmp(data2 + 129 - i, data1 + 129 - i, i * 2), -0xFF);
    }
    data1[128] = 'c';
    data2[128] = 'e';
    for (size_t i = 1; i < 66; ++i) {
        cr_assert_eq(my_memcmp(data1 + 128, data2 + 128, i), -2);
        cr_assert_eq(my_memcmp(data2 + 128, data1 + 128, i), 2);
        cr_assert_eq(my_memcmp(data1 + 129 - i, data2 + 129 - i, i), -2);
        cr_assert_eq(my_memcmp(data2 + 129 - i, data1 + 129 - i, i), 2);
        cr_assert_eq(my_memcmp(data1 + 129 - i, data2 + 129 - i, i * 2), -2);
        cr_assert_eq(my_memcmp(data2 + 129 - i, data1 + 129 - i, i * 2), 2);
    }
    my_memset(data1 + 129, 'A', sizeof(data1) - 129);
    my_memset(data2 + 129, 'Z', sizeof(data2) - 129);
    for (size_t i = 1; i < 66; ++i) {
        cr_assert_eq(my_memcmp(data1 + 128, data2 + 128, i), -2);
        cr_assert_eq(my_memcmp(data2 + 128, data1 + 128, i), 2);
        cr_assert_eq(my_memcmp(data1 + 129 - i, data2 + 129 - i, i), -2);
        cr_assert_eq(my_memcmp(data2 + 129 - i, data1 + 129 - i, i), 2);
        cr_assert_eq(my_memcmp(data1 + 129 - i, data2 + 129 - i, i * 2), -2);
        cr_assert_eq(my_memcmp(data2 + 129 - i, data1 + 129 - i, i * 2), 2);
    }
}
