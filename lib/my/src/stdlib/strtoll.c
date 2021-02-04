/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines my_strtoll
*/

#include "my/stdlib.h"
#include "strtoll.h"

long long my_strtoll(const char *num_ptr, char **end_num_ptr, int base)
{
    return (my_strtoll_internal(num_ptr, end_num_ptr, base));
}
