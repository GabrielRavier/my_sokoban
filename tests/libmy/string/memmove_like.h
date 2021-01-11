/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memmove
*/

#include "../tests_header.h"
#include "my/string.h"
#include "my/macros.h"
#include <string.h>

// Are tested overlapping moves of 0...MAX bytes
#define MAX 130

static void fill(unsigned char destination[MAX * 3])
{
    for (size_t i = 0; i < MAX * 3; ++i)
        destination[i] = (10 + i) % MAX;
}

Test(MEMMOVE_LIKE_FUNC_TEST_NAME, non_overlap)
{
    unsigned char from_test[MAX * 3];
    unsigned char to_test[MAX * 3];
    unsigned char from_known[MAX * 3];
    unsigned char to_known[MAX * 3];

    for (size_t i = 0; i < MAX; ++i) {
        fill(from_test);
        fill(to_test);
        MEMMOVE_LIKE_FUNC(to_test + MAX, from_test + MAX + 1, i);

        fill(from_known);
        fill(to_known);
        memmove(to_known + MAX, from_known + MAX + 1, i);

        cr_assert_eq(my_memcmp(to_known, to_test, sizeof(to_known)), 0);
    }
}

Test(MEMMOVE_LIKE_FUNC_TEST_NAME, overlap_from_before)
{
    unsigned char to_test[MAX * 3];
    unsigned char to_known[MAX * 3];

    for (size_t i = 0; i < MAX; ++i)
        for (size_t j = 0; j < i; ++j) {
            fill(to_test);
            MEMMOVE_LIKE_FUNC(to_test + MAX * 2 - i, to_test + MAX * 2 - i - j, i);
      
            fill(to_known);
            memmove(to_known + MAX * 2 - i, to_known + MAX * 2 - i - j, i);

            cr_assert_eq(my_memcmp(to_known, to_test, sizeof(to_known)), 0);
        }
}

Test(MEMMOVE_LIKE_FUNC_TEST_NAME, overlap_from_after)
{
    unsigned char to_test[MAX * 3];
    unsigned char to_known[MAX * 3];

    for (size_t i = 0; i < MAX; ++i)
        for (size_t j = 0; j < i; ++j) {
            fill(to_test);
            MEMMOVE_LIKE_FUNC(to_test + MAX, to_test + MAX + j, i);

            fill(to_known);
            memmove(to_known + MAX, to_known + MAX + j, i);

            cr_assert_eq(my_memcmp(to_known, to_test, sizeof(to_known)), 0);
        }
}

static void memmove_test(size_t dest_offset, size_t src_offset, size_t n)
{
    char buffer1[0x4000];
    char buffer2[0x4000];

    for (size_t i = 0; i < 0x4000; ++i)
        buffer1[i] = buffer2[i] = (char)(i % 0x100);

    memmove(buffer1 + dest_offset, buffer1 + src_offset, n);
    MEMMOVE_LIKE_FUNC(buffer2 + dest_offset, buffer2 + src_offset, n);
    cr_assert_eq(my_memcmp(buffer1, buffer2, 0x4000), 0);
}

