/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Prints a string (including non-printable characters) and returns 0
*/

#include "my.h"
#include <stddef.h>

int my_showstr(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; ++i)
        if (my_isprint(str[i]))
            my_putchar(str[i]);
        else {
            my_putchar('\\');
            my_putchar("0123456789abcdef"[((unsigned char)str[i] / 16) % 16]);
            my_putchar("0123456789abcdef"[(unsigned char)str[i] % 16]);
        }

    return (0);
}
