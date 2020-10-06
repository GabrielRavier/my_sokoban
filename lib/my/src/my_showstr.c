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
            if (str[i] < 0x10)
                my_putchar('0');
            my_putnbr_base(str[i], "0123456789abcdef");
        }

    return (0);
}
