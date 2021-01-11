/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines my_strtol
*/

#include "strtol.h"

TYPE my_strtol(const char *num_ptr, char **end_num_ptr, int base)
{
    return my_strtol_internal(num_ptr, end_num_ptr, base);
}

