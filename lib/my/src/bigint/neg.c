/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Negates a bigint
*/

#include "my/bigint.h"

static bool is_zero(const struct my_bigint *num)
{
    return (num->number->length == 1 && num->number->string[0] == 0);
}

struct my_bigint *my_bigint_neg(struct my_bigint *self)
{
    self->is_negative = !is_zero(self) && !self->is_negative;
    return (self);
}
