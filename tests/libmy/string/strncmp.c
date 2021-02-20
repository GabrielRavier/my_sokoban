/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines strncmp
*/

#include "my/string.h"
#include "glibc.h"
#include "../tests_header.h"
#include "my/cpp-like/algorithm.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <limits.h>

static int sign(int x)
{
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}

static void do_one_test(const char *s1, const char *s2, size_t n)
{
    cr_assert_eq(sign(my_strncmp(s1, s2, n)), sign(strncmp(s1, s2, n)));
    cr_assert_eq(sign(my_strncmp(s2, s1, n)), sign(strncmp(s2, s1, n)));
}

Test(my_strncmp, gnulib_standard)
{
    do_one_test("", "", 0);
    do_one_test("", "", 1);
    do_one_test("", "", 1000000);

    do_one_test("", "foo", 0);
    do_one_test("", "foo", 1);
    do_one_test("", "foo", 2);
    do_one_test("", "foo", 3);
    do_one_test("", "foo", 4);
    do_one_test("", "foo", 5);
    do_one_test("", "foo", 1000000);

    do_one_test("foo", "foo", 0);
    do_one_test("foo", "foo", 1);
    do_one_test("foo", "foo", 2);
    do_one_test("foo", "foo", 3);
    do_one_test("foo", "foo", 4);
    do_one_test("foo", "foo", 5);
    do_one_test("foo", "foo", 1000000);

    do_one_test("foo", "bar", 0);
    do_one_test("foo", "bar", 1);
    do_one_test("foo", "bar", 2);
    do_one_test("foo", "bar", 3);
    do_one_test("foo", "bar", 4);
    do_one_test("foo", "bar", 5);
    do_one_test("foo", "bar", 1000000);

    do_one_test("foo", "foobar", 0);
    do_one_test("foo", "foobar", 1);
    do_one_test("foo", "foobar", 2);
    do_one_test("foo", "foobar", 3);
    do_one_test("foo", "foobar", 4);
    do_one_test("foo", "foobar", 5);
    do_one_test("foo", "foobar", 6);
    do_one_test("foo", "foobar", 7);
    do_one_test("foo", "foobar", 8);
    do_one_test("foo", "foobar", 1000000);

    do_one_test("oomph", "oops", 0);
    do_one_test("oomph", "oops", 1);
    do_one_test("oomph", "oops", 2);
    do_one_test("oomph", "oops", 3);
    do_one_test("oomph", "oops", 4);
    do_one_test("oomph", "oops", 5);
    do_one_test("oomph", "oops", 6);
    do_one_test("oomph", "oops", 1000000);
}

Test(my_strncmp, gnulib_u8)
{
    const char *input1 = "\xF0\x9D\x94\x9E";
    const char *input2 = "\xEF\xBB\xBF";

    do_one_test(input1, input2, 1);
    do_one_test(input1, input2, 2);
    do_one_test(input1, input2, 3);
    do_one_test(input1, input2, 4);
    do_one_test(input1, input2, 5);
    do_one_test(input1, input2, 6);
}

static void do_glibc_test(size_t align1, size_t align2, size_t len, size_t n, int max_char, int exp_result)
{
    if (n == 0)
        return;

    align1 &= 0x3F;
    if (align1 + (n + 1) >= glibc_page_size)
        return;

    align2 &= 0x3F;
    if (align2 + (n + 1) >= glibc_page_size)
        return;

    char *s1 = glibc_buf1 + align1;
    char *s2 = glibc_buf2 + align1;
    for (size_t i = 0; i < n; ++i)
        s1[i] = s2[i] = 1 + (23 << 8) * i % max_char;

    s1[n] = 24 + exp_result;
    s2[n] = 23;
    s1[len] = 0;
    s2[len] = 0;
    if (exp_result < 0)
        s2[len] = 32;
    else if (exp_result > 0)
        s1[len] = 64;
    if (len >= n)
        s2[n - 1] -= exp_result;
    do_one_test(s1, s2, n);
}

static void do_glibc_page_test(size_t offset1, size_t offset2, char *s2)
{
    if (offset1 >= glibc_page_size || offset2 >= glibc_page_size)
        return;
    do_one_test(glibc_buf1 + offset1, s2 + offset2, glibc_page_size);
}

