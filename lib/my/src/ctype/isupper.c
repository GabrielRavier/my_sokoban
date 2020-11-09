/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check for an uppercase letter
*/

#include "my/ctype.h"

int my_isupper(int c)
{
    return ((c >= 'A') && (c <= 'Z'));
}
