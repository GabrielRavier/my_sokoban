/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Recursively calculates nb to the power of p
*/

#include "my/misc.h"
#include "my/checked_multiply.h"

int my_compute_power_rec(int number, int power)
{
    int result;

    if (power < 0)
        return (0);
    if (power == 0)
        return (1);
    if (power % 2 == 0) {
        result = my_compute_power_rec(number, power / 2);
        if (!my_checked_multiply_int(result, result, &result))
            return (0);
    } else if (!my_checked_multiply_int(
            number, my_compute_power_rec(number, power - 1), &result))
        return (0);
    return (result);
}
