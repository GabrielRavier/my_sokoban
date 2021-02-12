/*
** EPITECH PROJECT, 2021
** libym
** File description:
** Defines calloc
*/

#include "my/stdlib.h"
#include "my/string.h"

void *my_calloc(size_t num_members, size_t size)
{
    size_t malloc_size = num_members * size;
    void *result = my_malloc(malloc_size);

    if (result != NULL)
        my_memset(result, 0, malloc_size);
    return (result);
}
