/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_memmove
*/

#include "my/string.h"

void *my_memmove(void *destination, const void *source, size_t size)
{
    unsigned char *char_destination = (unsigned char *)destination;
    const unsigned char *char_source = (const unsigned char *)source;

    if (char_destination < char_source)
        while (size--)
            *char_destination++ = *char_source++;
    else {
        char_destination += size;
        char_source += size;
        while (size--)
            *--char_destination = *--char_source;
    }
    return destination;
}
