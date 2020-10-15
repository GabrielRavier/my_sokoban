/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Does an unsigned subtraction of two bigints
*/

#include "my_bigint_internal.h"
#include "my_bigint.h"
#include "my.h"

void my_bigint_sub_unsigned(struct my_bigint *result, const struct my_bigint *operand2)
{
    size_t required_digits = MY_MAX(my_strlen(result->number), my_strlen(operand2->number)) + 1;
    my_bigint_at_least_digits(result, required_digits);

    __builtin_trap();
}
