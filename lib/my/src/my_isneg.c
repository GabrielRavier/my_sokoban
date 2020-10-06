/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar
** File description:
** Displays N if the parameter is negative and P if not
*/

#include "my.h"

int my_isneg(int n)
{
    my_putchar((n < 0) ? 'N' : 'P');
    return (0);
}
