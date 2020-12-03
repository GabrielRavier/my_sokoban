/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_memmem
*/

#include "my/string.h"

void *my_memmem(const void *haystack, size_t haystack_length,
    const void *needle, size_t needle_length)
{
    const char *char_haystack = haystack;
    const char *char_needle = needle;

    if (needle_length == 0)
        return (void *)haystack;
    if (haystack_length < needle_length)
        return (NULL);
    if (needle_length == 1)
        return (my_memchr(haystack, *char_needle, haystack_length));
    for (const char *it = char_haystack;
        it <= (char_haystack + haystack_length - needle_length); ++it)
        if (it[0] == char_needle[0] &&
            my_memcmp(it, needle, needle_length) == 0)
            return (void *)(it);
    return (NULL);
}
