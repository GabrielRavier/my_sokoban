/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Resizes a my_string
*/

#include "my/my_string.h"
#include "my/internal/my_string.h"

struct my_string *my_string_resize(struct my_string *self, size_t count)
{
    if (self == NULL)
        return NULL;
    if (count >= self->allocated_size)
        my_string_guarantee_can_expand(self, count - self->length);
    self->length = count;
    self->string[self->length] = '\0';
    return self;
}
