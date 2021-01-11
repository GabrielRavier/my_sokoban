/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines assign
*/

#include "my/my_string.h"
#include "my/string.h"

struct my_string *my_string_assign(struct my_string *self,
    const struct my_string *source)
{
    if (!self)
        return NULL;
    my_string_resize(self, source->length);
    my_memcpy(self->string, source->string, self->length);
    return self;
}
