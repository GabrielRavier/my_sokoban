/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares macros from libmy
*/

#pragma once

#define MY_PREPROCESSOR_CONCAT_YES_REALLY_EXPAND_THESE_ARGUMENTS(a, b) a##b
#define MY_PREPROCESSOR_CONCAT(a, b) \
    MY_PREPROCESSOR_CONCAT_YES_REALLY_EXPAND_THESE_ARGUMENTS(a, b)

// Gives us a relatively unique identifier. Provide a prefix if you use this
// several times on the same line
#define MY_MAKE_UNIQUE_IDENTIFIER(prefix) MY_PREPROCESSOR_CONCAT( \
    MY_PREPROCESSOR_CONCAT(__UNIQUE_IDENTIFIER, prefix), __LINE__)

// Produces a build error if expression is non-zero, but still allows usage in
// constant expressions
#define MY_BUILD_BUG_ON_ZERO(expression) \
    ((int)(__extension__ sizeof(struct { int : (-!!(expression)); })))

// Determines whether two expressions have the same type, though it does not
// determine whether they have different qualifiers
#define MY_IS_SAME_TYPE(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

// Fails to compile if the passed expression is not an array
#define MY_BUILD_BUG_ON_NON_ARRAY(array) \
    MY_BUILD_BUG_ON_ZERO(MY_IS_SAME_TYPE((array), &(array)[0]))

// Determines the amount of elements in an array. Will fail to compile on things
// that aren't arrays
#define MY_ARRAY_SIZE(array) \
    (sizeof(array) / sizeof((array)[0]) + MY_BUILD_BUG_ON_NON_ARRAY(array))

// Only compares a and b once, to avoid side effects
#define MY_MAKE_MIN_MAX_COMPARE_ONCE(a, b, unique_identifier_a, \
    unique_identifier_b, operation) __extension__ ({ \
        typeof(a) unique_identifier_a = (a); \
        typeof(b) unique_identifier_b = (b); \
        ((unique_identifier_a) operation (unique_identifier_b) ? \
            (unique_identifier_a) : \
            (unique_identifier_b)); })

#define MY_SWAP(a, b) \
    do { \
        typeof(a) swap_tmp = (a); \
        (a) = (b); \
        (b) = swap_tmp; } while (0)

// Returns the minimum of a and b
#define MY_MIN(a, b) MY_MAKE_MIN_MAX_COMPARE_ONCE(a, b, \
    MY_MAKE_UNIQUE_IDENTIFIER(_a), MY_MAKE_UNIQUE_IDENTIFIER(_b), <)

// Returns the maximum of a and b
#define MY_MAX(a, b) MY_MAKE_MIN_MAX_COMPARE_ONCE(a, b, \
    MY_MAKE_UNIQUE_IDENTIFIER(_a), MY_MAKE_UNIQUE_IDENTIFIER(_b), >)

// Returns a value, clamped to be between low and high
#define MY_CLAMP(value, low, high) MY_MIN((typeof(value))MY_MAX(value, low), high)
