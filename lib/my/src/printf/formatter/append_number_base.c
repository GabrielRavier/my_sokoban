/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements append_number_base
*/

#include "my/internal/printf/formatter.h"
#include <assert.h>
#include <limits.h>

void asprintf_append_number_base(struct my_string *destination,
    uintmax_t number, int base, bool is_uppercase)
{
    const uintmax_t tmp = number / base;
    if (tmp != 0)
        asprintf_append_number_base(destination, tmp, base, is_uppercase);
    my_string_append_char(destination,
        (is_uppercase ? "0123456789ABCDEF" :
            "0123456789abcdef")[number % base]);
}
