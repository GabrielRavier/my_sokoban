/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares inttypes-related entities
*/

#pragma once

#include "features.h"
#include <stdint.h>

/// Converts a string to an intmax_t.
intmax_t my_strtoimax(const char *MY_RESTRICT num_ptr,
    char **MY_RESTRICT end_num_ptr, int base) MY_ATTR_NONNULL((1))
    MY_ATTR_NOTHROW;
