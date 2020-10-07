/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Writes the strings and a trailing newline to stdout
*/

#include "my.h"

int my_puts(const char *string)
{
    my_putstr(string);
    my_putchar('\n');
    return 0;
}
