/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests getenv
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include <stdio.h>

Test(my_getenv, freebsd_clearenv_basic)
{
    char name[1024], value[1024];

    for (size_t i = 0; i < 1024; ++i) {
        snprintf(name, sizeof(name), "crap%zu", i);
        snprintf(value, sizeof(value), "%zu", i);
        cr_assert_eq(my_setenv(name, value, 1), 0);
    }

    clearenv();

    snprintf(name, sizeof(name), "crap0");
    snprintf(value, sizeof(name), "0");
    cr_assert_eq(my_setenv(name, value, 1), 0);

    cr_assert_str_eq(my_getenv("crap0"), "0");
    cr_assert_eq(my_getenv("crap1"), NULL);
    cr_assert_eq(my_getenv("crap2"), NULL);
}

Test(my_getenv, freebsd_basic)
{
    cr_assert_eq(my_setenv("EVIL", "very=bad", 1), 0);
    cr_assert_str_eq(my_getenv("EVIL"), "very=bad");
    cr_assert_str_eq(my_getenv("EVIL=very"), "bad");
    cr_assert_eq(unsetenv("EVIL"), 0);
}

Test(my_getenv, dietlibc)
{
    cr_assert_eq(putenv("foo=bar"), 0);
    cr_assert_str_eq(my_getenv("foo"), "bar");
}
