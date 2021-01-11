/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines isalnum
*/

#include "my/ctype.h"

int my_isalnum(int c)
{
    return (my_isalpha(c) || my_isdigit(c));
}
