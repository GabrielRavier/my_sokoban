/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines isupper
*/

#include "my/ctype.h"

int my_isupper(int c)
{
    return ((c >= 'A') && (c <= 'Z'));
}
