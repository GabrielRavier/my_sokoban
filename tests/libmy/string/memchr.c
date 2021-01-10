/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memchr
*/

#include "../tests_header.h"
#include "my/string.h"
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

static void *zero_size_ptr(void)
{
    size_t page_size = (size_t)getpagesize();
    char *two_pages = (char *)mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (two_pages != (char *)(-1) && mprotect(two_pages + page_size, page_size, PROT_NONE) == 0)
        return two_pages + page_size;
    return NULL;
}

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
    cr_assert(input);
    if (!input)
        abort();

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
        size_t limit = 257;

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
