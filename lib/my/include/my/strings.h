/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares strings-related entities
*/

#pragma once

#include "features.h"
#include <stddef.h>

// Compares two strings, ignoring case
int my_strcasecmp(const char *s1, const char *s2) MY_ATTR_NOTHROW MY_ATTR_PURE
    MY_ATTR_NONNULL((1, 2));

// Compares the first length bytes of s1 and s2, returning 0 if they are equal
// and a non-zero value otherwise
int my_bcmp(const void *s1, const void *s2, size_t length) MY_ATTR_NOTHROW
    MY_ATTR_PURE MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_only, 1, 3))
    MY_ATTR_ACCESS((read_only, 2, 3));

// Same as my_memmove, except source and destination are interchanged
void my_bcopy(const void *source, void *destination, size_t size)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((read_only, 1, 3)) MY_ATTR_ACCESS((write_only, 2, 3));
