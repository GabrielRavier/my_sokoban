/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements vasprintf_format_cstring
*/

#include "my/internal/printf/formatter.h"
#include "my/string.h"
#include "my/ctype.h"

void asprintf_format_cstring(struct my_string *destination, va_list arguments,
    const struct my_printf_conversion_info *format_info)
{
    const char *string_argument = va_arg(arguments, const char *);
    if (format_info->conversion_specifier == 's')
        my_string_append(destination, string_argument,
                         my_strlen(string_argument));
    else {
        for (size_t i = 0; string_argument[i] != '\0'; ++i)
            if (my_isprint(string_argument[i]))
                my_string_append_char(destination, string_argument[i]);
            else {
                my_string_append_char(destination, '\\');
                asprintf_append_number_base(destination,
                    (unsigned char)string_argument[i], 8, false);
            }
    }
}
