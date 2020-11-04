/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"
#include <limits.h>

void asprintf_format_signed_integer(struct my_string *destination,
    va_list arguments, const struct my_printf_conversion_info *format_info)
{
    int signed_argument = va_arg(arguments, int);

    if (signed_argument < 0) {
        my_string_append_char(destination, '-');
        if (signed_argument != INT_MAX)
            signed_argument = -signed_argument;
    }
    asprintf_append_number_base(destination, signed_argument, 10, false);
}


