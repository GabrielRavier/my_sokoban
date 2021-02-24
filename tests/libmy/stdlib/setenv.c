/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests setenv
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <stdio.h>
#include <errno.h>

#pragma GCC diagnostic ignored "-Wcast-qual"

Test(my_setenv, midnightbsd_gnulib)
{
    cr_assert_eq(my_setenv("a", "==", -1), 0);
    cr_assert_eq(my_setenv("a", "2", 0), 0);
    cr_assert_eq(my_getenv("a"), getenv("a"));

    errno = 0;
    cr_assert_eq(my_setenv("", "", 1), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv("a=b", "", 1), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv(NULL, "", 0), -1);
    cr_assert_eq(errno, EINVAL);
}

Test(my_setenv, freebsd_setenv_basic)
{
    static const size_t NUM_VARS = 1024;
    size_t offset = lrand48();
    char name[1024];
    char value[1024];

    for (size_t i = 0; i < NUM_VARS; ++i) {
        snprintf(name, sizeof(name), "var%zu", (i * 7 + offset) % NUM_VARS);
        snprintf(value, sizeof(value), "value%ld", lrand48());
        cr_assert_eq(my_setenv(name, value, 1), 0);
        cr_assert_eq(my_setenv(name, "foo", 0), 0);
        cr_assert_str_eq(my_getenv(name), value);
    }

    offset = lrand48();
    for (size_t i = 0; i < NUM_VARS; ++i) {
        snprintf(name, sizeof(name), "var%zu", (i * 11 + offset) % NUM_VARS);
        cr_assert_eq(my_unsetenv(name), 0);
        cr_assert_eq(my_getenv(name), NULL);
        cr_assert_eq(my_unsetenv(name), 0);
    }

    errno = 0;
    cr_assert_eq(my_setenv(NULL, "val", 1), -1);
    cr_assert_eq(errno, EINVAL);
    errno = 0;
    cr_assert_eq(my_setenv("", "val", 1), -1);
    cr_assert_eq(errno, EINVAL);
    errno = 0;
    cr_assert_eq(my_setenv("v=r", "val", 1), -1);
    cr_assert_eq(errno, EINVAL);
    cr_assert_eq(my_setenv("var", "=val", 1), 0);
    cr_assert_str_eq(my_getenv("var"), "=val");
}

Test(my_setenv, freebsd_setenv_mixed)
{
    char string[32];

    my_strcpy(string, "mixedcrap=putenv");
    cr_assert_eq(my_setenv("mixedcrap", "setenv", 1), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "setenv");
    cr_assert_eq(putenv(string), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "putenv");
    cr_assert_eq(my_unsetenv("mixedcrap"), 0);
    cr_assert_eq(my_getenv("mixedcrap"), NULL);

    cr_assert_eq(putenv(string), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "putenv");
    cr_assert_eq(my_setenv("mixedcrap", "setenv", 1), 0);
    cr_assert_str_eq(my_getenv("mixedcrap"), "setenv");
    cr_assert_eq(my_unsetenv("mixedcrap"), 0);
    cr_assert_eq(my_getenv("mixedcrap"), NULL);
}

Test(my_setenv, klibc)
{
    cr_assert_eq(my_setenv("SETENV", "setenv", 1), 0);
    cr_assert_eq(putenv((char *)"PUTENV=putenv"), 0);
    cr_assert_str_eq(my_getenv("SETENV"), "setenv");
    cr_assert_str_eq(my_getenv("PUTENV"), "putenv");

    cr_assert_eq(my_setenv("SETENV", "setenv_good", 1), 0);
    cr_assert_eq(putenv((char *)"PUTENV=putenv_good"), 0);
    cr_assert_str_eq(my_getenv("SETENV"), "setenv_good");
    cr_assert_str_eq(my_getenv("PUTENV"), "putenv_good");

    cr_assert_eq(my_setenv("SETENV", "setenv_bad", 0), 0);
    cr_assert_eq(my_setenv("NEWENV", "newenv_good", 0), 0);
    cr_assert_str_eq(my_getenv("SETENV"), "setenv_good");
    cr_assert_str_eq(my_getenv("NEWENV"), "newenv_good");

    cr_assert_eq(my_unsetenv("SETENV"), 0);
    cr_assert_eq(my_unsetenv("NEWENV"), 0);
    cr_assert_eq(my_getenv("SETENV"), NULL);
    cr_assert_eq(my_getenv("NEWENV"), NULL);
}

Test(my_setenv, bionic_einval)
{
    errno = 0;
    cr_assert_eq(my_setenv(NULL, "value", 0), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv(NULL, "value", 1), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv("", "value", 0), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv("", "value", 1), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv("a=b", "value", 0), -1);
    cr_assert_eq(errno, EINVAL);

    errno = 0;
    cr_assert_eq(my_setenv("a=b", "value", 1), -1);
    cr_assert_eq(errno, EINVAL);
}

Test(my_setenv, bionic)
{
    cr_assert_eq(my_unsetenv("test-variable"), 0);

    char a[] = "a";
    char b[] = "b";
    char c[] = "c";

    cr_assert_eq(my_setenv("test-variable", a, 0), 0);
    cr_assert_str_eq(my_getenv("test-variable"), a);

    cr_assert_eq(my_setenv("test-variable", b, 0), 0);
    cr_assert_str_eq(my_getenv("test-variable"), a);

    cr_assert_eq(my_setenv("test-variable", c, 1), 0);
    cr_assert_str_eq(my_getenv("test-variable"), c);

    cr_assert_str_eq(a, "a");
    cr_assert_str_eq(b, "b");
    cr_assert_str_eq(c, "c");

    cr_assert_eq(my_unsetenv("test-variable"), 0);
}
