/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests my_memcpy
*/

#include "my/string.h"
#include <criterion/criterion.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 10240
#define START_COPY 2560
#define MAX_BLOCK_SIZE 256
#define MAX_OFFSET 3

#if (START_COPY + MAX_OFFSET + MAX_BLOCK_SIZE >= BUFFER_SIZE)
    #error "Won't compile, there would be a buffer overrun"
#endif

inline static uint32_t msws() {
    static const uint64_t s = 0xb5ad4eceda1ce2a9;
    static uint64_t x = 0, w = 0;
    x *= x; 
    x += (w += s); 
    return x = (x>>32) | (x<<32);
}

Test(my_memcpy, buffers)
{
    char source[BUFFER_SIZE];
    char destination[BUFFER_SIZE];
    char backup_source[BUFFER_SIZE];
    size_t i;

    for (i = 0; i < BUFFER_SIZE; ++i)
        backup_source[i] = source[i] = msws() | 1;

    // Makes calls to my_memcpy with block sizes ranging between 1 and MAX_BLOCK_SIZE bytes, with aligned and misaligned source and destination
    for (size_t sa = 0; sa <= MAX_OFFSET; ++sa)
        for (size_t da = 0; da <= MAX_OFFSET; ++da)
            for (size_t n = 1; n < MAX_BLOCK_SIZE; ++n) {
                for (size_t j = 0; j < BUFFER_SIZE; ++j)
                    destination[j] = 0x5B;

                cr_assert_eq(my_memcpy(destination + START_COPY + da, source + sa, n), (destination + START_COPY + da));
                for (size_t j = 0; j < BUFFER_SIZE; ++j)
                    if (j < START_COPY + da)
                        cr_assert_eq(destination[j], 0x5B);
                    else if (j < START_COPY + da + n) {
                        i = j - START_COPY - da;
                        cr_assert_eq(destination[j], (source + sa)[i]);
                    }
                    else
                        cr_assert_eq(destination[j], 0x5B);

                for (size_t j = 0; j < BUFFER_SIZE; ++j)
                    cr_assert_eq(source[j], backup_source[j]);
            }
}
