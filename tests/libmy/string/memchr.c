/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests memchr
*/

#include "../tests_header.h"
#include "zero_size_ptr.h"
#include "bionic_test_state.h"
#include "../bionic_buffer.h"
#include "my/string.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

static void do_one_test(const void *s, int c, size_t n)
{
    cr_assert_eq(my_memchr(s, c, n), memchr(s, c, n));
}

static void do_one_test_slash(const void *s, size_t n)
{
    do_one_test(s, '/', n);
    do_one_test(s, (int)(0xFFFFFF00 | '/'), n);
}

Test(my_memchr, netbsd_basic)
{
    do_one_test_slash("", 0);
    do_one_test_slash("/", 0);
    do_one_test_slash("/", 1);
    do_one_test_slash("/a", 2);
    do_one_test_slash("/ab", 3);
    do_one_test_slash("/abc", 4);
    do_one_test_slash("/abcd", 5);
    do_one_test_slash("/abcde", 6);
    do_one_test_slash("/abcdef", 7);
    do_one_test_slash("/abcdefg", 8);
    do_one_test_slash("a/", 1);
    do_one_test_slash("a/", 2);
    do_one_test_slash("a/b", 3);
    do_one_test_slash("a/bc", 4);
    do_one_test_slash("a/bcd", 5);
    do_one_test_slash("a/bcde", 6);
    do_one_test_slash("a/bcdef", 7);
    do_one_test_slash("a/bcdefg", 8);

    do_one_test_slash("ab/", 2);
    do_one_test_slash("ab/", 3);
    do_one_test_slash("ab/c", 4);
    do_one_test_slash("ab/cd", 5);
    do_one_test_slash("ab/cde", 6);
    do_one_test_slash("ab/cdef", 7);
    do_one_test_slash("ab/cdefg", 8);

    do_one_test_slash("abc/", 3);
    do_one_test_slash("abc/", 4);
    do_one_test_slash("abc/d", 5);
    do_one_test_slash("abc/de", 6);
    do_one_test_slash("abc/def", 7);
    do_one_test_slash("abc/defg", 8);

    do_one_test_slash("abcd/", 4);
    do_one_test_slash("abcd/", 5);
    do_one_test_slash("abcd/e", 6);
    do_one_test_slash("abcd/ef", 7);
    do_one_test_slash("abcd/efg", 8);

    do_one_test_slash("abcde/", 5);
    do_one_test_slash("abcde/", 6);
    do_one_test_slash("abcde/f", 7);
    do_one_test_slash("abcde/fg", 8);

    do_one_test_slash("abcdef/", 6);
    do_one_test_slash("abcdef/", 7);
    do_one_test_slash("abcdef/g", 8);

    do_one_test_slash("abcdefg/", 7);
    do_one_test_slash("abcdefg/", 8);
    do_one_test_slash("\xff\xff\xff\xff" "efg/", 8);
    do_one_test_slash("a" "\xff\xff\xff\xff" "fg/", 8);
    do_one_test_slash("ab" "\xff\xff\xff\xff" "g/", 8);
    do_one_test_slash("abc" "\xff\xff\xff\xff" "/", 8);
}

Test(my_memchr, netsbd_simple)
{
    char buf[] = "abcdefg";

    do_one_test(buf, 'a', 0);
    do_one_test(buf, 'g', 0);
    do_one_test(buf, 'x', 7);
    do_one_test("", 'x', 0);
    do_one_test("", 'x', 1);

    for (size_t i = 0; i < 2000; ++i) {
        do_one_test(buf, 'a', i);
        do_one_test(buf, 'b', i);
        do_one_test(buf, 'c', i);
        do_one_test(buf, 'd', i);
        do_one_test(buf, 'e', i);
        do_one_test(buf, 'f', i);
        do_one_test(buf, 'g', i);
    }
}

