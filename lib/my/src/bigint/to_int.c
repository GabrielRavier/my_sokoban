/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts a bigint to an int
*/

#include "my/bigint.h"

int my_bigint_to_int(const struct my_bigint *num)
{
    int result = 0;
    int multiplier = 1;

    for (size_t i = 0; i < num->number->length; ++i) {
        result += num->number->string[i] * multiplier;
        multiplier *= 10;
    }
    if (num->is_negative)
        result = -result;
    return (result);
}
