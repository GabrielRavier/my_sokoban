/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Writes the string s to fd (without its null terminator)
*/

#include "my/stdio.h"
#include "my/string.h"
#include <unistd.h>
#include <stdio.h>

int my_dputs(const char *string, int fd)
{
    const size_t string_len = my_strlen(string);

    if (string_len == 0)
        return (0);
    if ((size_t)write(fd, string, string_len) != string_len)
        return (EOF);
    return (0);
}
