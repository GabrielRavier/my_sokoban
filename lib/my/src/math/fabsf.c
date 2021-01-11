/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines fabsf
*/

#include "my/math.h"

float my_fabsf(float x)
{
    return ((x < 0) ? -x : x);
}
