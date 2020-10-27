/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Negates a bigint
*/

#include "my/bigint.h"

struct my_bigint *my_bigint_neg(struct my_bigint *self)
{
    self->is_negative = !self->is_negative;
    return self;
}
