/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Frees a bigint
*/

#include "my/bigint.h"
#include <stdlib.h>

void my_bigint_free(struct my_bigint *num)
{
    free(num->number);
    free(num);
}
