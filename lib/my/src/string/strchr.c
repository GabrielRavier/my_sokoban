/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Return a pointer to the find occurence of the character in the passed string
*/

#include "my/string.h"
#include <stddef.h>

#pragma GCC diagnostic ignored "-Wcast-qual"

char *my_strchr(const char *str, int character)
{
    do {
        if (*str == character)
            return ((char *)str);
    } while ((*str++) != '\0');
    return (NULL);
}
