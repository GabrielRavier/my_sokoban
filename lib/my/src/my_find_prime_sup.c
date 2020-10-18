/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Finds the smallest prime number that is >= to nb
*/

#include "my/misc.h"
#include <limits.h>

int my_find_prime_sup(int nb)
{
    if (nb < 0)
        nb = 0;

    for (int i = nb; i < INT_MAX; ++i)
        if (my_is_prime(i))
            return i;

    return 0;
}
