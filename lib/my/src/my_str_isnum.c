/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check if the passed string only contains digits
*/

#include "my/misc.h"
#include "my/ctype.h"

bool my_str_isnum(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_isdigit(str[i]))
            return (false);
    return (true);
}