Test(MEMMOVE_LIKE_FUNC_TEST_NAME, osv_tests)
{
    char buf1[9] = "12344321";
    MEMMOVE_LIKE_FUNC(&buf1[4], buf1, 4);
    cr_assert_eq(my_strncmp("12341234", buf1, 8), 0);

    char buf2[11] = "1234554321";
    MEMMOVE_LIKE_FUNC(&buf2[5], buf2, 5);
    cr_assert_eq(my_strncmp("1234512345", buf2, 10), 0);

    char buf3[9] = "12344321";
    MEMMOVE_LIKE_FUNC(buf3, &buf3[4], 4);
    cr_assert_eq(my_strncmp("43214321", buf3, 8), 0);

    char buf4[11] = "1234554321";
    MEMMOVE_LIKE_FUNC(buf4, &buf4[5], 5);
    cr_assert_eq(my_strncmp("5432154321", buf4, 10), 0);

    char buf5[9] = "12344321";
    MEMMOVE_LIKE_FUNC(buf5, &buf5[2], 4);
    cr_assert_eq(my_strncmp("34434321", buf5, 8), 0);

    char buf6[11] = "1234554321";
    MEMMOVE_LIKE_FUNC(&buf6[2], buf6, 5);
    cr_assert_eq(my_strncmp("1212345321", buf6, 10), 0);

    char buf7[17] = "1234567887654321";
    MEMMOVE_LIKE_FUNC(buf7, &buf7[2], 8);
    cr_assert_eq(my_strncmp("3456788787654321", buf7, 16), 0);

    char buf8[19] = "123456789987654321";
    MEMMOVE_LIKE_FUNC(&buf8[2], buf8, 9);
    cr_assert_eq(my_strncmp("121234567897654321", buf8, 18), 0);

    char loop_buf[18] = "1234567890000000";
    for (size_t i = 0; i < 8; ++i) {
        char buf_tmp[18];

        const char *loop_results[] = {
            "1234567812345678",
            "1234567823456789",
            "1234567834567890",
            "1234567845678900",
            "1234567856789000",
            "1234567867890000",
            "1234567878900000",
            "1234567889000000",
        };

        my_strncpy(buf_tmp, loop_buf, 18);
        MEMMOVE_LIKE_FUNC(&buf_tmp[8], &buf_tmp[i], 8);
        cr_assert_eq(my_strncmp(loop_results[i], buf_tmp, 16), 0);
    }

    char loop_buf2[18] = "0000000012345678";
    for (size_t i = 0; i < 8; ++i) {
        char buf_tmp[18];

        const char *loop_results[] = {
            "1234567812345678",
            "0123456782345678",
            "0012345678345678",
            "0001234567845678",
            "0000123456785678",
            "0000012345678678",
            "0000001234567878",
            "0000000123456788",
        };

        my_strncpy(buf_tmp, loop_buf2, 18);
        MEMMOVE_LIKE_FUNC(&buf_tmp[i], &buf_tmp[8], 8);
        cr_assert_eq(my_strncmp(loop_results[i], buf_tmp, 16), 0);
    }

    memmove_test(381, 0, 8);
    memmove_test(4, 0, 2303);
    memmove_test(40, 0, 2692);
    memmove_test(10, 0, 2732);
    memmove_test(424, 0, 2746);
    memmove_test(10, 0, 3618);
    memmove_test(415, 0, 3646);
    memmove_test(6, 0, 4057);
    memmove_test(6, 0, 4063);
    memmove_test(115, 0, 4075);
    memmove_test(4, 0, 4190);
    memmove_test(761, 0, 4202);
    memmove_test(587, 0, 5773);
    memmove_test(47, 0, 6356);
    memmove_test(6, 0, 403);
    memmove_test(10, 0, 6417);
    memmove_test(757, 0, 6600);
    memmove_test(703, 0, 8585);
    memmove_test(206, 0, 9284);
    memmove_test(720, 0, 9494);
    memmove_test(4, 0, 10210);
    memmove_test(597, 0, 11855);
    memmove_test(6, 0, 13520);
    memmove_test(4, 0, 13526);
    memmove_test(125, 0, 14572);

    memmove_test(10318, 10328, 127);
    memmove_test(10318, 10328, 138);

    for (int i = 0; i < 1000; i++) {
        size_t n;
        size_t destOffset = rand() % 0x4000;
        size_t srcOffset = rand() % 0x4000;
        // Calculate number of bytes so that source and dest overlap
        if (destOffset < srcOffset) {
            n = MY_MIN(srcOffset - destOffset + 128, 0x4000 - srcOffset);
            cr_assert(srcOffset + n <= 0x4000);
        } else {
            n = MY_MIN(destOffset - srcOffset + 128, 0x4000 - destOffset);
            cr_assert(destOffset + n <= 0x4000);
        }
        memmove_test(destOffset, srcOffset, n);
    }
}
