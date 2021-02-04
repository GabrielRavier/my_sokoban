/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines my_strtoul
*/

#include "my/stdlib.h"
#include "strtoul.h"

unsigned long my_strtoul(const char *num_ptr, char **end_num_ptr, int base)
{
    return my_strtoul_internal(num_ptr, end_num_ptr, base);
}
