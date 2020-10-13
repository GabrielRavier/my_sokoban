/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Prints a character on the specified file descriptor
*/

#include "my.h"
#include <unistd.h>

void my_dputc(int character, int fd)
{
    unsigned char character_as_char = (unsigned char)character;
    write(fd, &character_as_char, sizeof(character_as_char));
}