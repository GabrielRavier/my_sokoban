/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays the int given as a parameter (works with all values including
** INT_MIN)
*/

#include "my.h"

int my_putnbr(int number)
{
    return my_putnbr_base(number, "0123456789");
}
