/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compare two strings
*/

#include "my/string.h"

int my_strcmp(const char *string1, const char *string2)
{
    int i = 0;

    do {
        if (string1[i] != string2[i])
            return (string1[i] - string2[i]);
    } while (string1[i++]);
    return (0);
}
