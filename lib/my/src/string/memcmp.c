/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_memcmp
*/

#include "my/string.h"

int my_memcmp(const void *s1, const void *s2, size_t length)
{
    const char *char_s1 = s1;
    const char *char_s2 = s2;

    for (size_t i = 0; i < length; ++i)
        if (char_s1[i] != char_s2[i])
            return (char_s1[i] - char_s2[i]);
    return (0);
}
