/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests putenv
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"

Test(my_putenv, freebsd_putenv_basic)
{
    char string[1024];

    my_strcpy(string, "crap=true");
    cr_assert_eq(putenv(string), 0);
    cr_assert_eq(my_getenv("crap"), getenv("crap"));
    string[1] = 'l';
    cr_assert_eq(my_getenv("clap"), getenv("clap"));
    cr_assert_eq(my_getenv("crap"), getenv("crap"));
    string[1] = 'r';
    cr_assert_eq(my_unsetenv("crap"), 0);
    cr_assert_eq(my_getenv("crap"), getenv("crap"));
}

Test(my_putenv, bionic)
{
    cr_assert_eq(my_unsetenv("a"), 0);

    char s1[] = "a=b";
    cr_assert_eq(putenv(s1), 0);
    cr_assert_str_eq(my_getenv("a"), "b");

    s1[2] = 'c';
    cr_assert_str_eq(my_getenv("a"), "c");

    char s2[] = "a=b";
    cr_assert_eq(putenv(s2), 0);
    cr_assert_str_eq(my_getenv("a"), "b");
    cr_assert_eq(s1[2], 'c');

    cr_assert_eq(my_unsetenv("a"), 0);
}
