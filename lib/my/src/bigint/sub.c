/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Subtracts two bigints
*/

#include "my/internal/bigint.h"
#include "my/bigint.h"

void my_bigint_sub(struct my_bigint *result, const struct my_bigint *operand2)
{
    bool is_result_negative = my_bigint_compare(result, operand2) <= 0;

    if (result->is_negative == operand2->is_negative)
        my_bigint_sub_unsigned(result, operand2);
    else
        my_bigint_add_unsigned(result, operand2);
    result->is_negative = is_result_negative;
}
