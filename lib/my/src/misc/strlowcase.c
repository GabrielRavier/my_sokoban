/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Puts every letter of a string into lowercase
*/

#include "my/misc.h"
#include "my/ctype.h"

char *my_strlowcase(char *str)
{
    char *const result = str;

    while (*str != '\0') {
        *str = my_tolower(*str);
        ++str;
    }
    return (result);
}
