/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares macros from libmy
*/

#pragma once

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

// Returns the maximum of a and b
#define MY_MAX(a, b) ((a) > (b) ? (a) : (b))

// Returns the minimum of a and b
#define MY_MIN(a, b) ((a) > (b) ? (b) : (a))
