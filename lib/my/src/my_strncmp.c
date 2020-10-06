/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Compares two strings, except it only compares at most n bytes
*/

#include "my.h"

int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    do {
        if (n <= 0)
            return (0);

        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);

        --n;
    } while (s1[i++]);

    return (0);
}
