/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Calculate the length of the initial segment of the string not including any
** bytes from reject
*/

#include "my/string.h"
#include <stddef.h>
#include <stdbool.h>

size_t my_strcspn(const char *str, const char *reject)
{
    size_t result = 0;
    char current_reject_character;
    char current_str_character;
    const char *reject_iterator;

    while (true) {
        current_str_character = *str++;
        if (current_str_character == '\0')
            return (result);
        reject_iterator = reject;
        do {
            current_reject_character = *reject_iterator++;
            if (current_reject_character == '\0')
                break;
        } while (current_reject_character != current_str_character);
        if (current_reject_character != '\0')
            return (result);
        ++result;
    }
}
