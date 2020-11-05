/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_vasprintf
*/

#include "my/internal/printf/parse_conversion_info.h"
#include "my/stdio.h"
#include "my/internal/printf/formatter.h"
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
    ['f'] = &asprintf_format_decimal_float,
    ['F'] = &asprintf_format_decimal_float,
    ['e'] = &asprintf_format_decimal_float,
    ['E'] = &asprintf_format_decimal_float,
    ['g'] = &asprintf_format_decimal_float,
    ['G'] = &asprintf_format_decimal_float,
    ['a'] = &asprintf_format_decimal_float,
    ['A'] = &asprintf_format_decimal_float,
    ['%'] = &asprintf_format_percent_sign,
};

static void do_padding_loop(struct my_string *destination,
    size_t destination_length_before_conversion, size_t converted_length,
    struct my_printf_conversion_info *conversion_info)
{
    while (converted_length++ < (size_t)conversion_info->field_width)
        if (conversion_info->flag_minus)
            my_string_append_char(destination, ' ');
        else
            my_string_insert_char(destination,
                conversion_info->flag_0 ? '0' : ' ',
                destination_length_before_conversion);
}

static void do_padding(struct my_string *destination,
    size_t destination_length_before_conversion,
    struct my_string *prefixed_string,
    struct my_printf_conversion_info *conversion_info)
{
    formatter_func_t formatting_func = formatter_functions[
        (unsigned char)conversion_info->conversion_specifier];
    size_t converted_length = destination->length -
        destination_length_before_conversion + (prefixed_string ?
            prefixed_string->length : 0);

    if (formatting_func != &asprintf_format_unsigned_integer &&
        formatting_func != &asprintf_format_signed_integer)
        conversion_info->flag_0 = false;
    if (!conversion_info->flag_0 && prefixed_string)
        my_string_insert(destination, prefixed_string->string,
            prefixed_string->length, destination_length_before_conversion);
    do_padding_loop(destination, destination_length_before_conversion,
        converted_length, conversion_info);
    if (conversion_info->flag_0 && prefixed_string)
        my_string_insert(destination, prefixed_string->string,
            prefixed_string->length, destination_length_before_conversion);
}

// Returns the next character after the conversion specifier.
static const char *do_conversion_specification(struct my_string *destination,
    const char *conversion_specification, va_list arguments)
{
    struct my_printf_conversion_info conversion_info = { 0 };
    size_t destination_length_before_conversion = destination->length;
    formatter_func_t formatter_function;

    parse_printf_flags(&conversion_info, &conversion_specification);
    parse_printf_field_width(&conversion_info, &conversion_specification,
        arguments);
    parse_printf_precision(&conversion_info, &conversion_specification,
        arguments);
    parse_printf_length_modifier(&conversion_info, &conversion_specification);
    conversion_info.conversion_specifier = *conversion_specification++;
    formatter_function = formatter_functions[
        (unsigned char)conversion_info.conversion_specifier];
    if (formatter_function != NULL)
        do_padding(destination, destination_length_before_conversion,
            formatter_function(destination, arguments, &conversion_info),
                &conversion_info);
    return (conversion_specification);
}

static void do_my_string_printf(struct my_string *destination,
    const char *format, va_list arguments)
{
    char current_char;

    while (1) {
        while (1) {
            current_char = *format++;
            if (current_char == '%')
                break;
            if (current_char == '\0')
                return;
            my_string_append_char(destination, current_char);
        }
        format = do_conversion_specification(destination, format, arguments);
    }
}

int my_vasprintf(char **result_string_ptr, const char *format,
    va_list arguments)
{
    struct my_string *result = my_string_new();
    size_t resulting_length;

    do_my_string_printf(result, format, arguments);
    *result_string_ptr = result->string;
    resulting_length = result->length;
    free(result);
    return ((int)resulting_length);
}
