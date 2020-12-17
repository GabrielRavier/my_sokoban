/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares checked_multiply-related functions from libmy
*/

#pragma once

#include "my/config.h"
#include <stdbool.h>

// Promotes the two argument into infinite precision integer, adds them, stores
// the result (casted to the type of the pointed to value) and returns whether
// the casted value is equal to the infinite precision value
bool my_checked_multiply_int(int lhs, int rhs,
    int *result) MY_ATTR_WARN_UNUSED_RESULT;
bool my_checked_multiply_unsigned(unsigned lhs, unsigned rhs,
    unsigned *result) MY_ATTR_WARN_UNUSED_RESULT;
