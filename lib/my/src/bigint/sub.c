/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Subtracts two bigints
*/

#include "my/bigint.h"

struct my_bigint *my_bigint_sub(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    bool is_result_negative = my_bigint_compare(result, operand2) < 0;

    if (result->is_negative != operand2->is_negative)
        my_bigint_add_unsigned(result, operand2);
    else
        my_bigint_sub_unsigned(result, operand2);
    result->is_negative = is_result_negative;
    return (result);
}

struct my_bigint *my_bigint_sub_int(struct my_bigint *result, int operand2)
{
    struct my_bigint *tmp = my_bigint_new_from_int(operand2);

    my_bigint_sub(result, tmp);
    my_bigint_free(tmp);
    return (result);
}
