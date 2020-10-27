/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements assigning a bigint into another one
*/

#include "my/bigint.h"
#include "my/string.h"

void my_bigint_assign(struct my_bigint *destination, const struct my_bigint *source)
{
    my_string_assign(destination->number, source->number);
    destination->is_negative = source->is_negative;
}
