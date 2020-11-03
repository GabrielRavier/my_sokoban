/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_vasprintf
*/

#include "my/stdio.h"
#include "my/my_string.h"
#include "my/string.h"
#include "my/ctype.h"
#include <stdlib.h>
#include <limits.h>

static void append_number_base(struct my_string *result, unsigned number,
    unsigned base)
{
    int tmp = number / base;

    if (tmp != 0)
        append_number_base(result, tmp, base);
    my_string_append_char(result, '0' + number % base);
}

static void do_my_string_printf(struct my_string *result, const char *format,
    va_list arguments)
{
    char current_character;
    int int_argument;
    unsigned unsigned_argument;
    const char *string_argument;

    while (1) {
        while (1) {
            current_character = *format++;
            if (current_character == '%')
                break;
            if (current_character == '\0')
                return;
            my_string_append_char(result, current_character);
        }
        current_character = *format++;
        switch (current_character) {
        case 'd':
        case 'o':
            int_argument = va_arg(arguments, int);
            if (int_argument < 0) {
                if (int_argument != INT_MAX)
                    int_argument = -int_argument;
                my_string_append_char(result, '-');
            }
            append_number_base(result, (unsigned)int_argument,
                               current_character == 'o' ? 8 : 10);
            break;

        case 'b':
            unsigned_argument = va_arg(arguments, unsigned);
            append_number_base(result, unsigned_argument, 2);
            break;

        case 'c':
            my_string_append_char(result, va_arg(arguments, int));
            break;

        case 's':
        case 'S':
            string_argument = va_arg(arguments, const char *);
            if (current_character == 's')
                my_string_append(result, string_argument,
                    my_strlen(string_argument));
            else {
                for (size_t i = 0; string_argument[i] != '\0'; ++i)
                    if (my_isprint(string_argument[i]))
                        my_string_append_char(result, string_argument[i]);
                    else {
                        my_string_append_char(result, '\\');
                        append_number_base(result,
                            (unsigned char)string_argument[i], 8);
                    }
            }
            break;
        }
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
