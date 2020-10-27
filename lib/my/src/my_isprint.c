/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Checks for a printable character
*/

#include "my/ctype.h"

static const int PRINTABLE_RANGE_START = 0x20;
static const int PRINTABLE_RANDE_END = 0x7E;

// Assumes ASCII, i.e. this is the range of printable characters in ASCII
int my_isprint(int c)
{
    return ((c >= PRINTABLE_RANGE_START) && (c <= PRINTABLE_RANDE_END));
}
