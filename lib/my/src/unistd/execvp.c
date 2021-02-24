/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines execvp
*/

#include "my/unistd.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <errno.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wcast-qual"

static const char *make_exec_pathname(const char *path_string, const char *file,
    char **exec_pathname)
{
    if ((my_asprintf(exec_pathname, "%.*s%s%s", my_strchr(path_string, ':') ?
        (int)(my_strchr(path_string, ':') - path_string) : -1, path_string,
        *path_string != '\0' ? "/" : "", file) < 0) ||
        (my_strchr(path_string, ':') == NULL))
        return (NULL);
    return (my_strchr(path_string, ':') + 1);
}

static bool handle_enoexec(const char *file, char *const argv[])
{
    const char *new_arguments[2560];

    new_arguments[0] = "sh";
    new_arguments[1] = file;
    for (size_t i = 1; argv[i] != NULL; ++i) {
        new_arguments[i + 1] = argv[i];
        if (i >= 2558) {
            errno = E2BIG;
            return (false);
        }
    }
    my_execv("/bin/sh", (char *const *)new_arguments);
    return (true);
}

int my_execvp(const char *file, char *const argv[])
{
    const char *env_path = my_getenv("PATH");
    const char *path_string = my_strchr(file, '/') ? "" : env_path ? env_path :
        "/bin:/usr/bin";
    char *exec_pathname;

    do {
        path_string = make_exec_pathname(path_string, file, &exec_pathname);
        if (!exec_pathname)
            return (-1);
        my_execv(exec_pathname, argv);
        my_free(exec_pathname);
        if (errno == ENOEXEC && !handle_enoexec(file, argv))
            return (-1);
    } while (path_string != NULL);
    return (-1);
}
