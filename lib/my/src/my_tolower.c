/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** If uppercase, return lowercase equivalent
*/

#include "my.h"

int my_tolower(int c)
{
    return (my_isupper(c) ? (c - 'A' + 'a') : c);
}
