/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines putchar
*/

#include "my/stdio.h"
#include <unistd.h>

int my_putchar(int character)
{
    return (my_putc(character, my_stdout));
}
