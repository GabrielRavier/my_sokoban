/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines getenv
*/

#include "my/stdlib.h"
#include <stdbool.h>

extern char **environ;

char *my_getenv(const char *name)
{
    char **environ_it;
    char *current_env_var_it;
    const char *name_it;

    if (environ == NULL)
        return (NULL);
    for (environ_it = environ; *environ_it != NULL; ++environ_it) {
        current_env_var_it = *environ_it;
        for (name_it = name; *name_it == *current_env_var_it &&
            *name_it != '\0'; ++name_it)
            ++current_env_var_it;
        if (*name_it == '\0' && *current_env_var_it == '=')
            return (current_env_var_it + 1);
    }
    return (NULL);
}
