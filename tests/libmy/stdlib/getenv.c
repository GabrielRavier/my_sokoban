/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests getenv
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;

Test(my_getenv, freebsd_clearenv_basic)
{
    char name[1024], value[1024];

    for (size_t i = 0; i < 1024; ++i) {
        snprintf(name, sizeof(name), "crap%zu", i);
        snprintf(value, sizeof(value), "%zu", i);
        cr_assert_eq(setenv(name, value, 1), 0);
    }

    *environ = NULL;

    snprintf(name, sizeof(name), "crap0");
    snprintf(value, sizeof(name), "0");
    cr_assert_eq(setenv(name, value, 1), 0);

    cr_assert_str_eq(my_getenv("crap0"), "0");
    cr_assert_eq(my_getenv("crap1"), NULL);
    cr_assert_eq(my_getenv("crap2"), NULL);
}

Test(my_getenv, freebsd_basic)
{
    cr_assert_eq(setenv("EVIL", "very=bad", 1), 0);
    cr_assert_str_eq(my_getenv("EVIL"), "very=bad");
    cr_assert_str_eq(my_getenv("EVIL=very"), "bad");
    cr_assert_eq(unsetenv("EVIL"), 0);
}

Test(my_getenv, freebsd_putenv_basic)
{
    char string[1024];

    my_strcpy(string, "crap=true");
    cr_assert_eq(putenv(string), 0);
    cr_assert_str_eq(my_getenv("crap"), "true");
    string[1] = 'l';
    cr_assert_str_eq(my_getenv("clap"), "true");
    cr_assert_eq(my_getenv("crap"), NULL);
    string[1] = 'r';
    cr_assert_eq(unsetenv("crap"), 0);
    cr_assert_eq(my_getenv("crap"), NULL);
}

Test(my_getenv, freebsd_setenv_basic)
{
    static const size_t NUM_VARS = 1024;
    size_t offset = lrand48();
    char name[1024];
    char value[1024];

    for (size_t i = 0; i < NUM_VARS; ++i) {
        snprintf(name, sizeof(name), "var%zu", (i * 7 + offset) % NUM_VARS);
        snprintf(name, sizeof(value), "value%ld", lrand48());
        cr_assert_eq(setenv(name, value, 1), 0);
        cr_assert_eq(setenv(name, "foo", 0), 0);
        cr_assert_str_eq(my_getenv(name), value);
    }

    offset = lrand48();
    for (size_t i = 0; i < NUM_VARS; ++i) {
        snprintf(name, sizeof(name), "var%zu", (i * 11 + offset) % NUM_VARS);
        cr_assert_eq(unsetenv(name), 0);
        cr_assert_eq(my_getenv(name), NULL);
        cr_assert_eq(unsetenv(name), 0);
    }

    cr_assert_eq(setenv(NULL, "val", 1), -1);
    cr_assert_eq(errno, EINVAL);
    cr_assert_eq(setenv("", "val", 1), -1);
    cr_assert_eq(errno, EINVAL);
    cr_assert_eq(setenv("v=r", "val", 1), -1);
    cr_assert_eq(errno, EINVAL);
    cr_assert_eq(setenv("var", "=val", 1), 0);
    cr_assert_str_eq(my_getenv("var"), "=val");
}

Test(my_getenv, freebsd_setenv_mixed)
{
    char string[32];

    my_strcpy(string, "mixedcrap=putenv");
    cr_assert_eq(setenv("mixedcrap", "setenv", 1), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "setenv");
    cr_assert_eq(putenv(string), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "putenv");
    cr_assert_eq(unsetenv("mixedcrap"), 0);
    cr_assert_eq(my_getenv("mixedcrap"), NULL);

    cr_assert_eq(putenv(string), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "putenv");
    cr_assert_eq(setenv("mixedcrap", "setenv", 1), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "setenv");
    cr_assert_eq(unsetenv("mixedcrap"), 0);
    cr_assert_eq(my_getenv("mixedcrap"), NULL);
}

Test(my_getenv, dietlibc)
{
    cr_assert_eq(putenv("foo=bar"), 0);
    cr_assert_str_eq(my_getenv("foo"), "bar");
}
