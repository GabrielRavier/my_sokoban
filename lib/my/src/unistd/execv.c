/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines execv
*/

#include "my/unistd.h"
#include <unistd.h>

extern char **environ;

int my_execv(const char *pathname, char *const argv[])
{
    return (execve(pathname, argv, environ));
}
