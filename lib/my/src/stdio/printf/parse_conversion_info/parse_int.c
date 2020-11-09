/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_parse_int
*/

#include "my/internal/printf/parse_conversion_info.h"
#include "my/ctype.h"
#include <limits.h>

int asprintf_parse_int(const char **to_parse)
{
    int result = **to_parse - '0';
    char digit;

    while (my_isdigit(*++*to_parse))
        if (result >= 0) {
            if (result > (INT_MAX / 10))
                return -1;
            digit = **to_parse - '0';
            result *= 10;
            if (INT_MAX - digit < result)
                return -1;
            result += digit;
        }
    return result;
}
