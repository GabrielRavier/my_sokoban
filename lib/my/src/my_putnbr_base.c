/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays a number in a given base
*/

#include "my.h"

int my_putnbr_base(int number, const char *base)
{
    return my_putnbr_base_width(number, base, 0);
}
