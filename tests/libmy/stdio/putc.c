/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests putc
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/string.h"
#include <criterion/redirect.h>
#include <unistd.h>

static void midnight_bsd_do_test_str(int (*func)(int, my_file_t *))
{
    const char *str = "1234567890x";
    const char *path = tmpnam(NULL);

    char buf[10];
    my_memset(buf, 'x', sizeof(buf));

    my_file_t *fp = my_fopen(path, "w+");
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

// Note: The original for these also has tests for putc_unlocked
Test(my_putc, midnight_bsd_str)
{
    midnight_bsd_do_test_str(my_putc);
}

Test(my_fputc, midnight_bsd_str)
{
    midnight_bsd_do_test_str(my_fputc);
}

#if !LIBMY_USE_LIBC_FILE

static void midnight_bsd_do_test_err(int (*func)(int, my_file_t *))
{
    const char *path = tmpnam(NULL);
    my_file_t *fp = my_fopen(path, "w+");

    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_fclose(fp), 0);
    cr_assert_eq(unlink(path), 0);
    cr_assert_eq(func('x', fp), EOF);
}

Test(my_putc, midnight_bsd_err)
{
    midnight_bsd_do_test_err(my_putc);
}

Test(my_fputc, midnight_bsd_err)
{
    midnight_bsd_do_test_err(my_fputc);
}

#endif

// TODO Add first gnulib tests when we get to setvbuf
// TODO Add second gnulib tests when we get to fdopen+setvbuf

static void dietlibc_do_test(int (*func)(int, my_file_t *))
{
    cr_assert_lt(func('x', my_stdin), 0);
    my_fflush(NULL);
    cr_assert_neq(my_ferror(my_stdin), 0);
}

Test(my_putc, dietlibc)
{
    dietlibc_do_test(my_putc);
}

Test(my_fputc, dietlibc)
{
    dietlibc_do_test(my_fputc);
}

// TODO Add cloudlibc tests when we get to fdopen

static void glibc_do_unbputc_test(int (*func)(int, my_file_t *))
{
    func('1', my_stderr);
    func('2', my_stderr);

    cr_assert_stderr_eq_str("12");
}

Test(my_putc, glibc_unbputc, .init = cr_redirect_stderr)
{
    glibc_do_unbputc_test(my_putc);
}

Test(my_fputc, glibc_unbputc, .init = cr_redirect_stderr)
{
    glibc_do_unbputc_test(my_fputc);
}

static void bionic_do_read_test(int (*func)(int, my_file_t *))
{
    my_file_t *fp = my_fopen("/proc/version", "r");

    cr_assert_neq(fp, NULL);
    cr_assert_eq(func('x', fp), EOF);
    cr_assert_eq(my_fclose(fp), 0);
}

Test(my_putc, bionic_read)
{
    bionic_do_read_test(my_putc);
}

Test(my_fputc, bionic_read)
{
    bionic_do_read_test(my_fputc);
}

static void wine_do_test(int (*func)(int, my_file_t *))
{
    char *temp_filename = tempnam(NULL, "wputc");
    my_file_t *fp = my_fopen(temp_filename, "wb");

    cr_assert_neq(fp, NULL);
    cr_assert_eq(func(0, fp), 0);
    cr_assert_eq(func(0xFF, fp), 0xff);
    cr_assert_eq(func(0xFFFFFFFF, fp), 0xFF);
    cr_assert_eq(my_fclose(fp), 0);

    fp = my_fopen(temp_filename, "rb");
    cr_assert_eq(func(0, fp), EOF);
    cr_assert_eq(my_fclose(fp), 0);

    unlink(temp_filename);
    free(temp_filename);
}

Test(my_putc, wine)
{
    wine_do_test(my_putc);
}

Test(my_fputc, wine)
{
    wine_do_test(my_fputc);
}
