/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strncat
*/

#include "my/string.h"
#include <stdbool.h>

char *my_strncat(char *destination, const char *source, size_t n)
{
    char *const result = destination;
    char current_character;

    destination += my_strlen(destination);
    while (true) {
        current_character = *source++;
        *destination++ = current_character;
        if (current_character == '\0')
            break;
        if (n-- == 0) {
            destination[-1] = '\0';
            break;
        }
    }
    return (result);
}
