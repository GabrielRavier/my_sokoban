/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Copies the string pointed to by src to the buffer pointed to by dest
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
