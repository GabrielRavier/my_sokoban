/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares iterator-related utilities
*/

#include "../macros.h"

/// Determines the amount of elements in an array. Will fail to compile on things
/// that aren't arrays
#ifndef __cplusplus
/// Ignore the C++ compatibility warning here, we aren't even enabling this in
/// C++ (use std::size instead)
#define MY_ARRAY_SIZE(array) (__extension__({    \
    size_t result; \
    _Pragma("GCC diagnostic push"); \
    _Pragma("GCC diagnostic ignored \"-Wc++-compat\"") \
    result = (sizeof(array) / sizeof((array)[0]) + \
        MY_BUILD_BUG_ON_NON_ARRAY(array)); \
    _Pragma("GCC diagnostic pop"); \
    result;}))
#endif
