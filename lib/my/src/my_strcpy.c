/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Copies the string pointed to by src to the buffer pointed to by dest
*/

#include "my.h"

char *my_strcpy(char *dest, const char *src)
{
    char *result = dest;
    char tmp;

    do {
        tmp = *src++;
        *dest++ = tmp;
    } while (tmp);

    return (result);
}
