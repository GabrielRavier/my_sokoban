/*
** EPITECH PROJECT, 2020
** InfinAdd
** File description:
** Adds together two bigints
*/

#include "my/bigint.h"

void my_bigint_add(struct my_bigint *result, const struct my_bigint *operand2)
{
    bool is_result_negative;
    int compare_result;
    if (result->is_negative == operand2->is_negative)
        my_bigint_add_unsigned(result, operand2);
    else {
        compare_result = my_bigint_compare_unsigned(result, operand2);
        if (compare_result == 0)
            is_result_negative = false;
        else
            is_result_negative = compare_result >= 0 ?
                result->is_negative : operand2->is_negative;
        my_bigint_sub_unsigned(result, operand2);
        result->is_negative = is_result_negative;
    }
}
