/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar - Day 08
** File description:
** Copes size bytes from source to destination
*/

#include "my/string.h"
#include <stddef.h>

void *my_memcpy(void *destination, const void *source, size_t size)
{
    return my_memmove(destination, source, size);
}
