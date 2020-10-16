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
    } else
        num->is_negative = false;

    if (!my_str_isnum(str))
        return false;

    while (*str == '0' && *(str + 1) != '\0')
        ++str;

    num->number = (unsigned char *)my_strdup(str);
    num->num_digits = my_strlen(str);
    my_revstr((char *)num->number);
    for (size_t i = 0; i < num->num_digits; ++i)
        num->number[i] -= '0';

    return true;
}
