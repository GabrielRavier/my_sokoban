/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compares two bigints without the sign
*/

#include "my_bigint.h"

int my_bigint_compare_unsigned(
    const struct my_bigint *operand1, const struct my_bigint *operand2)
{
    if (operand1->num_digits > operand2->num_digits)
        return 1;
    else if (operand1->num_digits < operand2->num_digits)
        return -1;

    for (size_t i = operand1->num_digits; i != 0; --i) {
        if (operand1->number[i - 1] > operand2->number[i - 1])
            return 1;
        else if (operand1->number[i - 1] < operand2->number[i - 1])
            return -1;
    }

    return 0;
}
