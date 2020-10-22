/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Calculates the length of a string (excluding the terminating null byte)
*/

#include "my/string.h"

size_t my_strlen(char const *str)
{
    size_t result = 0;

    while (*str++ != '\0')
        ++result;
    return (result);
}
