/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines islower
*/

#include "my/ctype.h"

int my_islower(int c)
{
    return ((c >= 'a') && (c <= 'z'));
}
