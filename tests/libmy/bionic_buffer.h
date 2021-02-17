/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines bionic_buffer stuff
*/

#pragma once

#include "tests_header.h"
#include "my/cpp-like/iterator.h"
#include "my/string.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stddef.h>

static const size_t BIONIC_BUFFER_FENCEPOST_LENGTH = 8;

static const int BIONIC_BUFFER_SINGLE_ALIGNS[][2] = {
    // Both buffers at same alignment.
    { 1, 0 },
    { 2, 0 },
    { 4, 0 },
    { 8, 0 },
    { 16, 0 },
    { 32, 0 },
    { 64, 0 },
    { 128, 0 },

    // General unaligned cases.
    { 4, 1 },
    { 4, 2 },
    { 4, 3 },

    { 8, 1 },
    { 8, 2 },
    { 8, 3 },
    { 8, 4 },
    { 8, 5 },
    { 8, 6 },
    { 8, 7 },

    { 128, 1 },
    { 128, 4 },
    { 128, 8 },
    { 128, 12 },
    { 128, 16 },
};

static size_t bionic_buffer_set_increase(size_t length)
{
    return length >= 4096 ? 1024 : length >= 1024 ? 256 : 1;
}

static void *bionic_buffer_get_aligned_ptr(void *original_ptr, int alignment, int or_mask)
{
    uintptr_t ptr = (uintptr_t)original_ptr;

    if (alignment > 0) {
        ptr += alignment - (ptr & (alignment - 1));
        ptr |= alignment | or_mask;
    }
    return (void *)ptr;
}

static void bionic_buffer_set_fencepost(uint8_t *buffer)
{
    for (size_t i = 0; i < BIONIC_BUFFER_FENCEPOST_LENGTH; i += 2) {
        buffer[i] = 0xDE;
        buffer[i + 1] = 0xAD;
    }
}

static void bionic_buffer_verify_fencepost(uint8_t *buffer)
{
    for (size_t i = 0; i < BIONIC_BUFFER_FENCEPOST_LENGTH; i += 2) {
        if (buffer[i] != 0xDE || buffer[i + 1] != 0xAD) {
            uint8_t expected_value;
            if (buffer[i] == 0xDE) {
                ++i;
                expected_value = 0xAD;
            } else
                expected_value = 0xDE;
            cr_assert_eq(expected_value, buffer[i]);
        }
    }
}

static void bionic_run_single_buffer_align_test(size_t max_test_size, void (*test_func)(uint8_t *, size_t))
{
    uint8_t *buffer = malloc(max_test_size * 3);

    cr_assert_neq(buffer, NULL);
    for (size_t i = 0; i < MY_ARRAY_SIZE(BIONIC_BUFFER_SINGLE_ALIGNS); ++i) {
        size_t increase = 1;
        for (size_t length = 0; length <= max_test_size; length += increase) {
            increase = bionic_buffer_set_increase(length);

            uint8_t *buffer_aligned = bionic_buffer_get_aligned_ptr(buffer + BIONIC_BUFFER_FENCEPOST_LENGTH, BIONIC_BUFFER_SINGLE_ALIGNS[i][0], BIONIC_BUFFER_SINGLE_ALIGNS[i][1]);

            bionic_buffer_set_fencepost(&buffer_aligned[-BIONIC_BUFFER_FENCEPOST_LENGTH]);
            bionic_buffer_set_fencepost(&buffer_aligned[length]);

            test_func(buffer_aligned, length);

            bionic_buffer_verify_fencepost(&buffer_aligned[-BIONIC_BUFFER_FENCEPOST_LENGTH]);
            bionic_buffer_verify_fencepost(&buffer_aligned[length]);
        }
    }
    free(buffer);
}

static void bionic_run_single_buffer_overread_test(void (*test_func)(uint8_t *, size_t))
{
    const size_t page_size = sysconf(_SC_PAGE_SIZE);

    uint8_t *memory;
    cr_assert_eq(posix_memalign((void **)&memory, page_size, 2 * page_size), 0);
    my_memset(memory, 0x23, 2 * page_size);

    // Make the second page fault on read/write
    cr_assert_eq(mprotect(&memory[page_size], page_size, PROT_NONE), 0);

    for (size_t i = 0; i < page_size; ++i)
        test_func(&memory[page_size - i], i);

    cr_assert_eq(mprotect(&memory[page_size], page_size, PROT_READ | PROT_WRITE), 0);
    free(memory);
}
