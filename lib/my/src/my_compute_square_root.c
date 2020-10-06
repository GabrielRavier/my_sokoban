/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Calculates a square root (if it is a whole number)
*/

#include "my.h"
#include <limits.h>

// Returns 0 if the result we have is not the correct square root for nb,
// otherwise result
static int check_result(int result, int nb)
{
    int mul_result;
    if (my_checked_multiply(result, result, &mul_result) && mul_result == nb)
        return result;
    return 0;
}

static int try_find_square_root(int nb)
{
    int small_candidate;
    int large_candidate;
    int multiply_result;

    if (nb < 2)
        return nb;

    small_candidate = try_find_square_root(nb >> 2) << 1;
    large_candidate = small_candidate + 1;

    if (!my_checked_multiply(
        large_candidate, large_candidate, &multiply_result) ||
        (multiply_result > nb))
        return small_candidate;
    return large_candidate;
}

int my_compute_square_root(int nb)
{
    if (nb < 0)
        return 0;

    return check_result(try_find_square_root(nb), nb);
}
