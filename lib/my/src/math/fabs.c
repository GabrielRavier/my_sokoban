/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fabs
*/

#include "my/math.h"
#include <stdint.h>

double my_fabs(double x)
{
    union {
        double as_double;
        uint64_t as_u64;
    } u = {.as_double = x};

    u.as_u64 &= 0x7FFFFFFFFFFFFFFFull;
    return u.as_double;
}
