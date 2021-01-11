/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests memmem
*/

#include "../tests_header.h"
#include "my/string.h"
#include <string.h>
#include <signal.h>
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

static void do_one_test(const void *haystack, size_t haystack_length,
    const void *needle, size_t needle_length)
{
    cr_assert_eq(
        my_memmem(haystack, haystack_length, needle, needle_length),
        memmem(haystack, haystack_length, needle, needle_length));
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
    size_t pg = (size_t)getpagesize();
    char *src = (char *)mmap(NULL, pg * 2, PROT_READ|PROT_WRITE,
                     MAP_ANON|MAP_PRIVATE, -1, (off_t)0);
    cr_assert_neq(src, MAP_FAILED); 
    char *guard = (char *)mmap(src + pg, pg,
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

Test(my_memmem, gnulib)
{
    /* Declare failure if test takes too long, by using default abort
       caused by SIGALRM. Timeout might be too little, possible revise this in the future */
    signal(SIGALRM, SIG_DFL);
    alarm(10);

    do_one_test("foo", 3, "", 0);
    do_one_test("foo", 3, "o", 1);
    do_one_test("ABC ABCDAB ABCDABCDABDE", my_strlen("ABC ABCDAB ABCDABCDABDE"), "ABCDABD", 7);
    do_one_test("ABC ABCDAB ABCDABCDABDE", my_strlen("ABC ABCDAB ABCDABCDABDE"), "ABCDABE", 7);
    do_one_test("ABC ABCDAB ABCDABCDABDE", my_strlen("ABC ABCDAB ABCDABCDABDE"), "ABCDABCD", 8);
    {
        const char *input = "F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                         "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
            "_C3_A7_20_EF_BF_BD";
        const char *need = "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD";
        do_one_test(input, my_strlen(input), need, my_strlen(need));
    }
    {
        const char *input = "F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_A7_20_EF_BF_BD_DA_B5_C2_A6_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD";
        const char *need = "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD";
        do_one_test(input, my_strlen(input), need, my_strlen(need));
    }
    /* Check that length 0 does not dereference the pointer.  */
    void *page_boundary = zero_size_ptr();
    if (page_boundary) {
        do_one_test(page_boundary, 0, "foo", 3);

        const char input[] = "foo";
        do_one_test(input, my_strlen(input), page_boundary, 0);
    }

    /* Check that a very long haystack is handled quickly if the needle is
       short and occurs near the beginning.  */
    {
        size_t repeat = 10000;
        size_t m = 1000000;
        const char *needle =
            "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
            "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        size_t n = my_strlen(needle);
        char *haystack = (char *)malloc(m + 1);
        if (haystack != NULL) {
            my_memset(haystack, 'A', m);
            haystack[0] = 'B';

            for (; repeat > 0; repeat--)
                do_one_test(haystack, m, needle, n);
            free(haystack);
        }
    }

    /* Check that a very long needle is discarded quickly if the haystack is
       short.  */
    {
        size_t repeat = 10000;
        size_t m = 1000000;
        const char *haystack =
            "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
            "ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB";
        size_t n = my_strlen(haystack);
        char *needle = (char *)malloc(m + 1);
        if (needle != NULL) {
            my_memset(needle, 'A', m);
            for (; repeat > 0; repeat--)
                do_one_test(haystack, n, needle, m);
            free(needle);
        }
    }

    /* Check that the asymptotic worst-case complexity is not quadratic.  */
    {
        size_t m = 1000000;
        char *haystack = (char *)malloc(2 * m + 1);
        char *needle = (char *)malloc(m + 1);
        if (haystack != NULL && needle != NULL) {
            my_memset(haystack, 'A', 2 * m);
            haystack[2 * m] = 'B';

            my_memset(needle, 'A', m);
            needle[m] = 'B';

            do_one_test(haystack, 2 * m + 1, needle, m + 1);
        }
        free(needle);
        free(haystack);
    }

    /* Check that long needles not present in a haystack can be handled
       with sublinear speed.  */
    {
        size_t repeat = 10000;
        size_t m = 1000000;
        size_t n = 1000;
        char *haystack = (char *)malloc(m);
        char *needle = (char *)malloc(n);
        if (haystack != NULL && needle != NULL) {
            my_memset(haystack, 'A', m);
            my_memset(needle, 'B', n);
            for (; repeat > 0; repeat--)
                do_one_test(haystack, m, needle, n);
        }
        free(haystack);
        free(needle);
    }

    {
        const char *haystack = "..wi.d.";
        const char *needle = ".d.";
        do_one_test(haystack, my_strlen(haystack), needle, my_strlen(needle));
    }

    {
        /* Like the above, but trigger the flaw in two_way_long_needle
           by using a needle of length LONG_NEEDLE_THRESHOLD (32) or greater.
           Rather than trying to find the right alignment manually, I've
           arbitrarily chosen the following needle and template for the
           haystack, and ensure that for each placement of the needle in
           that haystack, memmem finds it.  */
        const char *needle = "\nwith_gnu_ld-extend-to-len-32-b\n";
        const char *h =
            "\n"
            "with_build_libsubdir\n"
            "with_local_prefix\n"
            "with_gxx_include_dir\n"
            "with_cpp_install_dir\n"
            "with_e_\n"
            "..............................\n"
            "with_FGHIJKLMNOPQRSTUVWXYZ\n"
            "with_567890123456789\n"
            "with_multilib_list\n";
        size_t h_len = my_strlen(h);
        char *haystack = (char *)malloc(h_len + 1);
        size_t i;
        cr_assert(haystack);
        for (i = 0; i < h_len - my_strlen(needle); i++) {
            my_memcpy(haystack, h, h_len + 1);
            my_memcpy(haystack + i, needle, my_strlen(needle) + 1);
            do_one_test(haystack, my_strlen(haystack), needle, my_strlen(needle));
        }
        free(haystack);
    }

    /* Test long needles.  */
    {
        size_t m = 1024;
        char *haystack = (char *)malloc(2 * m + 1);
        char *needle = (char *)malloc(m + 1);
        if (haystack != NULL && needle != NULL) {
            haystack[0] = 'x';
            my_memset(haystack + 1, ' ', m - 1);
            my_memset(haystack + m, 'x', m);
            haystack[2 * m] = '\0';
            my_memset(needle, 'x', m);
            needle[m] = '\0';
            do_one_test(haystack, my_strlen(haystack), needle, my_strlen(needle));
        }
        free(needle);
        free(haystack);
    }
}
