/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines compute_power_rec
*/

#include "my/misc.h"

int my_compute_power_rec(int number, int power)
{
    int result;

    if (power < 0)
        return (0);
    if (power == 0)
        return (1);
    if (power % 2 == 0) {
        result = my_compute_power_rec(number, power / 2);
        if (__builtin_mul_overflow(result, result, &result))
            return (0);
    } else if (__builtin_mul_overflow(
            number, my_compute_power_rec(number, power - 1), &result))
        return (0);
    return (result);
}
