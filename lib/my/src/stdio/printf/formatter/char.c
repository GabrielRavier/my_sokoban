/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements vasprintf_format_char
*/

#include "my/internal/printf/formatter.h"
#include <wchar.h>
#include <sys/types.h>

struct my_string *asprintf_format_char(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info)
{
    char buffer[4];

    if (format_info->length_modifier != PRINTF_LENGTH_MODIFIER_LONG &&
        format_info->length_modifier != PRINTF_LENGTH_MODIFIER_LONG_LONG &&
        format_info->conversion_specifier != 'C')
        my_string_append_char(destination, va_arg(*arguments, int));
    else
        my_string_append(destination, buffer,
            asprintf_utf32_char_to_utf8(buffer, va_arg(*arguments, wint_t)));
    return (NULL);
}
