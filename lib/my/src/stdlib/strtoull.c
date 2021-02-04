/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines my_strtoull
*/

#include "my/stdlib.h"
#include "strtoull.h"

unsigned long long my_strtoull(const char *num_ptr, char **end_num_ptr,
    int base)
{
    return my_strtoull_internal(num_ptr, end_num_ptr, base);
}
