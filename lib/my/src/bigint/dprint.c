/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Prints a bigint on the given fd
*/

#include "my/bigint.h"
#include "my/stdio.h"
#include <unistd.h>
#include <stdio.h>

static bool is_not_zero(const struct my_bigint *num)
{
    return (num->number->length > 0 && !(num->number->length == 1 && num->number->string[0] != 0));
}

bool my_bigint_dprint(int fd, const struct my_bigint *num)
{
    if (num->is_negative && is_not_zero(num))
        if (my_dputc('-', fd) == EOF)
            return (false);
    for (size_t i = num->number->length; i != 0; --i) {
        if (my_dputc('0' + num->number->string[i - 1], fd) == EOF)
            return (false);
    }
    return (true);
}
