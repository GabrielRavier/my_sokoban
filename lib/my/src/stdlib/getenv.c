/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines getenv
*/

#include "my/stdlib.h"
#include "my/internal/stdlib.h"
#include <stdbool.h>

char *my_getenv(const char *name)
{
    size_t offset_unused;

    return my_getenv_offset(name, &offset_unused);
}
