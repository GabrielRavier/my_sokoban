/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements append_number_base
*/

#include "my/internal/printf/formatter.h"
#include <assert.h>
#include <limits.h>

static_assert(LONG_MAX > INT_MAX, "Need long that is bigger than int");

void asprintf_append_number_base(struct my_string *destination, long number,
    int base, bool is_uppercase)
{
    long tmp;

    if (number < 0) {
        my_string_append_char(destination, '-');
        number = -number;
    }
    tmp = number / base;
    if (tmp != 0)
        asprintf_append_number_base(destination, tmp, base, is_uppercase);
    my_string_append_char(destination, (is_uppercase ? "0123456789ABCDEF" : "0123456789abcdef")[number % base]);
}
