/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays N if the parameter is negative and P if not
*/

#include "my.h"

void my_isneg(int n)
{
    my_putchar((n < 0) ? 'N' : 'P');
}
