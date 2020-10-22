/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Changes the size of the memory block pointed to by ptr to size bytes
*/

#include "my/stdlib.h"
#include "my/string.h"
#include <stdlib.h>

static void *handle_other_cases(void *ptr, size_t new_length,
    size_t original_length)
{
    void *new_ptr;

    if (new_length <= original_length)
        return (ptr);
    new_ptr = malloc(new_length);
    if (new_ptr) {
        my_memcpy(new_ptr, ptr, original_length);
        free(ptr);
    }
    return (new_ptr);
}

void *my_realloc_size(void *ptr, size_t new_length, size_t original_length)
{
    if (new_length == 0) {
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL)
        return (malloc(new_length));
    return (handle_other_cases(ptr, new_length, original_length));
}
