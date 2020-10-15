/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Sets an initialized bigint from a string
*/

#include "my_bigint.h"
#include "my.h"
#include <stdlib.h>

// Maybe add stuff like skipping whitespace in the future ? idk
bool my_bigint_set_str(struct my_bigint *num, const char *str)
{
    if (*str == '-') {
        num->is_negative = true;
        ++str;
    }
    else
        num->is_negative = false;

    if (!my_str_isnum(str))
        return false;

    while (*str == '0')
        ++str;

    num->number = my_strdup(str);
    my_revstr(num->number);
    return true; 
}
