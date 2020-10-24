/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements erase
*/

#include "my/my_string.h"
#include "my/string.h"

struct my_string *my_string_erase(struct my_string *self, size_t index,
    size_t count)
{
    if (self == NULL || index > self->length || (index + count) > self->length)
        return self;
    my_memmove(self->string + index, self->string + index + count,
        self->length - (index + count));
    self->length -= count;
    self->string[self->length] = '\0';
    return self;
}
