/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memcmp
*/

#include "../tests_header.h"
#include "my/string.h"
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>

static void *zero_size_ptr(void)
{
    size_t page_size = (size_t)getpagesize();
    char *two_pages = (char *)mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (two_pages != (char *)(-1) && mprotect(two_pages + page_size, page_size, PROT_NONE) == 0)
        return two_pages + page_size;
    return NULL;
}

Test(my_memcmp, very_simple)
{
    cr_assert_eq(my_memcmp("a", "b", 0), 0);
    cr_assert_eq(my_memcmp("", "", 0), 0);
}

Test(my_memcmp, basic_fuzz)
{
    unsigned char data1[256], data2[256];

    for (size_t i = 0; i < 256; ++i)
        data1[i] = data2[i] = (unsigned char)(i ^ 0x55);
    for (size_t i = 1; i < 256; ++i)
        cr_assert_eq(my_memcmp(data1, data2, i), 0);
    for (size_t i = 1; i < 256; ++i)
        cr_assert_eq(my_memcmp(data1 + i, data2 + i, 256 - i), 0);
}

Test(my_memcmp, more_fuzz)
{
    unsigned char data1[256], data2[256];

    for (size_t i = 0; i < 256; ++i) {
        data1[i] = (unsigned char)i;
        data2[i] = (unsigned char)(i ^ 0x55);
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

static void test_one_linux_kernel_selftests(char *s1, char *s2, size_t max_offset, size_t size_start, size_t max_size)
{
    for (size_t offset = 0; offset < max_offset; ++offset)
        for (size_t size = size_start; size < (max_size - offset); ++size) {
            int good_result = memcmp(s1 + offset, s2 + offset, size);
            int our_result = my_memcmp(s1 + offset, s2 + offset, size);
            cr_assert((our_result < 0 && good_result < 0) || (our_result == good_result) || (our_result > 0 && good_result > 0));
        }
}

static void do_linux_kernel_selftests(bool is_large)
{
    static const size_t SIZE = 256;
    static const size_t ITERATIONS = 250;
    static const size_t LARGE_SIZE = 5 * 1024;
    static const size_t LARGE_ITERATIONS = 50;
    static const size_t LARGE_MAX_OFFSET = 32;
    static const size_t LARGE_SIZE_START = 4096;
    static const size_t MAP_SIZE = 64 * 1024;
    static const size_t MAX_OFFSET_DIFF_S1_S2 = 48;
    size_t comp_size = (is_large) ? LARGE_SIZE : SIZE;
    size_t alloc_size = comp_size + MAX_OFFSET_DIFF_S1_S2;
    size_t iterations = is_large ? LARGE_ITERATIONS : ITERATIONS;
    char *p = (char *)mmap(NULL, 4 * MAP_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    cr_assert_neq(p, MAP_FAILED);

    // s1/s2 are at the end of a page
    char *s1 = p + MAP_SIZE - alloc_size;
    char *s2 = p + 3 * MAP_SIZE - alloc_size;

    // Unmap the pages right after them to force a fault if we overread
    munmap(p + MAP_SIZE, MAP_SIZE);
    munmap(p + 3 * MAP_SIZE, MAP_SIZE);

    srandom((unsigned)time(NULL));

    for (size_t i = 0; i < iterations; ++i) {
        for (size_t j = 0; j < alloc_size; ++j)
            s1[j] = (char)random();
        char *rand_s1 = s1 + ((size_t)random() % MAX_OFFSET_DIFF_S1_S2);
        char *rand_s2 = s2 + ((size_t)random() % MAX_OFFSET_DIFF_S1_S2);
        my_memcpy(rand_s2, rand_s1, comp_size);

        size_t changed_byte = (size_t)random() % comp_size;
        rand_s2[changed_byte] = (char)(random() & 0xFF);

        if (is_large)
            test_one_linux_kernel_selftests(rand_s1, rand_s2, LARGE_MAX_OFFSET, LARGE_SIZE_START, comp_size);
        else
            test_one_linux_kernel_selftests(rand_s1, rand_s2, SIZE, 0, comp_size);
    }

    srandom((unsigned)time(NULL));

    for (size_t i = 0; i < iterations; ++i) {
        for (size_t j = 0; j < alloc_size; ++j)
            s1[j] = (char)random();
        char *rand_s1 = s1 + ((size_t)random() % MAX_OFFSET_DIFF_S1_S2);
        char *rand_s2 = s2 + ((size_t)random() % MAX_OFFSET_DIFF_S1_S2);
        my_memcpy(rand_s2, rand_s1, comp_size);

        // Change 1/8th of the bytes, randomly
        for (size_t j = 0; j < (comp_size / 8); ++j) {
            size_t changed_byte = (size_t)random() % comp_size;
            rand_s2[changed_byte] = (char)(random() & 0xFF);
        }

        if (is_large)
            test_one_linux_kernel_selftests(rand_s1, rand_s2, LARGE_MAX_OFFSET, LARGE_SIZE_START, comp_size);
        else
            test_one_linux_kernel_selftests(rand_s1, rand_s2, SIZE, 0, comp_size);
    }
}

Test(my_memcmp, pretty_through)
{
    do_linux_kernel_selftests(false);
    do_linux_kernel_selftests(true);
}

Test(my_memcmp, specific_fails)
{
    __attribute__((aligned(0x100))) char buffer1[0x100];
    my_strcpy(buffer1 + 0x81, "\325\230\370_\022c\256\066\250\212\321\363\364\071\320g\202\261\204eK\257\024\326\rf\212\340\266\022ꋫ\343\353\275F\231\363\356#\305\342\030\376\262\177\200c\003宲\372\205\277`\017\237\027!\212\242");
    __attribute__((aligned(0x100))) char buffer2[0x100];
    my_strcpy(buffer2 + 0xA2, "\325\230\370_\022c\256\066\250\212\321\363\364\071\320g\202\261\204eK\257\024\326\rf\212\340\266\022\352\213\345\343\353\275F\231\363\356#\305\342\030\376\262\177\200c\003宲\372\205\277`\017\237\027!\212\242");

    cr_assert_lt(my_memcmp(buffer1 + 0x81, buffer2 + 0xA2, 63), 0);
}

Test(my_memcmp, gnulib)
{
    char foo[21];
    char bar[21];
    for (size_t i = 0; i < 4; ++i) {
        char *a = foo + i;
        char *b = bar + i;
        my_strcpy(a, "--------01111111");
        my_strcpy(b, "--------10000000");
        cr_assert_lt(my_memcmp(a, b, 0x10), 0);
    }

    char *page_boundary1 = (char *)zero_size_ptr(), *page_boundary2 = (char *)zero_size_ptr();
    if (page_boundary1 && page_boundary2)
        cr_assert_eq(my_memcmp(page_boundary1, page_boundary2, 0), 0);

    cr_assert(my_memcmp("foo", "foobar", 2) == 0);
    cr_assert(my_memcmp("foo", "foobar", 3) == 0);
    cr_assert(my_memcmp("foo", "foobar", 4) != 0);
    cr_assert(my_memcmp("foo", "bar", 1) != 0);
    cr_assert(my_memcmp("foo", "bar", 3) != 0);
    cr_assert(my_memcmp("foo", "moo", 4) < 0);
    cr_assert(my_memcmp("moo", "foo", 4) > 0);
    cr_assert(my_memcmp("oomph", "oops", 3) < 0);
    cr_assert(my_memcmp("oops", "oomph", 3) > 0);
    cr_assert(my_memcmp("foo", "foobar", 4) < 0);
    cr_assert(my_memcmp("foobar", "foo", 4) > 0);
    cr_assert(my_memcmp("\100", "\201", 1) < 0);
    cr_assert(my_memcmp("\201", "\100", 1) > 0);
    cr_assert(my_memcmp("\200", "\201", 1) < 0);
    cr_assert(my_memcmp("\201", "\200", 1) > 0);
}
