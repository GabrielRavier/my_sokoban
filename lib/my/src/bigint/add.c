/*
** EPITECH PROJECT, 2020
** InfinAdd
** File description:
** Adds together two bigints
*/

#include "my/bigint.h"

struct my_bigint *my_bigint_add(struct my_bigint *result,
    const struct my_bigint *operand2)
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
            is_result_negative = compare_result >= 0 ? result->is_negative :
                operand2->is_negative;
        my_bigint_sub_unsigned(result, operand2);
        result->is_negative = is_result_negative;
    }
    return (result);
}

struct my_bigint *my_bigint_add_int(struct my_bigint *result, int operand2)
{
    struct my_bigint *tmp = my_bigint_new_from_int(operand2);

    my_bigint_add(result, tmp);
    my_bigint_free(tmp);
    return (result);
}