Test(my_memchr, gnulib)
{
    size_t n = 0x100000;
    char *input = (char *)malloc(n);
    cr_assert(input != NULL);

    input[0] = 'a';
    input[1] = 'b';
    my_memset(input + 2, 'c', 1024);
    my_memset(input + 1026, 'd', n - 1028);
    input[n - 2] = 'e';
    input[n - 1] = 'a';

    /* Basic behavior tests.  */
    do_one_test(input, 'a', n);
    do_one_test(input, 'a', 0);

    {
        void *page_boundary = zero_size_ptr();
        if (page_boundary)
            do_one_test(page_boundary, 'a', 0);
    }

    do_one_test(input, 'b', n);
    do_one_test(input, 'c', n);
    do_one_test(input, 'd', n);
    do_one_test(input, 'a', n);
    do_one_test(input, 'e', n);
    do_one_test(input, 'f', n);
    do_one_test(input, '\0', n);
    do_one_test(input + 1, 'b', n - 1);
    do_one_test(input + 1, 'c', n - 1);
    do_one_test(input + 1, 'd', n - 1);
    do_one_test(input + 1, 'a', n - 1);
    do_one_test(input + 1, 'e', n - 1);
    do_one_test(input + 1, 0x789ABC00 | 'e', n - 1);

    /* Check that a very long haystack is handled quickly if the byte is
       found near the beginning.  */
    {
        size_t repeat = 10000;
        for (; repeat > 0; repeat--)
            do_one_test(input, 'c', n);
    }

    /* Alignment tests.  */
    for (size_t i = 0; i < 32; i++) {
        for (size_t j = 0; j < 256; j++)
            input[i + j] = (char)j;
        for (int j = 0; j < 256; j++)
            do_one_test(input + i, j, 256);
    }

    /* Check that memchr() does not read past the first occurrence of the
       byte being searched.  See the Austin Group's clarification
       <https://www.opengroup.org/austin/docs/austin_454.txt>.
       Test both '\0' and something else, since some implementations
       special-case searching for NUL.
    */
    {
        char *page_boundary = (char *)zero_size_ptr();
        /* Too small, and we miss cache line boundary tests; too large,
           and the test takes cubically longer to complete.  */
        size_t limit = 150;

        if (page_boundary != NULL) {
            for (size_t i = 1; i <= limit; i++) {
                char *mem = page_boundary - i;
                my_memset(mem, 'X', i);
                do_one_test(mem, 'U', i);
                do_one_test(mem, 0, i);
                for (size_t j = 0; j < i; j++) {
                    mem[j] = 'U';
                    for (size_t k = j + 1; k < i + limit; k++)
                        do_one_test(mem, 'U', k);
                    mem[j] = 0;
                    for (size_t k = j + 1; k < i + limit; k++)
                        do_one_test(mem, 0, k);
                    mem[j] = 'X';
                }
            }
        }
    }
    free(input);
}

Test(my_memchr, avr_libc)
{
    /* Not found        */
    do_one_test("", 0, 0);
    do_one_test("", 255, 0);
    do_one_test("ABCDEF", 'a', 6);

    /* Found    */
    do_one_test("\000", 0, 1);
    do_one_test("\001", 1, 1);
    do_one_test("\377", 255, 1);
    do_one_test("987654321", '7', 9);

    /* '\0' has't a special sense       */
    do_one_test("12345", 0, 6);
    do_one_test(".\000.", 0, 3);
    do_one_test("\000a\000b", 'b', 4);

    /* First occurance  */
    do_one_test("abcdabcd", 'b', 8);
    do_one_test("........", '.', 8);

    /* 'c' converted to a char  */
    do_one_test("ABCDEF", 'A' + 0x100, 6);
    do_one_test("ABCDE\377", ~0, 6);

    /* Very long string */
    do_one_test("................................................................"
           "................................................................"
           "................................................................"
           "................................................................"
           "*...............................................................",
           '*', 320);
}

Test(my_memchr, cloudlibc_match)
{
    char buf[] = "Foo bar baz";
    do_one_test(buf, 'a', sizeof(buf));
}

Test(my_memchr, cloudlibc_nomatch)
{
    char buf[] = "Foo bar baz";
    do_one_test(buf, 'x', sizeof(buf));
}

