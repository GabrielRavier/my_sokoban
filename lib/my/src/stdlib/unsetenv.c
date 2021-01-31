/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines unsetenv
*/

#include "my/stdlib.h"
#include "my/internal/stdlib.h"
#include "my/string.h"
#include <errno.h>

extern char **environ;

int my_unsetenv(const char *name)
{
    char **environ_it;
    size_t offset;

    if (*name == '\0' || my_strchr(name, '=') != NULL) {
        errno = EINVAL;
        return (-1);
    }
    while (my_getenv_offset(name, &offset) != NULL)
        for (environ_it = &environ[offset];; ++environ_it) {
            environ_it[0] = environ_it[1];
            if (*environ_it == NULL)
                break;
        }
    return (0);
}
