/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines my_strtoll
*/

#include "strtoll.h"

TYPE my_strtoll(const char *num_ptr, char **end_num_ptr, int base)
{
    return my_strtoll_internal(num_ptr, end_num_ptr, base);
}

