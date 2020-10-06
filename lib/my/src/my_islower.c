/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Checks for a lowercase character
*/

#include "my.h"

int my_islower(int c)
{
    return ((c >= 'a') && (c <= 'z'));
}
