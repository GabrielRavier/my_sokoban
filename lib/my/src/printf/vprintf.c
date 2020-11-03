/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_vprintf
*/

#include "my/stdio.h"
#include <unistd.h>

int my_vprintf(const char *format, va_list arguments)
{
    return my_vdprintf(STDOUT_FILENO, format, arguments);
}
