/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts a number to a string in a given base
*/

#include "my.h"

char *my_nbr_to_string_base(int number, const char *base)
{
    return my_nbr_to_string_base_width(number, base, 0);
}
