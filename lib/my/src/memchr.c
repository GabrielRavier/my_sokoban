/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Scans memory for a character
*/

#include "my/string.h"

void *my_memchr(const void *ptr, int character, size_t length)
{
    const unsigned char *char_ptr = (const unsigned char *)ptr;

    while (length-- > 0) {
        if (*char_ptr == (unsigned char)character)
            return (void *)char_ptr;
        ++char_ptr;
    }
    return NULL;
}