static void do_glibc_test_limit(size_t align1, size_t align2, size_t len, size_t n, int max_char, int exp_result)
{
    char *s1, *s2;

    if (n == 0) {
        s1 = glibc_buf1 + glibc_page_size;
        s2 = glibc_buf2 + glibc_page_size;
        do_one_test(s1, s2, n);
        return;
    }

    align1 &= 0xF;
    align2 &= 0xF;
    size_t align_n = (glibc_page_size - n) & 0xF;

    s1 = glibc_buf1 + glibc_page_size - n;
    s2 = glibc_buf2 + glibc_page_size - n;

    if (align1 < align_n)
        s1 = s1 - (align_n - align1);
    if (align2 < align_n)
        s2 = s2 - (align_n - align2);

    for (size_t i = 0; i < n; ++i)
        s1[i] = s2[i] = i + 23 * i % max_char;

    if (len < n) {
        s1[len] = 0;
        s2[len] = 0;
        if (exp_result < 0)
            s2[len] = 32;
        else if (exp_result > 0)
            s1[len] = 64;
    }
    do_one_test(s1, s2, n);
}

Test(my_strncmp, glibc)
{
    glibc_test_string_init();

    // Specific bugs from glibc testcases
    char *s1 = glibc_buf1 + 0xB2C;
    char *s2 = glibc_buf2 + 0xFD8;

    my_strcpy(s1, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs");
    my_strcpy(s2, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV");

    // Check possible overflow bug
    s1[4] = CHAR_MAX;
    s2[4] = CHAR_MIN;

    for (size_t offset = 0; offset < 6; ++offset)
        for (size_t i = 0; i < 80; ++i)
            do_one_test(s1 + offset, s2 + offset, i);

    s1 = glibc_buf1;
    size_t i = 0;
    while (i < glibc_page_size - 1)
        s1[i++] = 23;
    s1[i] = 0;

    s2 = my_strdup(s1);
    for (size_t i = 0; i < 64; ++i)
        do_glibc_page_test(3988 + i, 2636, s2);
    free(s2);

    /* To trigger glibc bug 25933, we need a size that is equal to the vector
       length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
       make this test generic and run it for all architectures as additional
       boundary testing for such related algorithms.  */
    static const size_t size = 32 * 4;

    my_memset(glibc_buf1, 'a', glibc_page_size);
    my_memset(glibc_buf2, 'a', glibc_page_size);
    glibc_buf1[glibc_page_size - 1] = '\0';

    /* Iterate over a size that is just below where we expect the bug to
       trigger up to the size we expect will trigger the bug e.g. [99-128].
       Likewise iterate the start of two strings between 30 and 31 bytes
       away from the boundary to simulate alignment changes.  */
    for (size_t s = 99; s < size; ++s)
        for (size_t s1a = 30; s1a < 32; ++s1a)
            for (size_t s2a = 30; s2a < 32; ++s2a)
                do_one_test(glibc_buf1 + glibc_page_size - s - s1a,
                            glibc_buf2 + glibc_page_size - s - s2a, s);

    // Non-specific testcases
    for (size_t i = 0; i < 16; ++i) {
        do_glibc_test(0, 0, 8, i, 127, 0);
        do_glibc_test(0, 0, 8, i, 127, -1);
        do_glibc_test(0, 0, 8, i, 127, 1);
        do_glibc_test(i, i, 8, i, 127, 0);
        do_glibc_test(i, i, 8, i, 127, 1);
        do_glibc_test(i, i, 8, i, 127, -1);
        do_glibc_test(i, 2 * i, 8, i, 127, 0);
        do_glibc_test(2 * i, i, 8, i, 127, 1);
        do_glibc_test(i, 3 * i, 8, i, 127, -1);
        do_glibc_test(0, 0, 8, i, 255, 0);
        do_glibc_test(0, 0, 8, i, 255, 1);
        do_glibc_test(0, 0, 8, i, 255, -1);
        do_glibc_test(i, i, 8, i, 255, 0);
        do_glibc_test(i, i, 8, i, 255, 1);
        do_glibc_test(i, i, 8, i, 255, -1);
        do_glibc_test(i, 2 * i, 8, i, 255, 0);
        do_glibc_test(2 * i, i, 8, i, 255, 1);
        do_glibc_test(i, 3 * i, 8, i, 255, -1);
    }

    for (size_t i = 1; i < 8; ++i) {
        do_glibc_test(0, 0, 8 << i, 16 << i, 127, 0);
        do_glibc_test(0, 0, 8 << i, 16 << i, 127, 1);
        do_glibc_test(0, 0, 8 << i, 16 << i, 127, -1);
        do_glibc_test(0, 0, 8 << i, 16 << i, 255, 0);
        do_glibc_test(0, 0, 8 << i, 16 << i, 255, 1);
        do_glibc_test(0, 0, 8 << i, 16 << i, 255, -1);
        do_glibc_test(8 - i, 2 * i, 8 << i, 16 << i, 127, 0);
        do_glibc_test(8 - i, 2 * i, 8 << i, 16 << i, 127, 1);
        do_glibc_test(2 * i, i, 8 << i, 16 << i, 255, 0);
        do_glibc_test(2 * i, i, 8 << i, 16 << i, 255, 1);
    }

    do_glibc_test_limit(0, 0, 0, 0, 127, 0);
    do_glibc_test_limit(4, 0, 21, 20, 127, 0);
    do_glibc_test_limit(0, 4, 21, 20, 127, 0);
    do_glibc_test_limit(8, 0, 21, 20, 127, 0);
    do_glibc_test_limit(0, 8, 21, 20, 127, 0);

    for (size_t i = 0; i < 8; ++i) {
        do_glibc_test_limit(0, 0, 17 - i, 16 - i, 127, 0);
        do_glibc_test_limit(0, 0, 17 - i, 16 - i, 255, 0);
        do_glibc_test_limit(0, 0, 15 - i, 16 - i, 127, 0);
        do_glibc_test_limit(0, 0, 15 - i, 16 - i, 127, 1);
        do_glibc_test_limit(0, 0, 15 - i, 16 - i, 127, -1);
        do_glibc_test_limit(0, 0, 15 - i, 16 - i, 255, 0);
        do_glibc_test_limit(0, 0, 15 - i, 16 - i, 255, 1);
        do_glibc_test_limit(0, 0, 15 - i, 16 - i, 255, -1);
    }

    // Random tests
    unsigned char *p1 = (unsigned char *)(glibc_buf1 + glibc_page_size - 512);
    unsigned char *p2 = (unsigned char *)(glibc_buf1 + glibc_page_size - 512);
    for (size_t i = 0; i < 50000; ++i) {
        size_t align1 = random() & 0x1F;
        size_t align2;
        if (random() & 1)
            align2 = random() & 0x1F;
        else
            align2 = align1 + (random() & 24);
        size_t pos = random() & 0x1FF;
        size_t size = random() & 0x1FF;
        size_t j = MY_MAX(align1, align2);
        if (pos + j > 0x1FF)
            pos = 0x1FE - j - (random() & 7);
        size_t len1 = random() & 0x1FF;
        if (pos >= len1 && (random() & 1))
            len1 = pos + (random() & 7);
        if (len1 + j >= 0x200)
            len1 = 0x1FF - j - (random() & 7);
        size_t len2 = (pos >= len1) ? len1 : (len1 + (len1 == 511 - j ? 0 : random() % (511 - j - len1)));
        j = MY_MIN(MY_MAX(pos, len2) + align1 + 0x40, 0x200);
        for (size_t i = 0; i < j; ++i) {
            p1[i] = random() & 0xFF;
            if (i < len1 + align1 && p1[i] == '\0')
                p1[i] = 1 + random() % 0xFE;
        }
        for (size_t i = 0; i < j; ++i) {
            p2[i] = random() & 0xFF;
            if (i < len2 + align2 && p2[i] == '\0')
                p2[i] = 1 + random() % 0xFE;
        }
        my_memcpy(p2 + align2, p1 + align1, pos);
        if (pos < len1) {
            if (p2[align2 + pos] == p1[align1 + pos]) {
                p2[align2 + pos] = random() & 0xFF;
                if (p2[align2 + pos] == p1[align1 + pos])
                    p2[align2 + pos] = p1[align1 + pos] + 3 + (random() & 0x7F);
            }
        }
        p1[len1 + align1] = '\0';
        p2[len2 + align2] = '\0';

        do_one_test((const char *)(p1 + align1), (const char *)(p2 + align2), size);
    }
}

Test(my_strncmp, specific_fails)
{
    do_one_test("abcd\177fghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs", "abcd\200fghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV", 5);
}
