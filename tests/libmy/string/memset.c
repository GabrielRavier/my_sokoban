/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests memset
*/

#include "../tests_header.h"
#include "littlekernel_fill_buffer.h"
#define GLIBC_MIN_PAGE_SIZE 131072
#include "glibc.h"
#include "bionic_test_state.h"
#include "escape_check_zero.h"
#include "../bionic_buffer.h"
#include "my/cpp-like/algorithm.h"
#include "my/string.h"
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

static void netbsd_check(const char *buffer, size_t length, char character)
{
    for (size_t i = 0; i < length; ++i)
        cr_assert_eq(buffer[i], character);
}

static void checked_my_memset(void *destination, int character, size_t length)
{
    cr_assert_eq(my_memset(destination, character, length), destination);
}

Test(my_memset, netbsd_array)
{
    char buffer[1024];

    checked_my_memset(buffer, 0, sizeof(buffer));
    netbsd_check(buffer, sizeof(buffer), 0);

    checked_my_memset(buffer, 'x', sizeof(buffer));
    netbsd_check(buffer, sizeof(buffer), 'x');
}

Test(my_memset, netbsd_return)
{
    char buffer[2];

    checked_my_memset((char *)1, 0, 0);
    checked_my_memset(buffer, 2, sizeof(buffer));
}

Test(my_memset, netsbd_basic)
{
    const size_t page_size = sysconf(_SC_PAGE_SIZE);
    
    char *our_buffer = malloc(page_size), *libc_buffer = malloc(page_size);
    cr_assert(our_buffer != NULL && libc_buffer != NULL);

    memset(libc_buffer, 0, page_size);
    checked_my_memset(our_buffer, 0, page_size);
    cr_assert_eq(my_memcmp(libc_buffer, our_buffer, page_size), 0);

    memset(libc_buffer, 'x', page_size);
    checked_my_memset(our_buffer, 'x', page_size);
    cr_assert_eq(my_memcmp(libc_buffer, our_buffer, page_size), 0);

    free(our_buffer);
    free(libc_buffer);
}

Test(my_memset, netbsd_non_zero)
{
    size_t page_size = sysconf(_SC_PAGE_SIZE);

    char *buffer = malloc(page_size);
    cr_assert_neq(buffer, NULL);

    for (size_t i = 0x21; i < 0x7F; ++i) {
        checked_my_memset(buffer, i, page_size);
        netbsd_check(buffer, page_size, i);
    }

    free(buffer);
}

Test(my_memset, netbsd_zero_size)
{
    char buf[1024];

    checked_my_memset(buf, 'x', sizeof(buf));
    netbsd_check(buf, sizeof(buf), 'x');

    checked_my_memset(buf + sizeof(buf) / 2, 0, 0);
    netbsd_check(buf, sizeof(buf), 'x');
}

// Add more tests from netbsd when we have bzero

Test(my_memset, netbsd_struct)
{
    struct stat st;
    st.st_dev = 0;
    st.st_ino = 1;
    st.st_mode = 2;
    st.st_nlink = 3;
    st.st_uid = 4;
    st.st_gid = 5;
    st.st_rdev = 6;
    st.st_size = 7;
    st.st_atime = 8;
    st.st_mtime = 9;

    checked_my_memset(&st, 0, sizeof(st));

    cr_assert_eq(st.st_dev, 0);
    cr_assert_eq(st.st_ino, 0);
    cr_assert_eq(st.st_mode, 0);
    cr_assert_eq(st.st_nlink, 0);
    cr_assert_eq(st.st_uid, 0);
    cr_assert_eq(st.st_gid, 0);
    cr_assert_eq(st.st_rdev, 0);
    cr_assert_eq(st.st_size, 0);
    cr_assert_eq(st.st_atime, 0);
    cr_assert_eq(st.st_mtime, 0);
}

Test(my_memset, cloudlibc_null)
{
    checked_my_memset((char *)5, 'A', 0);
}

Test(my_memset, cloudlibc_small)
{
    char buffer[11];
    checked_my_memset(buffer, '!', 10);
    buffer[10] = '\0';
    cr_assert_str_eq(buffer, "!!!!!!!!!!");
}

