/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements append
*/

#include "my/my_string.h"

struct my_string *my_string_append(struct my_string *self, const char *string,
    size_t length)
{
    return my_string_insert(self, string, length, self->length);
}
