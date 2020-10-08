/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Changes the size of the memory block pointed to by ptr to size bytes
*/

#include "my.h"
#include <stdlib.h>

static void *handle_other_cases(void *ptr, size_t new_length,
    size_t original_length)
{
    if (new_length <= original_length)
        return ptr;
    else {
        void *new_ptr = malloc(new_length);
        if (new_ptr) {
            my_memcpy(new_ptr, ptr, original_length);
            free(ptr);
        }
        return new_ptr;
    }
}

void *my_realloc_size(void *ptr, size_t new_length, size_t original_length)
{
    if (new_length == 0) {
        free(ptr);
        return NULL;
    } else if (ptr == NULL)
        return malloc(new_length);
    else
        return handle_other_cases(ptr, new_length, original_length);
}
