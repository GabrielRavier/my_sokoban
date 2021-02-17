/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests memcpy
*/

#include "../tests_header.h"
#include "escape_check_zero.h"
#include "littlekernel_fill_buffer.h"
#include "bionic_test_state.h"
#include "../bionic_buffer.h"
#include "my/string.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

inline static uint32_t msws(void)
{
    static const uint64_t s = 0xb5ad4eceda1ce2a9;
    static uint64_t x = 0, w = 0;
    x *= x;
    x += (w += s);
    x = (x >> 32) | (x << 32);
    return (uint32_t)x;
}

static void checked_my_memcpy(void *destination, const void *source, size_t n)
{
    cr_assert_eq(my_memcpy(destination, source, n), destination);
}

Test(my_memcpy, buffers)
{
    enum {
        BUFFER_SIZE = 10240
    };
    static const size_t START_COPY = 1250, MAX_BLOCK_SIZE = 256, MAX_OFFSET = 3;
    char source[BUFFER_SIZE];
    char destination[BUFFER_SIZE];
    char backup_source[BUFFER_SIZE];
    size_t i;

    cr_assert_not(START_COPY + MAX_OFFSET + MAX_BLOCK_SIZE >= BUFFER_SIZE);

    for (i = 0; i < BUFFER_SIZE; ++i)
        backup_source[i] = source[i] = (char)(msws() | 1);

    // Makes calls to my_memcpy with block sizes ranging between 1 and MAX_BLOCK_SIZE bytes, with aligned and misaligned source and destination
    for (size_t sa = 0; sa <= MAX_OFFSET; ++sa)
        for (size_t da = 0; da <= MAX_OFFSET; ++da)
            for (size_t n = 1; n < MAX_BLOCK_SIZE; ++n) {
                my_memset(destination, 0x5B, BUFFER_SIZE);

                checked_my_memcpy(destination + START_COPY + da, source + sa, n);
                for (size_t j = 0; j < BUFFER_SIZE; ++j)
                    if (j < START_COPY + da)
                        cr_assert_eq(destination[j], 0x5B);
                    else if (j < START_COPY + da + n) {
                        i = j - START_COPY - da;
                        cr_assert_eq(destination[j], (source + sa)[i]);
                    } else
                        cr_assert_eq(destination[j], 0x5B);

                cr_assert_eq(my_memcmp(source, backup_source, BUFFER_SIZE), 0);
            }
}

Test(my_memcpy, escape)
{
    const uint8_t zeros[17] = {0};
    const uint8_t source[17] = "0123456789ABCDEF";
    uint8_t destination[17];

    checked_my_memcpy(destination, source, 10);
    destination[10] = '\0';
    cr_assert_str_eq((char *)destination, "0123456789");

    checked_my_memcpy(destination, source, 4);
    destination[4] = '\0';
    cr_assert_str_eq((char *)destination, "0123");

    checked_my_memcpy(destination, source, 0);
    destination[0] = '\0';
    cr_assert_str_eq((char *)destination, "");

    for (size_t i = 0; i < 8; ++i)
        for (size_t j = 0; j < 8; ++j) {
            my_memset(destination, 0xFF, sizeof(destination));
            checked_my_memcpy(destination + i, zeros + i, j);
            escape_check_zero(destination, i, j, sizeof(destination));
        }
}

