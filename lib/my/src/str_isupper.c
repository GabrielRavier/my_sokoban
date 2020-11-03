/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check if the passed string only contains uppercase characters
*/

#include "my/misc.h"
#include "my/ctype.h"

bool my_str_isupper(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_isupper(str[i]))
            return (false);
    return (true);
}
