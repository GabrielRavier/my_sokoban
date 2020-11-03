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

static const formatter_func_t formatting_functions[UCHAR_MAX] =
{
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

static void do_my_string_printf(struct my_string *destination, const char *format,
    va_list arguments)
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
        current_char = *format++;
        if (formatting_functions[(unsigned char)current_char] != NULL)
            formatting_functions[(unsigned char)current_char](destination,
                arguments, current_char);
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
