/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines my_vdprintf
*/

#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"

int my_vdprintf(int fd, const char *format, va_list arguments)
{
    char *string_to_print;
    const int string_length = my_vasprintf(&string_to_print, format, arguments);
    int result;

    if (string_length < 0)
        return (-1);
    result = (int)my_write(fd, string_to_print, (size_t)string_length);
    my_free(string_to_print);
    return (result);
}
