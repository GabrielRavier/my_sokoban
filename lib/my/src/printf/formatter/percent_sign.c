/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements vasprintf_format_percent_sign
*/

#include "my/internal/printf/formatter.h"

struct my_string *asprintf_format_percent_sign(struct my_string *destination, va_list arguments,
    struct my_printf_conversion_info *format_info)
{
    (void)arguments;
    (void)format_info;
    my_string_append_char(destination, '%');
    return (NULL);
}
