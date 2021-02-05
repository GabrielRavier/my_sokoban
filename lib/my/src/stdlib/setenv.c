/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines setenv
*/

#include "my/stdlib.h"
#include "my/internal/stdlib.h"
#include "my/string.h"
#include "my/strings.h"
#include <errno.h>
#include <stdbool.h>

extern char **environ;

static bool grow_environ(size_t environ_entry_count)
{
    static bool has_alloced_environ_before = false;
    char **new_environ = my_realloc_size(has_alloced_environ_before ? environ :
        NULL, sizeof(char *) * (environ_entry_count + 2), sizeof(char *) *
        (environ_entry_count + 1));

    if (new_environ == NULL) {
        errno = ENOMEM;
        return (false);
    }
    if (!has_alloced_environ_before++)
        my_memcpy(new_environ, environ, sizeof(char *) * environ_entry_count);
    environ = new_environ;
    return (true);
}

static bool make_new_entry(size_t *value_offset)
{
    size_t environ_entry_count = 0;
    char **environ_it = environ;

    if (environ)
        for (; *environ_it; ++environ_it)
            ++environ_entry_count;
    if (!grow_environ(environ_entry_count))
        return (false);
    environ[environ_entry_count + 1] = NULL;
    *value_offset = environ_entry_count;
    return (true);
}

static int set_new_value(const char *name, const char *value, size_t len_value,
    size_t value_offset)
{
    size_t len_name = my_strlen(name);

    environ[value_offset] = my_malloc(len_name + len_value + 2);
    if (environ[value_offset] == NULL) {
        errno = ENOMEM;
        return (-1);
    }
    my_memcpy(environ[value_offset], name, len_name);
    environ[value_offset][len_name] = '=';
    my_memcpy(environ[value_offset] + len_name + 1, value, len_value + 1);
    return (0);
}

int my_setenv(const char *name, const char *value, int overwrite)
{
    size_t len_value = my_strlen(value);
    char *old_value;
    size_t value_offset;

    if (name == NULL || *name == '\0' || my_strchr(name, '=') != NULL) {
        errno = EINVAL;
        return (-1);
    }
    old_value = my_getenv_offset(name, &value_offset);
    if (old_value) {
        if (overwrite == 0)
            return (0);
        if (my_strlen(old_value) >= len_value) {
            my_memcpy(old_value, value, len_value + 1);
            return (0);
        }
    } else if (!make_new_entry(&value_offset))
        return (-1);
    return (set_new_value(name, value, len_value, value_offset));
}
