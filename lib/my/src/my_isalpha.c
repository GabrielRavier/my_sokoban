/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check for an alphabetic character
*/

#include "my/ctype.h"

int my_isalpha(int c)
{
    return (my_isupper(c) || my_islower(c));
}
