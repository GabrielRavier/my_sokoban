/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strupcase
*/

#include "my/misc.h"
#include "my/ctype.h"

char *my_strupcase(char *str)
{
    char *const result = str;

    while (*str != '\0') {
        *str = (char)my_toupper(*str);
        ++str;
    }
    return (result);
}
