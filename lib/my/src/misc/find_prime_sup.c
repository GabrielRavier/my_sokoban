/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Finds the smallest prime number that is >= to nb
*/

#include "my/misc.h"
#include <limits.h>

int my_find_prime_sup(int number)
{
    if (number < 0)
        number = 0;
    for (unsigned i = (unsigned)number; i < INT_MAX; ++i)
        if (my_is_prime(i))
            return ((int)i);
    return (0);
}
