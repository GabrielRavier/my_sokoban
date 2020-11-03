/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_integer
*/

#include "my/internal/printf/formatter.h"

void asprintf_format_integer(struct my_string *destination, va_list arguments,
    char format_char)
{
    long integer_argument;

    if (format_char == 'd')
        integer_argument = va_arg(arguments, int);
    else
        integer_argument = va_arg(arguments, unsigned);
    asprintf_append_number_base(destination,
        integer_argument, (format_char == 'b' ? 2 : (format_char == 'o' ? 8 :
             (format_char == 'x' ? 16 : 10))));
}
