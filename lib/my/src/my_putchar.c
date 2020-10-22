/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Writes c to stdout
*/

#include "my/stdio.h"
#include <unistd.h>

int my_putchar(int character)
{
    return (my_dputc(character, STDOUT_FILENO));
}
