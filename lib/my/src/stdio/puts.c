/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines puts
*/

#include "my/stdio.h"
#include <stdio.h>
#include <unistd.h>

int my_puts(const char *string)
{
    if ((my_dputs(string, STDOUT_FILENO) == EOF) || my_putchar('\n') == EOF)
        return (EOF);
    return (0);
}
