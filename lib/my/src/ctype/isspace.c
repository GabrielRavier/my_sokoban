/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines isspace
*/

#include "my/ctype.h"

int my_isspace(int character)
{
    return character == ' ' || character == '\f' || character == '\n' ||
        character == '\r' || character == '\t' || character == '\v';
}
