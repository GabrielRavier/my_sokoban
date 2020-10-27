/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements new_from_string
*/

#include "my/my_string.h"
#include "my/string.h"
#include <sys/types.h>

struct my_string *my_string_new_from_string(const char *string, size_t length)
{
    struct my_string *self = my_string_new();
    if (string)
        my_string_append(self, string, length);
    return self;
}
