/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Determines the length of a fixed-size string
*/

#include "my/string.h"

size_t my_strnlen(const char *string, size_t max_length)
{
    const char *const memchr_result =
        (const char *)my_memchr(string, '\0', max_length);

    if (memchr_result == NULL)
        return (max_length);
    return (size_t)(memchr_result - string);
}