Test(my_memcpy, littlekernel)
{
    static const size_t MAX_SIZE = 256;
    uint8_t *source = aligned_alloc(64, MAX_SIZE * 2);
    uint8_t *source2 = aligned_alloc(64, MAX_SIZE * 2);
    uint8_t *destination = aligned_alloc(64, MAX_SIZE * 2);
    uint8_t *destination2 = aligned_alloc(64, MAX_SIZE * 2);
    uint8_t *original_destination = aligned_alloc(64, MAX_SIZE * 2);
    uint8_t *original_destination2 = aligned_alloc(64, MAX_SIZE * 2);
    littlekernel_fill_buffer(source, MAX_SIZE * 2, 567);
    littlekernel_fill_buffer(source2, MAX_SIZE * 2, 567);
    littlekernel_fill_buffer(original_destination, MAX_SIZE * 2, 567);
    littlekernel_fill_buffer(original_destination2, MAX_SIZE * 2, 567);

    for (size_t source_align = 0; source_align < 64; ++source_align)
        for (size_t destination_align = 0; destination_align < 64; ++destination_align)
            for (size_t size = 0; size < MAX_SIZE; ++size) {
                memcpy(destination, original_destination, MAX_SIZE * 2);
                memcpy(destination2, original_destination2, MAX_SIZE * 2);

                memcpy(destination + destination_align, source + source_align, size);
                checked_my_memcpy(destination2 + destination_align, source2 + source_align, size);

                cr_assert_eq(my_memcmp(destination, destination2, MAX_SIZE * 2), 0);
            }

    free(original_destination2);
    free(original_destination);
    free(destination2);
    free(destination);
    free(source2);
    free(source);
}

Test(my_memcpy, bionic)
{
    __auto_type state = bionic_test_state_new(64 * 1024);
    static const int CHARACTER = 4;

    for (size_t i = 0; i < state.n - 1; ++i)
        for (bionic_test_state_begin_iters(&state);
             bionic_test_state_has_next_iter(&state);
             bionic_test_state_next_iter(&state)) {
            size_t position = random() % (state.max_length - state.lengths[i]);

            my_memset(state.ptr1, CHARACTER, state.lengths[i]);
            my_memset(state.ptr1 + state.lengths[i], ~CHARACTER, state.max_length - state.lengths[i]);

            my_memset(state.ptr2, CHARACTER, state.lengths[i]);
            my_memset(state.ptr2 + state.lengths[i], ~CHARACTER, state.max_length - state.lengths[i]);
            my_memset(state.ptr2 + position, '\0', state.lengths[i]);

            checked_my_memcpy(state.ptr2 + position, state.ptr1 + position, state.lengths[i]);
            cr_assert_eq(my_memcmp(state.ptr1, state.ptr2, state.max_length), 0);
        }

    bionic_test_state_destroy(&state);
}

static void do_bionic_memcpy_test(uint8_t *source, uint8_t *destination, size_t length)
{
    my_memset(source, (length % 255) + 1, length);
    my_memset(destination, 0, length);

    checked_my_memcpy(destination, source, length);
    cr_assert_eq(my_memcmp(source, destination, length), 0);
}

Test(my_memcpy, bionic_align)
{
    bionic_run_source_destination_buffer_align_test(64 * 1024, do_bionic_memcpy_test);
}

Test(my_memcpy, bionic_overread)
{
    bionic_run_source_destination_buffer_overread_test(do_bionic_memcpy_test);
}

// Technically not standard, but clang depends on this working
static uint8_t *g_bionic_memcpy_same_buffer;

static void bionic_do_memcpy_same_test(uint8_t *buffer, size_t len)
{
    checked_my_memcpy(buffer, g_bionic_memcpy_same_buffer, len);
    checked_my_memcpy(buffer, buffer, len);
    cr_assert_eq(my_memcmp(buffer, g_bionic_memcpy_same_buffer, len), 0);
}

Test(my_memcpy, bionic_source_destination_same)
{
    static const size_t BUFFER_SIZE = 4096;
 
    g_bionic_memcpy_same_buffer = malloc(BUFFER_SIZE);
    for (size_t i = 0; i < BUFFER_SIZE; ++i)
        g_bionic_memcpy_same_buffer[i] = i;
    bionic_run_single_buffer_align_test(BUFFER_SIZE, bionic_do_memcpy_same_test);
}

Test(my_memcpy, plauger)
{
    char destination[6];

    checked_my_memcpy(destination, "abcde", 6);
    cr_assert_str_eq(destination, "abcde");
}
