/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines a function of the strto family generically
*/

#pragma once

#include "my/ctype.h"
#include <errno.h>
#include <stdbool.h>

static char digit(char c)
{
    return (c <= '9' ? c - '0' : my_tolower(c) + 10 - 'a');
}

static TYPE finish(const char *num_ptr, char **end_num_ptr, int base,
    bool is_negative)
{
    bool has_overflowed = false;
    TYPE_UNSIGNED result = digit(*num_ptr++);
    TYPE_UNSIGNED threshold = is_negative ? -(TYPE_UNSIGNED)TYPE_MIN : TYPE_MAX;

    while (my_isalnum(*num_ptr) && digit(*num_ptr) < base) {
        has_overflowed = has_overflowed || (result > threshold / base);
        result *= base;
        has_overflowed = has_overflowed ||
            (result > threshold - digit(*num_ptr));
        result += digit(*num_ptr++);
    }
    if (end_num_ptr)
        *end_num_ptr = (char *)num_ptr;
    if (has_overflowed)
        errno = ERANGE;
    return (has_overflowed ? (is_negative ? TYPE_MIN : TYPE_MAX) :
        (is_negative ? -result : result));
}

static TYPE INTERNAL_FUNC_NAME(const char *num_ptr, char **end_num_ptr,
    int base)
{
    bool is_negative = false;

    if (base == 1 || (unsigned)base > 36) {
        errno = EINVAL;
        return (0);
    }
    if (end_num_ptr)
        *end_num_ptr = (char *)num_ptr;
    while (my_isspace(*num_ptr))
        ++num_ptr;
    if (*num_ptr == '-' || *num_ptr == '+')
        is_negative = (*num_ptr++ == '-');
    if (base == 0)
        base = (*num_ptr != '0') ? 10 : my_tolower(num_ptr[1]) == 'x' ? 16 : 8;
    if (!my_isalnum(*num_ptr) || digit(*num_ptr) >= base)
        return (0);
    if (base == 16 && *num_ptr == '0' && my_tolower(num_ptr[1]) == 'x' &&
        my_isxdigit(num_ptr[2]))
        num_ptr += 2;
    return (finish(num_ptr, end_num_ptr, base, is_negative));
}
