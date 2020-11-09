/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Duplicates a string
*/

#include "my/string.h"
#include <stdlib.h>
#include <stddef.h>

char *my_strdup(const char *string)
{
    const size_t string_length = my_strlen(string) + 1;
    void *const duplicate_string = malloc(string_length);

    if (!duplicate_string)
        return (NULL);
    my_memcpy(duplicate_string, string, string_length);
    return ((char *)duplicate_string);
}
