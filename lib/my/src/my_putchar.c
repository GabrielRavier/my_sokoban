/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar - Day 07
** File description:
** Writes c to stdout
*/

#include "my.h"
#include <unistd.h>

void my_putchar(char character)
{
    write(STDOUT_FILENO, &character, sizeof(character));
}
