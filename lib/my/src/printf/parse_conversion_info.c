/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements parse_conversion_info
*/

#include "my/internal/printf/parse_conversion_info.h"
#include "my/string.h"
#include "my/ctype.h"

#define MAKE_FLAG_CASE(character, info_field_to_set) \
    case character:                                  \
        conversion_info->info_field_to_set = true
#define DO_MODIFIER(modifier_string, modifier_value)                \
    do {                                                            \
        if (parse_single_length_modifier(conversion_info, to_parse, \
            modifier_string, PRINTF_LENGTH_MODIFIER_CHAR))          \
            return;                                                 \
    } while (0)


void parse_printf_flags(struct my_printf_conversion_info *conversion_info,
    const char **to_parse)
{
    while (1) {
        switch (**to_parse) {
            MAKE_FLAG_CASE('-', flag_minus);
            break;
            MAKE_FLAG_CASE('+', flag_plus);
            break;
            MAKE_FLAG_CASE(' ', flag_space);
            break;
            MAKE_FLAG_CASE('#', flag_hash);
            break;
            MAKE_FLAG_CASE('0', flag_0);
            break;
        default:
            return;
        }
        ++*to_parse;
    }
}

void parse_printf_field_width(
    struct my_printf_conversion_info *conversion_info, const char **to_parse,
    va_list arguments)
{
    if (**to_parse == '*') {
        conversion_info->field_width = va_arg(arguments, int);
        ++*to_parse;
    }
    else {
        conversion_info->field_width = 0;
        while (my_isdigit(**to_parse))
            conversion_info->field_width = conversion_info->field_width * 10
                + (*((*to_parse)++) - '0');
    }
}

void parse_printf_precision(struct my_printf_conversion_info *conversion_info,
    const char **to_parse, va_list arguments)
{
    if (**to_parse == '.') {
        if (*++*to_parse == '*') {
            conversion_info->precision = va_arg(arguments, int);
            ++*to_parse;
        }
        else {
            conversion_info->precision = 0;
            while (my_isdigit(**to_parse))
                conversion_info->precision = conversion_info->precision * 10
                    + (*((*to_parse)++) - '0');
        }
    }
    else
        conversion_info->precision = -1;
}

static bool parse_single_length_modifier(
    struct my_printf_conversion_info *conversion_info, const char **to_parse,
    const char *length_modifier_string, int length_modifier_value)
{
    size_t length_modifier_string_length = my_strlen(length_modifier_string);

    if (my_strncmp(length_modifier_string, *to_parse,
        length_modifier_string_length) == 0) {
        conversion_info->length_modifier = length_modifier_value;
        *to_parse += length_modifier_string_length;
        return (true);
    }
    return (false);
}

void parse_printf_length_modifier(
    struct my_printf_conversion_info *conversion_info, const char **to_parse)
{
    DO_MODIFIER("hh", PRINTF_LENGTH_MODIFIER_CHAR);
    DO_MODIFIER("h", PRINTF_LENGTH_MODIFIER_SHORT);
    DO_MODIFIER("l", PRINTF_LENGTH_MODIFIER_LONG);
    DO_MODIFIER("ll", PRINTF_LENGTH_MODIFIER_LONG_LONG);
    DO_MODIFIER("j", PRINTF_LENGTH_MODIFIER_INTMAX);
    DO_MODIFIER("z", PRINTF_LENGTH_MODIFIER_SIZE_T);
    DO_MODIFIER("t", PRINTF_LENGTH_MODIFIER_PTRDIFF_T);
    DO_MODIFIER("L", PRINTF_LENGTH_MODIFIER_LONG_LONG);
    DO_MODIFIER("H", PRINTF_LENGTH_MODIFIER_DECIMAL32);
    DO_MODIFIER("D", PRINTF_LENGTH_MODIFIER_DECIMAL64);
    DO_MODIFIER("DD", PRINTF_LENGTH_MODIFIER_DECIMAL128);
}
