/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Checks for a printable character
*/

#include "my.h"

// Assumes ASCII, i.e. this is the range of printable characters in ASCII
int my_isprint(int c)
{
    return ((c >= 0x20) && (c <= 0x7E));
}
