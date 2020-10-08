/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays a number in a given base and width
*/

#include "my.h"
#include <stdlib.h>

int my_putnbr_base_width(int number, const char *base, size_t width)
{
    char *converted_number = my_nbr_to_string_base_width(number, base, width);
    my_putstr(converted_number);
    free(converted_number);

    return 0;
}
