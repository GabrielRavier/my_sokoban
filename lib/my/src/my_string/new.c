/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements new
*/

#include "my/my_string.h"
#include "my/internal/my_string.h"
#include "my/assert.h"
#include <stdlib.h>

struct my_string *my_string_new(void)
{
    struct my_string *self =
        (struct my_string *)malloc(sizeof(struct my_string));

    MY_ASSERT(self != NULL);
    self->length = 0;
    self->allocated_size = 0;
    self->string = NULL;
    my_string_guarantee_can_expand(self, 1);
    self->string[0] = '\0';
    return self;
}
