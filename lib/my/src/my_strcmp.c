/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compare two strings
*/

#include "my/string.h"

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    do {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    } while (s1[i++]);

    return (0);
}
