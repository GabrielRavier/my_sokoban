/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_parse_int
*/

#include "my/internal/printf/parse_conversion_info.h"
#include "my/ctype.h"
#include <limits.h>

static void do_loop_iter(int *result, char digit)
{
    if (*result > (INT_MAX / 10)) {
        *result = -1;
        return;
    }
    *result *= 10;
    if (INT_MAX - digit < *result) {
        *result = -1;
        return;
    }
    *result += digit;
}

int asprintf_parse_int(const char **to_parse)
{
    int result = **to_parse - '0';

    while (my_isdigit(*++*to_parse)) {
        if (result >= 0)
            do_loop_iter(&result, **to_parse - '0');
        if (result < 0)
            break;
    }
    return result;
}
