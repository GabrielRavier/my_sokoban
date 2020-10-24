/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements insert
*/

#include "my/internal/my_string.h"
#include "my/my_string.h"
#include "my/string.h"

// Does sanity checks, then expands the size of the string as needed, then moves
// the end of the string to make space for the inserted string (if we're
// inserting at the end, this will end up doing nothing), then copies the
// inserted string to where we want it to be
struct my_string *my_string_insert(struct my_string *self, const char *string,
    size_t length, size_t position)
{
    if (self == NULL || string == NULL || length == 0 ||
        (position > self->length))
        return self;
    my_string_guarantee_can_expand(self, length);
    my_memmove(self->string + position + length, self->string + position,
        self->length - position);
    my_memcpy(self->string + position, string, length);
    self->length += length;
    self->string[self->length] = '\0';
    return self;
}
