/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_pointer
*/

#include "my/internal/printf/formatter.h"

struct my_string *asprintf_format_pointer(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info)
{
    const uintptr_t argument = (uintptr_t)va_arg(*arguments, void *);
    struct my_string *prefix = NULL;

    (void)format_info;
    if (argument) {
        prefix = my_string_new_from_string("0x", 2);
        asprintf_append_number_base(destination, argument, 16, false);
    } else
        my_string_append(destination, "(nil)", 5);
    return (prefix);
}
