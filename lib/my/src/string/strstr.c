/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Find the first occurence of needle in haystack
*/

#include "my/string.h"
#include <stddef.h>

// Does strstr, with some basic optimizations such as starting with a search for
// the first character of needle in haystack
// Note: we use strncmp so that we don't need to match the null terminator of
// needle when searching for it in haystack
char *my_strstr(const char *haystack, const char *needle)
{
    const char needle_first_character = *needle++;
    char haystack_current_character;
    size_t needle_length;

    if (needle_first_character != '\0') {
        needle_length = my_strlen(needle);
        do {
            do {
                haystack_current_character = *haystack++;
                if (haystack_current_character == '\0')
                    return (NULL);
            } while (haystack_current_character != needle_first_character);
        } while (my_strncmp(haystack, needle, needle_length) != 0);
        --haystack;
    }
    return ((char *)(haystack));
}
