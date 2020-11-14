/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements guarantee_can_expand
*/

#include "my/internal/my_string.h"
#include "my/stdlib.h"
#include "my/macros.h"
#include "my/assert.h"

// We allocate some extra bytes to reduce the amount of calls to realloc when
// frequently increasing the size of self
static const size_t EXTRA_ALLOCATED_SPACE = 16;

struct my_string *my_string_guarantee_can_expand(struct my_string *self,
    size_t length)
{
    size_t current_allocated_size = self->allocated_size;

    if (self->length + length >= current_allocated_size) {
        self->allocated_size =
            MY_MAX(self->length + length + 1 + EXTRA_ALLOCATED_SPACE,
                self->length * 2);
        self->string = my_realloc_size(
            self->string, self->allocated_size, current_allocated_size);
        MY_ASSERT(self->string != NULL);
    }
    return self;
}
