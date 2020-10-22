/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compares two strings, except it only compares at most n bytes
*/

#include "my/string.h"

int my_strncmp(const char *string1, const char *string2, size_t n)
{
    int i = 0;

    do {
        if (n == 0)
            return (0);
        if (string1[i] != string2[i])
            return (string1[i] - string2[i]);
        --n;
    } while (string1[i++]);
    return (0);
}
