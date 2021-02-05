/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines execv
*/

#include "my/unistd.h"

extern char **environ;

int my_execv(const char *pathname, char *const argv[])
{
    return (my_execve(pathname, argv, environ));
}
