/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strncpy
*/

#include "my/string.h"

char *my_strncpy(char *destination, const char *source, size_t n)
{
    char *const result = destination;
    char current_character;

    for (size_t i = 0; i < n; ++i) {
        current_character = *source++;
        *destination++ = current_character;
        if (current_character == '\0') {
            while (++i < n)
                *destination++ = '\0';
            return (result);
        }
    }
    return (result);
}
