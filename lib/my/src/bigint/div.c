/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements bigint division
*/

#include "my/bigint.h"
#include "my/internal/bigint.h"

struct my_bigint *my_bigint_div(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    struct my_bigint *tmp = my_bigint_new_from_int(0);
    struct my_bigint *unused = my_bigint_new_from_int(0);

    my_bigint_div_mod(result, operand2, tmp, unused);
    my_bigint_assign(result, tmp);
    my_bigint_free(tmp);
    my_bigint_free(unused);
    return (result);
}

struct my_bigint *my_bigint_div_int(struct my_bigint *result, int operand2)
{
    struct my_bigint *tmp;

    if (operand2 == 10) {
        my_string_erase(result->number, 0, 1);
        if (result->number->length == 0)
            my_string_append_char(result->number, 0);
    } else {
        tmp = my_bigint_new_from_int(operand2);
        my_bigint_div(result, tmp);
        my_bigint_free(tmp);
    }
    return (result);
}
