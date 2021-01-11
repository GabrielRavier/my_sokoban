/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares algorithm-related entities
*/

#pragma once

#include "../macros.h"

/// Replaces all elements that are equal to old_value with new_value in the
/// range
#define MY_REPLACE(first_param, last, old_value, new_value) \
    do { \
        __auto_type first = (first_param); \
        for (; first != (last); ++first) \
            if (*first == (old_value)) \
                *first = (new_value); \
    } while (0)

/// Returns the number of elements in the range [first, last) equal to value
#define MY_COUNT(first_param, last, value) \
    (__extension__({ \
        size_t result = 0; \
        __auto_type first = (first_param); \
        for (; first != (last); ++first) \
            if (*first == (value)) \
                ++result; \
        result; \
    }))

/// Only compares a and b once, to avoid side effects
#define MY_MAKE_MIN_MAX_COMPARE_ONCE(a, b, unique_identifier_a, \
    unique_identifier_b, operation) \
    (__extension__ ({                                   \
        __auto_type (unique_identifier_a) = (a);        \
        __auto_type (unique_identifier_b) = (b);        \
        ((unique_identifier_a) operation (unique_identifier_b) ? \
            (unique_identifier_a) : \
            (unique_identifier_b)); \
    }))

/// Returns the minimum of a and b
#define MY_MIN(a, b) MY_MAKE_MIN_MAX_COMPARE_ONCE(a, b, \
    MY_MAKE_UNIQUE_IDENTIFIER(_a), MY_MAKE_UNIQUE_IDENTIFIER(_b), <)

/// Returns the maximum of a and b
#define MY_MAX(a, b) MY_MAKE_MIN_MAX_COMPARE_ONCE(a, b, \
    MY_MAKE_UNIQUE_IDENTIFIER(_a), MY_MAKE_UNIQUE_IDENTIFIER(_b), >)

/// Returns a value, clamped to be between low and high
#define MY_CLAMP(value, low, high) (__extension__ \
    MY_MIN((typeof(value))MY_MAX(value, low), high))
