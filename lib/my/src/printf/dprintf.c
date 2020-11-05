/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_dprintf
*/

#include "my/stdio.h"

int my_dprintf(int fd, const char *format, ...)
{
    va_list arguments;
    int result;

    va_start(arguments, format);
    result = my_vdprintf(fd, format, arguments);
    va_end(arguments);
    return (result);
}
