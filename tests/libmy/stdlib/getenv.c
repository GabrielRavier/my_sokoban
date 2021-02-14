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

    cr_assert_eq(my_getenv("crap0"), getenv("crap0"));
    cr_assert_eq(my_getenv("crap1"), getenv("crap1"));
    cr_assert_eq(my_getenv("crap2"), getenv("crap2"));
}

Test(my_getenv, freebsd_basic)
{
    cr_assert_eq(my_setenv("EVIL", "very=bad", 1), 0);
    cr_assert_eq(my_getenv("EVIL"), getenv("EVIL"));
    cr_assert_eq(my_getenv("EVIL=very"), getenv("EVIL=very"));
    cr_assert_eq(my_unsetenv("EVIL"), 0);
}

Test(my_getenv, dietlibc)
{
    cr_assert_eq(putenv("foo=bar"), 0);
    cr_assert_eq(my_getenv("foo"), getenv("foo"));
}

Test(my_getenv, bionic)
{
    cr_assert_eq(my_setenv("test-variable", "hello", 1), 0);
    cr_assert_eq(my_getenv("test-variable"), getenv("test-variable"));
    cr_assert_eq(my_unsetenv("test-variable"), 0);
    cr_assert_eq(my_getenv("test-variable"), NULL);
}
