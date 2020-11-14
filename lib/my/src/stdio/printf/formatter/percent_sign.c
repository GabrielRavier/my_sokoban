/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements vasprintf_format_percent_sign
*/

#include "my/internal/printf/formatter.h"

// We set the field width to 0 to conform to glibc behaviour and not respect the
// field width on percent signs
struct my_string *asprintf_format_percent_sign(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info)
{
    (void)arguments;
    (void)format_info;
    my_string_append_char(destination, '%');
    format_info->field_width = 0;
    return (NULL);
}
