/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Fill memory with a byte
*/

#include "my/string.h"

void *my_memset(void *destination, int character, size_t length)
{
    unsigned char *char_destination = (unsigned char *)destination;

    while (length--)
        *char_destination++ = (unsigned char)character;
    return (destination);
}
