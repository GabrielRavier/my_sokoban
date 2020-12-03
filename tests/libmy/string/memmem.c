/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memmem
*/

#include "my/string.h"
#include <criterion/criterion.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

static void do_one_test(const void *haystack, size_t haystack_length, const void *needle, size_t needle_length)
{
    cr_assert_eq(my_memmem(haystack, haystack_length, needle, needle_length), memmem(haystack, haystack_length, needle, needle_length));
}

Test(my_memmem, netbsd_basic)
{
    do_one_test("0123456789", 10, "", 0);
    do_one_test("", 0, "", 0);
    do_one_test("", 0, "0123", 4);
    do_one_test("0", 1, "0123", 4);
    do_one_test("0123456789", 10, "0123", 4);
    do_one_test("0123456789", 10, "456", 3);
    do_one_test("0123456789", 10, "789", 3);
    do_one_test("0123456789", 10, "0", 1);
    do_one_test("0123456789", 10, "9", 1);
    do_one_test("0123456789", 10, "abc", 3);
    do_one_test("0123456789", 10, "654", 3);
    do_one_test("0123456789", 10, "89abc", 5);
}

Test(my_memmem, netbsd_oob)
{
    static const char str[] = "abcde";
    size_t pg = getpagesize();
    char *src = mmap(NULL, pg * 2, PROT_READ|PROT_WRITE,
                     MAP_ANON|MAP_PRIVATE, -1, (off_t)0);
    cr_assert_neq(src, MAP_FAILED); 
    char *guard = mmap(src + pg, pg,
                       PROT_NONE, MAP_ANON|MAP_PRIVATE|MAP_FIXED, -1, (off_t)0);
    for (size_t i = 2; i < 5; i++) {
        char *search = src + pg - i;
        char match[sizeof(str)];
        search[-1] = str[0];
        search[0] = str[0];
        search[1] = str[0];
        memcpy(match, str, i);
        cr_assert_neq(memmem(search, i, match, i), search);
    }
    munmap(guard, pg);
    munmap(src, pg);
}
