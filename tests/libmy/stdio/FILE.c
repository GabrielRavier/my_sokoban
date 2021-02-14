/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines misc tests for FILE stuff
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <errno.h>

// Add the rest of this once we have fprintf, fwprintf, fwrite, fputs or fputwc
Test(my_stdio, bionic_cantwrite)
{
    MY_FILE *fp = my_fopen("/proc/version", "r");

    errno = 0;
    cr_assert_eq(my_putc('x', fp), EOF);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fputc('x', fp), EOF);
    cr_assert_eq(errno, EBADF);
}

static void cloudlibc_do_random_test(MY_FILE *fp)
{
    char contents[1024] = {0};
    bool has_error = false;
    off_t offset = 0;
    off_t length = 0;

    for (size_t i = 0; i < 10000; ++i) {
        switch (random() % 4) {
        case 0:
            cr_assert_eq((bool)my_ferror(fp), has_error);
            break;
        case 1:
            cr_assert_eq(my_fflush(fp), 0);
            break;
        case 2:
            if (offset < sizeof(contents)) {
                unsigned int c = random();
                cr_assert_eq(my_fputc(c, fp), (unsigned char)c);
                contents[offset++] = c;
                if (length < offset)
                    length = offset;
            }
        case 3:
            if (offset < sizeof(contents)) {
                unsigned int c = random();
                cr_assert_eq(my_putc(c, fp), (unsigned char)c);
                contents[offset++] = c;
                if (length < offset)
                    length = offset;
            }
        }
        cr_assert_geq(offset, 0);
        cr_assert_leq(offset, sizeof(contents));
        cr_assert_geq(length, 0);
        cr_assert_leq(length, sizeof(contents));
    }
    cr_assert_eq(my_fclose(fp), 0);
}

Test(my_stdio, cloudlibc_random)
{
    char *filename = tmpnam(NULL);

    for (size_t i = 0; i < 100; ++i) {
        MY_FILE *fp = my_fopen(filename, "w+");
        cloudlibc_do_random_test(fp);
    }
}
