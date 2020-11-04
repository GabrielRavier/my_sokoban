/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"

void asprintf_format_unsigned_integer(struct my_string *destination, va_list arguments,
    const struct my_printf_conversion_info *format_info)
{
    unsigned unsigned_argument = va_arg(arguments, unsigned);

    asprintf_append_number_base(destination,
        unsigned_argument, (format_info->conversion_specifier == 'b' ? 2 :
            (format_info->conversion_specifier == 'o' ? 8 :
            ((format_info->conversion_specifier == 'x' ||
                format_info->conversion_specifier == 'X') ? 16 : 10))),
        format_info->conversion_specifier == 'X');
}
