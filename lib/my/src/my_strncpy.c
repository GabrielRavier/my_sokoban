/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Similar to strcpy, except that at most n bytes of src are copied. If there is
** no null byte among the first n bytes of src, the string placed in dest is not
** null-terminated. If the length of src is less than n, strncpy writes
** additional null bytes to dst to ensure a total of n bytes are written
*/

#include "my/string.h"

char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *result = dest;
    char current_character;

    for (size_t i = 0; i < n; ++i) {
        current_character = *src++;
        *dest++ = current_character;

        if (current_character == '\0') {
            while (++i < n)
                *dest++ = '\0';

            return (result);
        }
    }

    return (result);
}
