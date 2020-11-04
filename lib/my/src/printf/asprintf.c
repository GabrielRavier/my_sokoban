/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_asprintf
*/

#include "my/stdio.h"

int my_asprintf(char **result_string_ptr, const char *format, ...)
{
    va_list arguments;
    int result;

    va_start(arguments, format);
    result = my_vasprintf(result_string_ptr, format, arguments);
    va_end(arguments);
    return (result);
}
