/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fputc
*/

#include "my/stdio.h"

int my_fputc(int c, my_file_t *fp)
{
    return (my_putc(c, fp));
}
