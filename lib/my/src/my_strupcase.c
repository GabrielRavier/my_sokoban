/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Puts every letter in uppercase
*/

#include "my.h"

char *my_strupcase(char *str)
{
    char *result = str;

    while (*str != '\0') {
        *str = my_toupper(*str);
        ++str;
    }

    return (result);
}
