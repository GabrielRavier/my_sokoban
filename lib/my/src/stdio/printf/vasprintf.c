/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_vasprintf
*/

#include "my/stdio.h"
#include "my/internal/printf/formatter.h"
#include "my/internal/printf/parse_conversion_info.h"
#include "my/internal/printf/padding.h"
#include "my/internal/printf/handle_invalid.h"
#include "my/my_string.h"
#include "my/string.h"
#include "my/ctype.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

static const formatter_func_t formatter_functions[UCHAR_MAX] = {
    ['d'] = &asprintf_format_signed_integer,
    ['i'] = &asprintf_format_signed_integer,
    ['b'] = &asprintf_format_unsigned_integer,
    ['o'] = &asprintf_format_unsigned_integer,
    ['u'] = &asprintf_format_unsigned_integer,
    ['x'] = &asprintf_format_unsigned_integer,
    ['X'] = &asprintf_format_unsigned_integer,
    ['c'] = &asprintf_format_char,
    ['s'] = &asprintf_format_cstring,
    ['S'] = &asprintf_format_cstring,
#ifdef LIBMY_FLOATING_POINT_CLUDGE
    ['f'] = &asprintf_format_decimal_float,
    ['F'] = &asprintf_format_decimal_float,
    ['e'] = &asprintf_format_decimal_float,
    ['E'] = &asprintf_format_decimal_float,
    ['g'] = &asprintf_format_decimal_float,
    ['G'] = &asprintf_format_decimal_float,
    ['a'] = &asprintf_format_decimal_float,
    ['A'] = &asprintf_format_decimal_float,
#endif
    ['%'] = &asprintf_format_percent_sign,
    ['p'] = &asprintf_format_pointer,
    ['C'] = &asprintf_format_char,
    ['n'] = &asprintf_format_n
};

MY_ATTR_WARN_UNUSED_RESULT static bool parse_format(
    struct my_printf_conversion_info *conversion_info,
    const char **conversion_specification, va_list *arguments)
{
    parse_printf_flags(conversion_info, conversion_specification);
    if (!parse_printf_field_width(conversion_info, conversion_specification,
        arguments))
        return (false);
    if (!parse_printf_precision(conversion_info, conversion_specification,
        arguments))
        return (false);
    parse_printf_length_modifier(conversion_info, conversion_specification);
    conversion_info->conversion_specifier = *((*conversion_specification)++);
    return (true);
}

// Returns the next character after the conversion specifier.
MY_ATTR_WARN_UNUSED_RESULT static const char *do_conversion_specification(
    struct my_string *destination, const char *conversion_specification,
    va_list *arguments, bool *has_encountered_invalid)
{
    struct my_printf_conversion_info conversion_info = { 0 };
    const size_t destination_length_before_conversion = destination->length;
    formatter_func_t formatter_function;

    if (!parse_format(&conversion_info, &conversion_specification, arguments))
        return (NULL);
    formatter_function = formatter_functions[
        (unsigned char)conversion_info.conversion_specifier];
    if (formatter_function != NULL)
        asprintf_do_padding(&((struct asprintf_do_padding_params){destination,
            destination_length_before_conversion, formatter_function(
                destination, arguments, &conversion_info),
            &conversion_info, formatter_function}));
    else
        return (asprintf_handle_invalid(destination, &conversion_info,
            has_encountered_invalid) ? (conversion_specification -
            (conversion_info.conversion_specifier == '\0')) : NULL);
    return (conversion_specification);
}

// has_encountered_invalid is related to extremely weird behaviour from glibc.
// If glibc's printf encounters a '\0' as a conversion specifier, it will
// return, *unless* it had already encountered an erroneous conversion
// specifier, in which case it will continue as normal
static bool do_my_string_printf(struct my_string *destination,
    const char *format, va_list *arguments)
{
    char current_char;
    bool has_encountered_invalid = false;

    while (1) {
        while (1) {
            current_char = *format++;
            if (current_char == '%')
                break;
            if (current_char == '\0')
                return (true);
            my_string_append_char(destination, current_char);
        }
        format = do_conversion_specification(destination, format, arguments,
            &has_encountered_invalid);
        if (!format)
            return (false);
    }
}

// We use a local copy of the arguments list and va_copy due to the fact that
// va_list may or may not be an array type, which fucks up the address-of
// operator unless we use a local copy
int my_vasprintf(char **result_string_ptr, const char *format,
    va_list arguments)
{
    struct my_string *result = my_string_new();
    size_t resulting_length;
    va_list local_arguments_copy;

    va_copy(local_arguments_copy, arguments);
    if (!do_my_string_printf(result, format, &local_arguments_copy)) {
        my_string_free(result);
        va_end(local_arguments_copy);
        return (-1);
    }
    *result_string_ptr = result->string;
    resulting_length = result->length;
    free(result);
    va_end(local_arguments_copy);
    return ((int)resulting_length);
}
