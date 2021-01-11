/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strcpy
*/

#include "my/string.h"

char *my_strcpy(char *destination, const char *source)
{
    char *const result = destination;
    char tmp;

    do {
        tmp = *source++;
        *destination++ = tmp;
    } while (tmp);
    return (result);
}
