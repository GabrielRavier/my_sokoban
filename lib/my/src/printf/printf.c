/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_printf
*/

#include "my/stdio.h"

int my_printf(const char *format, ...)
{
    va_list arguments;
    int result;

    va_start(arguments, format);
    result = my_vprintf(format, arguments);
    va_end(arguments);
    return (result);
}
