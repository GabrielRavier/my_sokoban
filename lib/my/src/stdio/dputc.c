/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines dputc
*/

#include "my/stdio.h"
#include <unistd.h>
#include <stdio.h>

int my_dputc(int character, int fd)
{
    const unsigned char character_as_char = (unsigned char)character;

    if (write(fd, &character_as_char, sizeof(character_as_char)) !=
        sizeof(character_as_char))
        return (EOF);
    return ((int)character_as_char);
}