Test(my_memset, cloudlibc_large)
{
    char buffer[101];
    checked_my_memset(buffer, '!', 100);
    buffer[100] = '\0';
    cr_assert_str_eq(buffer, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
}

static void glibc_do_one_test(char *destination, int character, size_t length)
{
    char test_buffer[length];

    checked_my_memset(destination, character, length);
    memset(test_buffer, character, length);
    cr_assert_eq(my_memcmp(test_buffer, destination, length), 0);
}

static void glibc_do_test(size_t alignment, int character, size_t length)
{
    alignment &= 7;
    if (alignment + length > glibc_page_size)
        return;

    glibc_do_one_test(glibc_buf1 + alignment, character, length);
}

static void glibc_do_random_tests(void)
{
    unsigned char *p2 = (unsigned char *)glibc_buf2;

    for (size_t i = 0; i < 65536; ++i)
        p2[i] = random() & CHAR_MAX;

    for (size_t n = 0; n < 10000; ++n) {
        size_t size = ((random() & 31) == 0) ? 65536 : 512;
        unsigned char *p1 = (unsigned char *)glibc_buf1 + glibc_page_size - size;
        size_t length = random() & (size - 1);
        size_t alignment = size - length - (random() & 31);
        if (alignment > size)
            alignment = size - length;
        if ((random() & 7) == 0)
            alignment &= ~0x3F;

        int character = ((random() & 7) == 0) ? 0 : random() & CHAR_MAX;
        int character2 = random() & CHAR_MAX;
        if (character2 == character)
            character2 = (character + 1) & CHAR_MAX;

        size_t j = MY_MIN(length + alignment + 128, size);
        size_t k = (alignment >= 0x80) ? alignment - 0x80 : 0;

        for (size_t i = k; i < alignment; ++i)
            p1[i] = character2;
        for (size_t i = alignment + length; i < j; ++i)
            p1[i] = character2;

        for (size_t i = 0; i < length; ++i) {
            p1[i + alignment] = p2[i];
            if (p1[i + alignment] == character)
                p1[i + alignment] = character2;
        }
        checked_my_memset(p1 + alignment, character, length);
        size_t i = k;
        for (i = k; i < alignment; ++i)
            cr_assert_eq(p1[i], character2);
        for (; i < alignment + length; ++i)
            cr_assert_eq(p1[i], character);
        for (; i < j; ++i)
            cr_assert_eq(p1[i], character2);
    }
}

Test(my_memset, glibc)
{
    glibc_test_string_init();

    for (int character = -65; character <= 130; ++character) {
        for (size_t i = 0; i < 18; ++i)
            glibc_do_test(0, character, 1 << i);
        for (size_t i = 1; i < 32; ++i) {
            glibc_do_test(i, character, i);
            if (i & (i - 1))
                glibc_do_test(0, character, i);
        }
        glibc_do_test(1, character, 14);
        glibc_do_test(3, character, 1024);
        glibc_do_test(4, character, 64);
        glibc_do_test(2, character, 25);
    }

    glibc_do_random_tests();
}

// TODO add bzero tests from glibc when we have it

#define GCC_3_MAX_OFFSET (sizeof(long long))
#define GCC_3_MAX_COPY (0xF)
#define GCC_3_MAX_EXTRA (sizeof(long long))
#define GCC_3_MAX_LENGTH (GCC_3_MAX_OFFSET + GCC_3_MAX_COPY + GCC_3_MAX_EXTRA)

static union {
    char buffer[GCC_3_MAX_LENGTH];
    long long unused_align_to_int;
    long double unused_align_to_fp;
} gcc_3_buffer_union;

static void gcc_3_check(size_t offset, size_t length, int character)
{
    char *p = gcc_3_buffer_union.buffer;
    for (size_t i = 0; i < offset; ++i)
        cr_assert_eq(*p++, 'a');
    for (size_t i = 0; i < length; ++i)
        cr_assert_eq(*p++, character);
    for (size_t i = 0; i < GCC_3_MAX_EXTRA; ++i)
        cr_assert_eq(*p++, 'a');
}

Test(my_memset, gcc_3)
{
    for (size_t offset = 0; offset < 8; ++offset)
        for (size_t length = 0; length < GCC_3_MAX_COPY; ++length) {
            my_memset(gcc_3_buffer_union.buffer, 'a', sizeof(gcc_3_buffer_union.buffer));

            checked_my_memset(gcc_3_buffer_union.buffer + offset, '\0', length);
            gcc_3_check(offset, length, '\0');

            checked_my_memset(gcc_3_buffer_union.buffer + offset, 'A', length);
            gcc_3_check(offset, length, 'A');

            checked_my_memset(gcc_3_buffer_union.buffer + offset, 'B', length);
            gcc_3_check(offset, length, 'B');
        }
}

Test(my_memset, gcc_4)
{
    char buffer[15];

    for (size_t i = 0; i < sizeof(buffer); ++i)
        buffer[i] = i + 1;
    my_memset(buffer, 0, sizeof(buffer));
    for (size_t i = 0; i < sizeof(buffer); ++i)
        cr_assert_eq(buffer[i], 0);
}

Test(my_memset, scc)
{
    char buffer[40];

    my_memset(buffer, 2, sizeof(buffer));
    for (size_t i = 0; i < sizeof(buffer); ++i)
        cr_assert_eq(buffer[i], 2);
    my_memset(buffer, 0, 0);
    for (size_t i = 0; i < sizeof(buffer); ++i)
        cr_assert_eq(buffer[i], 2);
}

Test(my_memset, escape)
{
    uint8_t buffer[16] = {0};

    my_memset(buffer, ' ', 10);
    cr_assert_str_eq((char *)buffer, "          ");
    my_memset(buffer, 'a', 10);
    cr_assert_str_eq((char *)buffer, "aaaaaaaaaa");
    my_memset(buffer, 'e', 1);
    my_memset(buffer + 1, 'b', 2);
    my_memset(buffer + 3, 'c', 3);
    my_memset(buffer + 6, 'd', 4);
    cr_assert_str_eq((char *)buffer, "ebbcccdddd");
    my_memset(buffer, 'X', 0);
    cr_assert_str_eq((char *)buffer, "ebbcccdddd");
    my_memset(buffer, 'X', 5);
    cr_assert_str_eq((char *)buffer, "XXXXXcdddd");
    my_memset(buffer, 'X', 6);
    cr_assert_str_eq((char *)buffer, "XXXXXXdddd");
    my_memset(buffer, 'X', 7);
    cr_assert_str_eq((char *)buffer, "XXXXXXXddd");
    my_memset(buffer, 'X', 8);
    cr_assert_str_eq((char *)buffer, "XXXXXXXXdd");

    for (size_t i = 0; i < 8; ++i)
        for (size_t j = 0; j < 8; ++j) {
            my_memset(buffer, 0xFF, sizeof(buffer));
            my_memset(buffer + i, 0, j);
            escape_check_zero(buffer, i, j, sizeof(buffer));
        }
}

Test(my_memset, littlekernel)
{
    static const size_t MAX_SIZE = 256;
    char *destination = aligned_alloc(64, MAX_SIZE * 2);
    char *destination2 = aligned_alloc(64, MAX_SIZE * 2);

    for (size_t destination_alignment = 0; destination_alignment < 64; ++destination_alignment)
        for (size_t size = 0; size < MAX_SIZE; ++size) {
            littlekernel_fill_buffer(destination, MAX_SIZE * 2, 123514);
            littlekernel_fill_buffer(destination2, MAX_SIZE * 2, 123514);
            for (int c = -1; c < 258; ++c) {
                my_memset(destination + destination_alignment, c, size);
                memset(destination2 + destination_alignment, c, size);
                cr_assert_eq(my_memcmp(destination, destination2, MAX_SIZE * 2), 0);
            }
        }

    free(destination2);
    free(destination);
}

Test(my_memset, bionic)
{
    __auto_type state = bionic_test_state_new(64 * 1024);
    static const char CHARACTER = 'P';

    for (size_t i = 0; i < state.n - 1; ++i) {
        for (bionic_test_state_begin_iters(&state);
             bionic_test_state_has_next_iter(&state);
             bionic_test_state_next_iter(&state)) {
            checked_my_memset(state.ptr1, ~CHARACTER, state.max_length * 2);
            my_memcpy(state.ptr2, state.ptr1, state.max_length);

            size_t position = random() % (state.max_length - state.lengths[i]);

            memset(state.ptr1 + position, CHARACTER, state.lengths[i]);
            checked_my_memset(state.ptr2 + position, CHARACTER, state.lengths[i]);
            cr_assert_eq(my_memcmp(state.ptr1, state.ptr2, state.max_length), 0);
        }
    }

    bionic_test_state_destroy(&state);
}

static void bionic_do_memset_test(uint8_t *buffer, size_t length)
{
    memset(buffer, 0, length);
    int value = (length % 255) + 1;
    checked_my_memset(buffer, value, length);
    for (size_t i = 0; i < length; ++i)
        cr_assert_eq(buffer[i], value);
}

Test(my_memset, bionic_align)
{
    bionic_run_single_buffer_align_test(64 * 1024, &bionic_do_memset_test);
}

Test(my_memset, plauger)
{
    char buffer[20];

    my_memset(buffer, '*', 10);
    cr_assert_eq(buffer[9], '*');
    my_memset(buffer + 2, '%', 0);
    cr_assert_eq(buffer[2], '*');
}
