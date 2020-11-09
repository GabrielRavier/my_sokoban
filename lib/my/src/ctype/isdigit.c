/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check for a digit (0 through 9)
*/

#include "my/ctype.h"

int my_isdigit(int c)
{
    return ((c >= '0') && (c <= '9'));
}
