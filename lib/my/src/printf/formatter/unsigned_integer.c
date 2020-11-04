/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"

static intmax_t get_arg(va_list arguments,
    struct my_printf_conversion_info *format_info)
{
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG)
        return va_arg(arguments, unsigned long);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG_LONG)
        return va_arg(arguments, unsigned long long);
    return va_arg(arguments, unsigned);
}

void asprintf_format_unsigned_integer(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    uintptr_t unsigned_argument = get_arg(arguments, format_info);
    int base = (format_info->conversion_specifier == 'b' ? 2 :
        (format_info->conversion_specifier == 'o' ? 8 :
        ((format_info->conversion_specifier == 'x' ||
            format_info->conversion_specifier == 'X') ? 16 : 10)));

    if (format_info->flag_hash && (base == 16 || base == 8) && unsigned_argument) {
        my_string_append_char(destination, '0');
        if (base == 16)
            my_string_append_char(destination, format_info->conversion_specifier);
    }
    asprintf_append_number_base(destination, unsigned_argument, base,
        format_info->conversion_specifier == 'X');
}
