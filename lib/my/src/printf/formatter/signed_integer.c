/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"
#include "my/internal/printf/parse_conversion_info.h"
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
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_PTRDIFF_T)
        return va_arg(arguments, ptrdiff_t);
    return va_arg(arguments, int);
}

static void do_precision(struct my_string *destination, size_t pos_before,
    struct my_printf_conversion_info *format_info)
{
    format_info->precision -= (destination->length - pos_before);
    while (format_info->precision-- > 0)
        my_string_insert_char(destination, '0', pos_before);
}

// Note: The cast to uintptr_t (done explicitly here for clarity) will handle
// the issue of INTMAX_MIN, since casting that to uintptr_t on 2s complement
// (now mandatory in C2x) will result in the corresponding unsigned value
struct my_string *asprintf_format_signed_integer(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    intmax_t signed_argument = get_arg(arguments, format_info);
    struct my_string *prefix = NULL;
    size_t pos_before = destination->length;

    if (format_info->precision == -1)
        format_info->precision = 1;
    if (signed_argument < 0) {
        prefix = my_string_new_from_string("-", 1);
        if (signed_argument != INTMAX_MIN)
            signed_argument = -signed_argument;
    }
    else if (format_info->flag_plus || format_info->flag_space)
        prefix = my_string_new_from_string(format_info->flag_plus ? "+" : " ",
            1);
    if (signed_argument)
        asprintf_append_number_base(destination, (uintmax_t)signed_argument, 10,
            false);
    do_precision(destination, pos_before, format_info);
    return prefix;
}


