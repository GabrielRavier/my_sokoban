/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines memcpy
*/

#include "my/string.h"
#include <stddef.h>

void *my_memcpy(void *destination, const void *source, size_t size)
{
    unsigned char *char_destination = (unsigned char *)destination;
    const unsigned char *char_source = (const unsigned char *)source;

    while (size--)
        *char_destination++ = *char_source++;
    return (destination);
}
