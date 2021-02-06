/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fputc
*/

#include "my/stdio.h"

int my_fputc(int c, MY_FILE *stream)
{
    return (my_putc(c, stream));
}
