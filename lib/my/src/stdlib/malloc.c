/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines malloc
*/

#include "my/stdlib.h"
#include <stdlib.h>

#if LIBMY_HAS_LIBC_ALLOC

void *my_malloc(size_t size)
{
    return (malloc(size));
}

#else

void *my_malloc(size_t size)
{
    return (NULL);
}

#endif
