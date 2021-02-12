/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares limits-related entities
*/

#pragma once

#include <limits.h>

#define MY_NUMERIC_LIMITS_MAX(type) ((type)-1 > 0 ? \
        (sizeof(type) == sizeof(unsigned char) ? \
            ((type)2 == 1 ? 1 : UCHAR_MAX) : \
        sizeof(type) == sizeof(unsigned short) ? USHRT_MAX : \
        sizeof(type) == sizeof(unsigned int) ? UINT_MAX : \
        sizeof(type) == sizeof(unsigned long) ? ULONG_MAX : \
        sizeof(type) == sizeof(unsigned long long) ? ULLONG_MAX : 0 \
    ) : (sizeof(type) == sizeof(signed char) ? SCHAR_MAX : \
        sizeof(type) == sizeof(short) ? SHRT_MAX : \
        sizeof(type) == sizeof(int) ? INT_MAX : \
        sizeof(type) == sizeof(long) ? LONG_MAX : \
        sizeof(type) == sizeof(long long) ? LLONG_MAX : 0))
