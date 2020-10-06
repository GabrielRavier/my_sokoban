/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Writes c to stdout
*/

#include "my.h"
#include <unistd.h>

void my_putchar(char character)
{
    write(STDOUT_FILENO, &character, sizeof(character));
}
