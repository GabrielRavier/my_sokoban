/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines my_strtoimax
*/

#include "my/inttypes.h"
#include "strtoimax.h"

intmax_t my_strtoimax(const char *num_ptr, char **end_num_ptr, int base)
{
    return my_strtoimax_internal(num_ptr, end_num_ptr, base);
}
