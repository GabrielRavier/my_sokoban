/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests putc
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/string.h"
#include <unistd.h>

static void midnight_bsd_do_test_str(int (*func)(int, MY_FILE *))
{
    const char *str = "1234567890x";
    const char *path = tmpnam(NULL);

    char buf[10];
    my_memset(buf, 'x', sizeof(buf));

    MY_FILE *fp = my_fopen(path, "w+");
    cr_assert_neq(fp, NULL);

    for (size_t i = 0; str[i] != 'x'; ++i)
        cr_assert_eq(func(str[i], fp), str[i]);

    cr_assert_eq(my_fclose(fp), 0);

    FILE *check = fopen(path, "r");
    cr_assert_neq(check, NULL);

    cr_assert_eq(fread(buf, 1, 10, check), 10);
    cr_assert_eq(my_strncmp(buf, str, 10), 0);
    cr_assert_eq(fclose(check), 0);
    cr_assert_eq(unlink(path), 0);
}

static void midnight_bsd_do_test_err(int (*func)(int, MY_FILE *))
{
    const char *path = tmpnam(NULL);
    MY_FILE *fp = my_fopen(path, "w+");

    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_fclose(fp), 0);
    cr_assert_eq(unlink(path), 0);
    cr_assert_eq(func('x', fp), EOF);
}

// Note: The original for these also has tests for putc_unlocked
Test(my_putc, midnight_bsd_str)
{
    midnight_bsd_do_test_str(my_putc);
}

Test(my_fputc, midnight_bsd_str)
{
    midnight_bsd_do_test_str(my_fputc);
}

Test(my_putc, midnight_bsd_err)
{
    midnight_bsd_do_test_err(my_putc);
}

Test(my_fputc, midnight_bsd_err)
{
    midnight_bsd_do_test_err(my_fputc);
}
