/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares internal math.h-related entities
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

// We don't need the same trick as for my_ieee754_double_parts since the
// mantissa aligns nicely
union my_ieee754_long_double_parts {
    long double as_long_double;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    struct {
        union {
            uint64_t mantissa : 64;
            struct {
                uint32_t mantissa_low : 32;
                uint32_t mantissa_high : 32;
            };
        };
        uint16_t exponent : 15;
        bool sign : 1;
        uint64_t unused : 40;
#else
        uint64_t unused : 40;
        bool sign : 1;
        uint16_t exponent : 15;
        union {
            uint64_t mantissa : 64;
            struct {
                uint32_t mantissa_high : 32;
                uint32_t mantissa_low : 32;
            };
        };
#endif
    };
};

// We use two seperate structs here because putting a struct inside of another
// struct will always result in padding if it does not align to a full byte
union my_ieee754_double_parts {
    double as_double;
    uint64_t as_u64;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    struct {
        uint32_t mantissa_low : 32;
        uint32_t mantissa_high : 20;
        uint16_t exponent : 11;
        bool sign : 1;
    };
    struct {
        uint64_t mantissa : 52;
    };
#else
    struct {
        bool sign : 1;
        uint16_t exponent : 11;
        uint32_t mantissa_high : 20;
        uint32_t mantissa_low : 32;
    };
    struct {
        uint16_t padding_for_mantissa : 12;
        uint64_t mantissa : 52;
    };
#endif
};

union my_ieee754_float_parts {
    float as_float;
    uint32_t as_u32;
    struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        uint32_t mantissa : 23;
        uint16_t exponent : 8;
        bool sign : 1;
#else
        bool sign : 1;
        uint16_t exponent : 8;
        uint32_t mantissa : 23;
#endif
    };
};
