/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compares two bigints without the sign
*/

#include "my/bigint.h"

int my_bigint_compare_unsigned(const struct my_bigint *operand1,
    const struct my_bigint *operand2)
{
    if (operand1->number->length > operand2->number->length)
        return (1);
    if (operand1->number->length < operand2->number->length)
        return (-1);
    for (size_t i = operand1->number->length; i != 0; --i) {
        if (operand1->number->string[i - 1] > operand2->number->string[i - 1])
            return (1);
        if (operand1->number->string[i - 1] < operand2->number->string[i - 1])
            return (-1);
    }
    return (0);
}
