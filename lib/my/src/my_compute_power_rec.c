/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Recursively calculates nb to the power of p
*/

#include "my/misc.h"
#include "my/checked_multiply.h"

int my_compute_power_rec(int nb, int p)
{
    int result;

    if (p < 0)
        return 0;

    if (p == 0)
        return 1;

    if (p % 2 == 0) {
        result = my_compute_power_rec(nb, p / 2);
        if (!my_checked_multiply_int(result, result, &result))
            return 0;
    } else if (!my_checked_multiply_int(nb, my_compute_power_rec(nb, p - 1),
            &result))
        return 0;

    return result;
}