Test(my_memchr, dietlibc)
{
    const char *test = "blubber";
    do_one_test("aaaa", 'x', 4);
    do_one_test(test, 'u', 2);
    do_one_test(test, 'u', 7);
    do_one_test(test, 'b', 7);
    do_one_test(test + 6, 'r', 1);
    do_one_test(test + 7, 0, 100);
}

Test(my_memchr, escape)
{
    do_one_test("abc", 'a', 3);
    do_one_test("abc", 'b', 3);
    do_one_test("abc", 'c', 3);
    do_one_test("abc", 'd', 3);
    do_one_test("def123456", 'd', 1);
    do_one_test("def123456", 'e', 1);
}

Test(my_memchr, bionic)
{
    int seek_char = 'N';
    __auto_type state = bionic_test_state_new(1024);

    for (size_t i = 0; i < state.n; ++i) {
        for (bionic_test_state_begin_iters(&state) ;
             bionic_test_state_has_next_iter(&state);
             bionic_test_state_next_iter(&state)) {
            my_memset(state.ptr1, ~seek_char, state.lengths[i]);
            size_t position = random() % state.max_length;
            if (position < state.lengths[i])
                state.ptr1[position] = seek_char;
            do_one_test(state.ptr1, seek_char, state.lengths[i]);
        }
    }
    bionic_test_state_destroy(&state);
}

Test(my_memchr, bionic_zero)
{
    void *buffer;
    cr_assert_eq(posix_memalign(&buffer, 64, 64), 0);
    my_memset(buffer, 10, 64);
    do_one_test(buffer, 5, 0);
    do_one_test(buffer, 10, 0);
    free(buffer);
}

static void bionic_do_buffer_test(uint8_t *buffer, size_t length)
{
    if (length >= 1) {
        int value = length % 128;
        int search_value = value + 1;
        
        my_memset(buffer, value, length);
        do_one_test(buffer, search_value, length);

        if (length >= 2) {
            buffer[0] = search_value;
            do_one_test(buffer, search_value, length);

            buffer[0] = value;
            buffer[length - 1] = search_value;
            do_one_test(buffer, search_value, length);
        }
    }
}

Test(my_memchr, bionic_align)
{
    bionic_run_single_buffer_align_test(4096, bionic_do_buffer_test);
}

Test(my_memchr, bionic_overread)
{
    bionic_run_single_buffer_overread_test(bionic_do_buffer_test);
}

Test(my_memchr, defora)
{
    const char *search = "sear\xff\xfe\x7f\x7e\x00\x01ch";

    for (size_t i = 0; i < sizeof(search); ++i)
        cr_assert_eq(my_memchr(search, search[i], sizeof(search)), &search[i]);
    cr_assert_eq(my_memchr(search, 'z', sizeof(search)), NULL);
}

Test(my_memchr, plauger)
{
    const char *abcde = "abcde";

    cr_assert_eq(my_memchr(abcde, 'c', 5), &abcde[2]);
    cr_assert_eq(my_memchr(abcde, 'e', 4), NULL);
}

Test(my_memchr, newlib)
{
    cr_assert_eq(my_memchr("A", 'A', 0), NULL);

    const char *target = "X";
    cr_assert_eq(my_memchr(target, 'X', 2), target);
    cr_assert_eq(my_memchr(target, 'Y', 2), NULL);

    target = "YY";
    cr_assert_eq(my_memchr(target, 'Y', 2), target);

    target = "WW";
    cr_assert_eq(my_memchr(target, 'W', 2), target);

    target = "ZZK";
    cr_assert_eq(my_memchr(target, 'K', 3), target + 2);
    cr_assert_eq(my_memchr(target, 'K', 4), target + 2);
}

Test(my_memchr, wine_ntdll)
{
    const char *string = "ab";

    cr_assert_eq(my_memchr(string, 'z', 2), NULL);
    cr_assert_eq(my_memchr(string, 'a', 2), string);
    cr_assert_eq(my_memchr(string, 0x100 + 'a', 2), string);
    cr_assert_eq(my_memchr(string, -0x100 + 'a', 2), string);
}
