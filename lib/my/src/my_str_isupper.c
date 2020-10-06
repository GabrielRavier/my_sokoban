/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check if the passed string only contains uppercase characters
*/

#include "my.h"

int my_str_isupper(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_isupper(str[i]))
            return (0);

    return (1);
}
