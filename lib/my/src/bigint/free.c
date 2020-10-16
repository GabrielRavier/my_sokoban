/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Frees a bigint
*/

#include "my_bigint.h"
#include <stdlib.h>

void my_bigint_free(const struct my_bigint *num)
{
    free(num->number);
}
