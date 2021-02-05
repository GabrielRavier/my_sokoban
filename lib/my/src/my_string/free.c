/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines free
*/

#include "my/my_string.h"
#include "my/stdlib.h"

void my_string_free(struct my_string *self)
{
    if (self == NULL)
        return;
    my_free(self->string);
    my_free(self);
}
