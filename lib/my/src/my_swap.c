/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Swaps the content of two integers to which pointers are passed as parameters
*/

#include "my/misc.h"

void my_swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
