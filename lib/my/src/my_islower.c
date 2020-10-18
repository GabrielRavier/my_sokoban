/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Checks for a lowercase character
*/

#include "my/ctype.h"

int my_islower(int c)
{
    return ((c >= 'a') && (c <= 'z'));
}
