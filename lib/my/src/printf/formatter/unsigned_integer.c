/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"

// We assume size_t is the unsigned counterpart to ptrdiff_t, which seems
// reasonable to me
static intmax_t get_arg(va_list arguments,
    struct my_printf_conversion_info *format_info)
{
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_CHAR)
        return (unsigned char)va_arg(arguments, unsigned int);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_SHORT)
        return (unsigned short)va_arg(arguments, unsigned int);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG)
        return va_arg(arguments, unsigned long);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG_LONG)
        return va_arg(arguments, unsigned long long);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_INTMAX)
        return va_arg(arguments, uintmax_t);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_SIZE_T)
        return va_arg(arguments, size_t);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_PTRDIFF_T)
        return va_arg(arguments, size_t);
    return va_arg(arguments, unsigned int);
}

static void do_precision(struct my_string *destination, size_t pos_before,
    struct my_printf_conversion_info *format_info)
{
    format_info->precision -= (destination->length - pos_before);
    while (format_info->precision-- > 0)
        my_string_insert_char(destination, '0', pos_before);
}

static int base_from_specifier(char conversion_specifier)
{
    return (conversion_specifier == 'b' ? 2 :
        (conversion_specifier == 'o' ? 8 :
        ((conversion_specifier == 'x' ||
            conversion_specifier == 'X') ? 16 : 10)));
}

struct my_string *asprintf_format_unsigned_integer(
    struct my_string *destination, va_list arguments,
    struct my_printf_conversion_info *format_info)
{
    uintptr_t unsigned_argument = get_arg(arguments, format_info);
    int base = base_from_specifier(format_info->conversion_specifier);
    struct my_string *prefix = NULL;
    size_t pos_before = destination->length;

    if (format_info->precision == -1 || (format_info->flag_hash &&
        format_info->precision == 0))
        format_info->precision = 1;
    if (format_info->flag_hash && (base == 16 || base == 8) &&
        unsigned_argument) {
        prefix = my_string_new_from_string("0", 1);
        if (base == 16)
            my_string_append_char(prefix,
                format_info->conversion_specifier);
    }
    if (unsigned_argument)
        asprintf_append_number_base(destination, unsigned_argument, base,
            format_info->conversion_specifier == 'X');
    do_precision(destination, pos_before, format_info);
    return prefix;
}
