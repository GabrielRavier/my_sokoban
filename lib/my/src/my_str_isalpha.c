/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Checks if the passed string only contains alphabetical characters
*/

#include "my/misc.h"
#include "my/ctype.h"

bool my_str_isalpha(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_isalpha(str[i]))
            return (false);
    return (true);
}
