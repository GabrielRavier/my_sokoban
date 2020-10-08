/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Returns whether the number is prime
*/

#include "my.h"

// From my_compute_square_root.c
static int internal_get_square_root_floor(int nb)
{
    int small_candidate;
    int large_candidate;
    int multiply_result;

    if (nb < 2)
        return nb;

    small_candidate = internal_get_square_root_floor(nb >> 2) << 1;
    large_candidate = small_candidate + 1;

    if (!my_checked_multiply(large_candidate, large_candidate, &multiply_result)
        || (multiply_result > nb))
        return small_candidate;
    return large_candidate;
}

// We use the floor of the square root plus 1 to be sure, so we either test up
// to the ceil of the square root or one after the square root (an extra
// iteration won't cost too long so that's good)
int my_is_prime(int nb)
{
    int square_root_floor = internal_get_square_root_floor(nb) + 1;

    if (nb <= 1)
        return 0;

    if (nb == 2)
        return 1;

    if ((nb % 2) == 0)
        return 0;

    for (int i = 3; i < square_root_floor; i += 2)
        if ((nb % i) == 0)
            return 0;

    return 1;
}
