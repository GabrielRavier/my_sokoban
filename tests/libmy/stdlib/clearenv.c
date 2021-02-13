/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines clearenv
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"

Test(my_cleanenv, bionic)
{
    extern char **environ;

    cr_assert_eq(my_setenv("test-variable", "a", 1), 0);

    char **old_environ = NULL;
    for (size_t i = 0; environ[i] != NULL; ++i) {
        old_environ = realloc(old_environ, sizeof(char *) * (i + 1));
        old_environ[i] = my_strdup(environ[i]);
    }

    cr_assert_eq(clearenv(), 0);
    cr_assert_eq(environ, NULL);
    cr_assert_eq(my_getenv("test-variable"), NULL);

    cr_assert_eq(my_setenv("test-variable", "post-clear", 1), 0);
    cr_assert_str_eq(my_getenv("test-variable"), "post-clear");

    for (size_t i = 0; old_environ[i] != NULL; ++i)
        cr_assert_eq(putenv(old_environ[i]), 0);

    cr_assert_str_eq(my_getenv("test-variable"), "a");
    cr_assert_eq(my_unsetenv("test-variable"), 0);
}
