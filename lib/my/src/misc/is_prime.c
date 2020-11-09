/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Returns whether the number is prime
*/

#include "my/misc.h"
#include "my/checked_multiply.h"
#include <stdbool.h>

// From my_compute_square_root.c
static unsigned internal_get_square_root_floor(unsigned nb)
{
    unsigned small_candidate;
    unsigned large_candidate;
    unsigned multiply_result;

    if (nb < 2)
        return (nb);
    small_candidate = internal_get_square_root_floor(nb >> 2u) << 1u;
    large_candidate = small_candidate + 1;
    if (!my_checked_multiply_unsigned(large_candidate, large_candidate,
            &multiply_result) || (multiply_result > nb))
        return (small_candidate);
    return (large_candidate);
}

// We use the floor of the square root plus 1 to be sure, so we either test up
// to the ceil of the square root or one after the square root (an extra
// iteration won't cost too long so that's good)
bool my_is_prime(unsigned nb)
{
    const unsigned square_root_floor = internal_get_square_root_floor(nb) + 1;

    if (nb <= 1)
        return (false);
    if (nb == 2)
        return (true);
    if ((nb % 2) == 0)
        return (false);
    for (unsigned i = 3; i < square_root_floor; i += 2)
        if ((nb % i) == 0)
            return (false);
    return (true);
}
