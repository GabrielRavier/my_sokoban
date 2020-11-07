/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Puts every letter in uppercase
*/

#include "my/misc.h"
#include "my/ctype.h"

char *my_strupcase(char *str)
{
    char *const result = str;

    while (*str != '\0') {
        *str = my_toupper(*str);
        ++str;
    }
    return (result);
}
