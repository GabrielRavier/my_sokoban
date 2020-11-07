/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Duplicates a string, but only at most length bytes
*/

#include "my/string.h"
#include <stdlib.h>

char *my_strndup(const char *string, size_t length)
{
    const size_t string_length = my_strnlen(string, length);
    char *const duplicate_string = (char *)malloc(string_length + 1);

    if (duplicate_string == NULL)
        return (NULL);
    my_memcpy(duplicate_string, string, string_length);
    duplicate_string[string_length] = '\0';
    return (duplicate_string);
}
