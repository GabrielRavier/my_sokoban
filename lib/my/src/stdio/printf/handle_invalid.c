/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_handle_invalid
*/

#include "my/internal/printf/handle_invalid.h"
#include "my/internal/printf/formatter.h"

// The else if are deliberate, we have to eliminate redundant flags as glibc
// also does so
static void stringisize_flags(struct my_string *destination,
    struct my_printf_conversion_info *conversion_info)
{
    if (conversion_info->flag_hash)
        my_string_append_char(destination, '#');
    if (conversion_info->flag_plus)
        my_string_append_char(destination, '+');
    else if (conversion_info->flag_space)
        my_string_append_char(destination, ' ');
    if (conversion_info->flag_minus)
        my_string_append_char(destination, '-');
    else if (conversion_info->flag_0)
        my_string_append_char(destination, '0');
}

bool asprintf_handle_invalid(struct my_string *destination,
    struct my_printf_conversion_info *conversion_info,
    bool *has_encountered_invalid)
{
    if (conversion_info->conversion_specifier == '\0' &&
        !*has_encountered_invalid)
        return (false);
    *has_encountered_invalid = true;
    my_string_append_char(destination, '%');
    stringisize_flags(destination, conversion_info);
    if (conversion_info->field_width != 0)
        asprintf_append_number_base(destination, conversion_info->field_width,
            10, false);
    if (conversion_info->precision != -1)
        asprintf_append_number_base(my_string_append_char(destination, '.'),
            conversion_info->precision, 10, false);
    if (conversion_info->conversion_specifier != '\0')
        my_string_append_char(destination,
            conversion_info->conversion_specifier);
    return (true);
}
