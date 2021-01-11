/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines bcopy
*/

#include "my/strings.h"
#include "my/string.h"

void my_bcopy(const void *source, void *destination, size_t size)
{
    my_memmove(destination, source, size);
}
