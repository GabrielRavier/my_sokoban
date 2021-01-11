/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strlen
*/

#include "my/string.h"

size_t my_strlen(char const *str)
{
    size_t result = 0;

    while (*str++ != '\0')
        ++result;
    return (result);
}
