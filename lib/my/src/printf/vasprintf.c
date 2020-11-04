/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_vasprintf
*/

#include "my/stdio.h"
#include "my/internal/printf/formatter.h"
#include "my/my_string.h"
#include "my/string.h"
#include "my/ctype.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

static const formatter_func_t formatting_functions[UCHAR_MAX] = {
    ['d'] = &asprintf_format_integer,
    ['i'] = &asprintf_format_integer,
    ['b'] = &asprintf_format_integer,
    ['o'] = &asprintf_format_integer,
    ['u'] = &asprintf_format_integer,
    ['x'] = &asprintf_format_integer,
    ['X'] = &asprintf_format_integer,
    ['c'] = &asprintf_format_char,
    ['s'] = &asprintf_format_cstring,
    ['S'] = &asprintf_format_cstring,
};

// Returns the next character after the conversion specifier.
static const char *do_conversion_specification(struct my_string *destination,
    const char *conversion_specification, va_list arguments)
{
    struct my_printf_conversion_info conversion_info = { 0 };

    parse_printf_flags(&conversion_info, &conversion_specification);
    parse_printf_field_width(&conversion_info, &conversion_specification,
        arguments);
    parse_printf_precision(&conversion_info, &conversion_specification,
        arguments);
    parse_printf_length_modifier(&conversion_info, &conversion_specification);
    conversion_info.conversion_specifier = *conversion_specification++;
    if (formatting_functions[
            (unsigned char)conversion_info.conversion_specifier] != NULL)
        formatting_functions[
            (unsigned char)conversion_info.conversion_specifier](destination,
            arguments, &conversion_info);
    return conversion_specification;
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
    return (int)resulting_length;
}
