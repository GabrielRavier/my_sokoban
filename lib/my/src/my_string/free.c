/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements free
*/

#include "my/my_string.h"
#include <stdlib.h>

void my_string_free(struct my_string *self)
{
    if (self == NULL)
        return;
    free(self->string);
    free(self);
}
