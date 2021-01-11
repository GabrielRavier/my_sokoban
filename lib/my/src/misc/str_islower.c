/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines str_islower
*/

#include "my/misc.h"
#include "my/ctype.h"

bool my_str_islower(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_islower(str[i]))
            return (false);
    return (true);
}
