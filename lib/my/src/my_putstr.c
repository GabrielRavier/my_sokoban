/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays the characters of a string one by one
*/

#include "my.h"
#include <unistd.h>

void my_putstr(char const *str)
{
    my_dputs(str, STDOUT_FILENO);
}
