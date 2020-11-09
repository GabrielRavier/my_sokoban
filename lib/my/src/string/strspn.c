/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Calculate the length of the initial segment of the string only including
** bytes from accept
*/

#include "my/string.h"
#include <stddef.h>
#include <stdbool.h>

size_t my_strspn(const char *str, const char *accept)
{
    size_t result = 0;
    const char *accept_iterator;
    char current_character;

    while (true) {
        current_character = *str++;
        if (current_character == '\0')
            break;
        for (accept_iterator = accept; *accept_iterator != '\0';
            ++accept_iterator)
            if (current_character == *accept_iterator)
                break;
        if (*accept_iterator == '\0')
            break;
        ++result;
    }
    return (result);
}
