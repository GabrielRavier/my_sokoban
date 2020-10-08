/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts a number to a string
*/

#include "my.h"

char *my_nbr_to_string(int number)
{
    return my_nbr_to_string_base(number, "0123456789");
}
