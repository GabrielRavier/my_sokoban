/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines isxdigit
*/

#include "my/ctype.h"

int my_isxdigit(int character)
{
    return (my_isdigit(character) || (my_tolower(character) >= 'a' &&
        my_tolower(character) <= 'f'));
}
