/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Calculates a square root (if it is a whole number)
*/

#include "my/misc.h"
#include "my/checked_multiply.h"
#include <limits.h>

// Returns 0 if the result we have is not the correct square root for nb,
// otherwise result
static int check_result(int result, int number)
{
    int mul_result;
    if (my_checked_multiply_int(result, result, &mul_result) &&
        mul_result == number)
        return (result);
    return (0);
}

static int try_find_square_root(int number)
{
    int small_candidate;
    int large_candidate;
    int multiply_result;

    if (number < 2)
        return (number);
    small_candidate = try_find_square_root(number >> 2) << 1;
    large_candidate = small_candidate + 1;
    if (!my_checked_multiply_int(large_candidate, large_candidate,
            &multiply_result) || (multiply_result > number))
        return (small_candidate);
    return (large_candidate);
}

int my_compute_square_root(int number)
{
    if (number < 0)
        return (0);
    return (check_result(try_find_square_root(number), number));
}
