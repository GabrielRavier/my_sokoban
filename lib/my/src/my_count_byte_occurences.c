/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Counts the amount of times a byte appears between two pointers
*/

#include "my/misc.h"
#include <stddef.h>

size_t my_count_byte_occurences(const char *first, const char *last,
    char character)
{
    size_t result = 0;

    while (first != last) {
        if (*first == character)
            ++result;
        ++first;
    }
    return (result);
}
