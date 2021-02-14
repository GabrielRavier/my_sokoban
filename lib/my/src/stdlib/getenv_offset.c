/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines getenv_offset
*/

#include "my/internal/stdlib.h"
#include "my/string.h"
#include <stddef.h>

extern char **environ;

// Similar to getenv, but outputs the offset of the found variable
char *my_getenv_offset(const char *name, size_t *offset)
{
    size_t name_len = my_strlen(name);
    char *const *environ_it = environ;

    if (environ == NULL || name_len == 0)
        return (NULL);
    for (; *environ_it != NULL; ++environ_it) {
        if (my_strncmp(*environ_it, name, name_len) == 0 &&
            (*environ_it)[name_len] == '=') {
            *offset = environ_it - environ;
            return (&(*environ_it)[name_len + 1]);
        }
    }
    return (NULL);
}
