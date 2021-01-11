/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests memcpy
*/

#include "../tests_header.h"
#include "my/string.h"
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

Test(my_memcpy, buffers)
{
#define BUFFER_SIZE 10240
    static const size_t START_COPY = 2560, MAX_BLOCK_SIZE = 256, MAX_OFFSET = 3;
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

                cr_assert_eq(my_memcpy(destination + START_COPY + da, source + sa, n), (destination + START_COPY + da));
                for (size_t j = 0; j < BUFFER_SIZE; ++j)
                    if (j < START_COPY + da)
                        cr_assert_eq(destination[j], 0x5B);
                    else if (j < START_COPY + da + n) {
                        i = j - START_COPY - da;
                        cr_assert_eq(destination[j], (source + sa)[i]);
                    } else
                        cr_assert_eq(destination[j], 0x5B);

                for (size_t j = 0; j < BUFFER_SIZE; ++j)
                    cr_assert_eq(source[j], backup_source[j]);
            }
#undef BUFFER_SIZE
}
