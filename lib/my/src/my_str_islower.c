/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check if the passed string only contains lowercase characters
*/

#include "my.h"

int my_str_islower(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_islower(str[i]))
            return (0);

    return (1);
}
