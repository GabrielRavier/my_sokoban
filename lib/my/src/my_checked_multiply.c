/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar - Day 05
** File description:
** Safely multiplies a number without overflow
*/

#include "checked_multiply.h"
#include <stdbool.h>
#include <limits.h>

// Returns true if lhs and rhs have the same sign (i.e. they are both negative
// or both positive
static bool same_signs(int lhs, int rhs)
{
    return (lhs < 0) == (rhs < 0);
}

// These two functions return true if overflow occurs for the specific case they
// check
static bool check_overflow_multiply_same_signs(int lhs, int rhs)
{
    if (lhs >= 0) {
        if (lhs && (INT_MAX / lhs) < rhs)
            return true;
    } else {
        if (lhs == INT_MIN || rhs == INT_MIN)
            return true;
        if ((INT_MAX / -lhs) < -rhs)
            return true;
    }

    return false;
}

static bool check_overflow_opposite_signs_multiply(
    int positive_operand, int negative_operand)
{
    return (
        positive_operand && negative_operand < (INT_MIN / positive_operand));
}

// If lhs * rhs would overflow, returns false. Otherwise, sets *result to lhs *
// rhs and returns true.
bool my_checked_multiply(int lhs, int rhs, int *result)
{
    if (same_signs(lhs, rhs)) {
        if (check_overflow_multiply_same_signs(lhs, rhs))
            return false;
    } else if (check_overflow_opposite_signs_multiply(
        lhs < 0 ? rhs : lhs, lhs < 0 ? lhs : rhs))
        return false;
    *result = lhs * rhs;
    return true;
}
