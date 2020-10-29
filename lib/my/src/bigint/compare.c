/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compares two bigints
*/

#include "my/bigint.h"

int my_bigint_compare(const struct my_bigint *operand1,
    const struct my_bigint *operand2)
{
    if (operand1->is_negative && !operand2->is_negative)
        return (-1);
    if (!operand1->is_negative && operand2->is_negative)
        return (1);
    return (operand1->is_negative ?
        my_bigint_compare_unsigned(operand2, operand1) :
        my_bigint_compare_unsigned(operand1, operand2));
}

int my_bigint_compare_int(const struct my_bigint *operand1, int operand2)
{
    struct my_bigint *tmp = my_bigint_new_from_int(operand2);
    int result = my_bigint_compare(operand1, tmp);

    my_bigint_free(tmp);
    return (result);
}
