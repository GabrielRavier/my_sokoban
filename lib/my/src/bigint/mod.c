/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements bigint modulo
*/

#include "my/bigint.h"
#include "my/internal/bigint.h"

struct my_bigint *my_bigint_mod(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    struct my_bigint *tmp = my_bigint_new_from_int(0);
    struct my_bigint *unused = my_bigint_new_from_int(0);

    my_bigint_div_mod(result, operand2, unused, tmp);
    my_bigint_assign(result, tmp);
    my_bigint_free(tmp);
    my_bigint_free(unused);
    return (result);
}

struct my_bigint *my_bigint_mod_int(struct my_bigint *result, int operand2)
{
    struct my_bigint *tmp;

    if (operand2 == 10)
        my_string_resize(result->number, 1);
    else {
        tmp = my_bigint_new_from_int(operand2);
        my_bigint_mod(result, tmp);
        my_bigint_free(tmp);
    }
    return (result);
}
