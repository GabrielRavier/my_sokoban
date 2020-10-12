/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Writes c to stdout
*/

#include "my.h"
#include <unistd.h>

void my_putchar(int character)
{
    my_dputc(character, STDOUT_FILENO);
}
