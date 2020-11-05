/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"
#include <sys/types.h>
#include <limits.h>

static intmax_t get_arg(va_list arguments,
    struct my_printf_conversion_info *format_info)
{
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_CHAR)
        return (char)va_arg(arguments, int);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_SHORT)
        return (short)va_arg(arguments, int);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG)
        return va_arg(arguments, long);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG_LONG)
        return va_arg(arguments, long long);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_INTMAX)
        return va_arg(arguments, intmax_t);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_SIZE_T)
        return va_arg(arguments, ssize_t);
    return va_arg(arguments, int);
}

// Note: The cast to uintptr_t (done explicitly here for clarity) will handle
// the issue of INTMAX_MIN, since casting that to uintptr_t on 2s complement
// (now mandatory in C2x) will result in the corresponding unsigned value
struct my_string *asprintf_format_signed_integer(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    intmax_t signed_argument = get_arg(arguments, format_info);
    struct my_string *prefix = NULL;

    if (signed_argument < 0) {
        prefix = my_string_new_from_string("-", 1);
        if (signed_argument != INTMAX_MIN)
            signed_argument = -signed_argument;
    }
    asprintf_append_number_base(destination, (uintmax_t)signed_argument, 10,
        false);
    return prefix;
}


