/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Reverses a string
*/

#include "my.h"

char *my_revstr(char *str)
{
    char tmp;
    int length = my_strlen(str);

    for (int i = 0; i < (length / 2); ++i) {
        tmp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = tmp;
    }

    return (str);
}
