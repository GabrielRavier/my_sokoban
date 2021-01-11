/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines isalpha
*/

#include "my/ctype.h"

int my_isalpha(int c)
{
    return (my_isupper(c) || my_islower(c));
}
