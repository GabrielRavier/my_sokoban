/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines str_isprintable
*/

#include "my/misc.h"
#include "my/ctype.h"

bool my_str_isprintable(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_isprint(str[i]))
            return (false);
    return (true);
}
