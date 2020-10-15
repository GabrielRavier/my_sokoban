/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Prints a bigint on the given fd
*/

#include "my_bigint.h"
#include "my.h"
#include <unistd.h>

void my_bigint_dprint(int fd, const struct my_bigint *num)
{
    if (num->is_negative)
        my_dputc('-', fd);

    for (size_t i = num->num_digits; i != 0; --i) {
        my_dputc('0' + num->number[i - 1], fd);
    }
}
