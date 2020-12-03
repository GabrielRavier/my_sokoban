/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements parse_conversion_info
*/

#include "my/internal/printf/parse_conversion_info.h"
#include "my/string.h"
#include "my/ctype.h"

void parse_printf_flags(struct my_printf_conversion_info *conversion_info,
    const char **to_parse)
{
    while (1) {
        switch (**to_parse) {
            INTERNAL_MAKE_FLAG_CASE('-', flag_minus);
            break;
            INTERNAL_MAKE_FLAG_CASE('+', flag_plus);
            break;
            INTERNAL_MAKE_FLAG_CASE(' ', flag_space);
            break;
            INTERNAL_MAKE_FLAG_CASE('#', flag_hash);
            break;
            INTERNAL_MAKE_FLAG_CASE('0', flag_0);
            break;
        default:
            return;
        }
        ++*to_parse;
    }
}

bool parse_printf_field_width(struct my_printf_conversion_info *conversion_info,
    const char **to_parse, va_list *arguments)
{
    if (**to_parse == '*') {
        conversion_info->field_width = va_arg(*arguments, int);
        if (conversion_info->field_width < 0) {
            conversion_info->flag_minus = true;
            conversion_info->field_width = -conversion_info->field_width;
        }
        ++*to_parse;
    } else {
        conversion_info->field_width =
            my_isdigit(**to_parse) ? asprintf_parse_int(to_parse) : 0;
        return conversion_info->field_width >= 0;
    }
    return (true);
}

// We put the check for a negative precision from va_arg below the else to
// respect the norm rule on having less than 3 nested branchings
bool parse_printf_precision(struct my_printf_conversion_info *conversion_info,
    const char **to_parse, va_list *arguments)
{
    if (**to_parse == '.') {
        if (*++*to_parse == '*') {
            conversion_info->precision = va_arg(*arguments, int);
            ++*to_parse;
        } else {
            conversion_info->precision =
                my_isdigit(**to_parse) ? asprintf_parse_int(to_parse) : 0;
            return conversion_info->precision >= 0;
        }
        if (conversion_info->precision < 0)
            conversion_info->precision = -1;
    } else
        conversion_info->precision = -1;
    return (true);
}

static bool parse_single_length_modifier(
    struct my_printf_conversion_info *conversion_info, const char **to_parse,
    const char *length_modifier_string, int length_modifier_value)
{
    const size_t length_modifier_string_length =
        my_strlen(length_modifier_string);

    if (my_strncmp(length_modifier_string, *to_parse,
            length_modifier_string_length) == 0) {
        conversion_info->length_modifier = length_modifier_value;
        *to_parse += length_modifier_string_length;
        return (true);
    }
    return (false);
}

// We place hh before h and ll before l because otherwise the
// smaller substrings would match
void parse_printf_length_modifier(
    struct my_printf_conversion_info *conversion_info, const char **to_parse)
{
    INTERNAL_DO_MODIFIER("hh", PRINTF_LENGTH_MODIFIER_CHAR);
    INTERNAL_DO_MODIFIER("h", PRINTF_LENGTH_MODIFIER_SHORT);
    INTERNAL_DO_MODIFIER("ll", PRINTF_LENGTH_MODIFIER_LONG_LONG);
    INTERNAL_DO_MODIFIER("q", PRINTF_LENGTH_MODIFIER_LONG_LONG);
    INTERNAL_DO_MODIFIER("l", PRINTF_LENGTH_MODIFIER_LONG);
    INTERNAL_DO_MODIFIER("j", PRINTF_LENGTH_MODIFIER_INTMAX);
    INTERNAL_DO_MODIFIER("z", PRINTF_LENGTH_MODIFIER_SIZE_T);
    INTERNAL_DO_MODIFIER("Z", PRINTF_LENGTH_MODIFIER_SIZE_T);
    INTERNAL_DO_MODIFIER("t", PRINTF_LENGTH_MODIFIER_PTRDIFF_T);
    INTERNAL_DO_MODIFIER("L", PRINTF_LENGTH_MODIFIER_LONG_LONG);
}
