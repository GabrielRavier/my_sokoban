/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines my_strtoumax
*/

#include "my/inttypes.h"
#include "strtoumax.h"

uintmax_t my_strtoumax(const char *num_ptr, char **end_num_ptr, int base)
{
    return (my_strtoumax_internal(num_ptr, end_num_ptr, base));
}
