/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"

void asprintf_format_unsigned_integer(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    uintptr_t unsigned_argument = va_arg(arguments, unsigned);
    int base = (format_info->conversion_specifier == 'b' ? 2 :
        (format_info->conversion_specifier == 'o' ? 8 :
        ((format_info->conversion_specifier == 'x' ||
            format_info->conversion_specifier == 'X') ? 16 : 10)));

    if (format_info->flag_hash && base == 16 && unsigned_argument) {
        my_string_append_char(destination, '0');
        my_string_append_char(destination, format_info->conversion_specifier);
    }
    asprintf_append_number_base(destination, unsigned_argument, base,
        format_info->conversion_specifier == 'X');
}
