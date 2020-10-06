/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays the characters of a string one by one
*/

#include "my.h"

int my_putstr(char const *str)
{
    while (*str != '\0')
        my_putchar(*str++);

    return (0);
}
