/*
** EPITECH PROJECT, 2020
** InfinAdd
** File description:
** Adds together two bigints
*/

#include "my_bigint.h"

void my_bigint_add(struct my_bigint *result, const struct my_bigint *operand2)
{
    bool is_result_negative;
    if (result->is_negative == operand2->is_negative)
        my_bigint_add_unsigned(result, operand2);
    else {
        is_result_negative = my_bigint_compare_unsigned(result, operand2) > 0 ? result->is_negative : operand2->is_negative;
        my_bigint_sub_unsigned(result, operand2);
        result->is_negative = is_result_negative;
    }
}
