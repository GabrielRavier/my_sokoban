/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts a string to an integer
*/

#include "my.h"
#include <stdbool.h>
#include <limits.h>

int my_getnbr(char const *number_ptr)
{
    return my_getnbr_base(number_ptr, "0123456789");
}
