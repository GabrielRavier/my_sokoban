/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines isdigit
*/

#include "my/ctype.h"

int my_isdigit(int c)
{
    return ((c >= '0') && (c <= '9'));
}
