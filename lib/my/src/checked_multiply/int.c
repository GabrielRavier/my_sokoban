/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar - Day 05
** File description:
** Safely multiplies a signed number without overflow
*/

#include "my/checked_multiply.h"
#include <stdbool.h>
#include <limits.h>

#ifndef __GNUC__
    #error "Only works on GCC-compatible compilers"
#endif

// If lhs * rhs would overflow, returns false. Otherwise, sets *result to lhs *
// rhs and returns true.
bool my_checked_multiply_int(int lhs, int rhs, int *result)
{
    return (__builtin_mul_overflow(lhs, rhs, result) == false);
}
