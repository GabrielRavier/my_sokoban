/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"
#include <limits.h>

// Note: The cast to uintptr_t (done explicitly here for clarity) will handle
// the issue of INTMAX_MIN, since casting that to uintptr_t on 2s complement
// (now mandatory in C2x) will result in the corresponding unsigned value
void asprintf_format_signed_integer(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    intptr_t signed_argument = va_arg(arguments, int);

    if (signed_argument < 0) {
        my_string_append_char(destination, '-');
        if (signed_argument != INTMAX_MIN)
            signed_argument = -signed_argument;
    }
    asprintf_append_number_base(destination, (uintptr_t)signed_argument, 10,
        false);
}


