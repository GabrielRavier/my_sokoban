/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar - Day 05
** File description:
** Safely multiplies a number without overflow
*/

#include "my/checked_multiply.h"

#ifndef __GNUC__
    #error "Only works on GCC-compatible compilers"
#endif

bool my_checked_multiply_unsigned(unsigned lhs, unsigned rhs, unsigned *result)
{
    return __builtin_mul_overflow(lhs, rhs, result) == false;
}
