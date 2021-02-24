/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines misc tests for FILE stuff
*/

#include "../tests_header.h"
#include "my/cpp-like/algorithm.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <errno.h>

// Add the rest of this once we have fprintf, fwprintf, fputs or fputwc
Test(my_stdio, bionic_cantwrite)
{
    my_file_t *fp = my_fopen("/proc/version", "r");

    errno = 0;
    cr_assert_eq(my_putc('x', fp), EOF);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fputc('x', fp), EOF);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fwrite("hello", 1, 2, fp), 0);
    cr_assert_eq(errno, EBADF);
}

static void cloudlibc_random_pair(size_t max, size_t *a, size_t *b)
{
    size_t total = random() % (max + 1);
    *a = random() % (total + 1);
    *b = (*a == 0) ? random() : total / *a;
}

static void cloudlibc_do_random_test(my_file_t *fp)
{
    char contents[1024] = {0};
    bool has_error = false;
    off_t offset = 0;
    off_t length = 0;

    for (size_t i = 0; i < 10000; ++i) {
        switch (random() % 5) {
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
            break;
        case 3:
            if (offset < sizeof(contents)) {
                unsigned int c = random();
                cr_assert_eq(my_putc(c, fp), (unsigned char)c);
                contents[offset++] = c;
                if (length < offset)
                    length = offset;
            }
            break;
        case 4:
        {
            size_t size, count;
            cloudlibc_random_pair(sizeof(contents) - offset, &size, &count);

            char write_buffer[sizeof(contents)];
            size_t write_length = size * count;
            for (size_t i = 0; i < write_length; ++i)
                write_buffer[i] = random();

            size_t result = write_length == 0 ? 0 : count;
            cr_assert_eq(my_fwrite(write_buffer, size, count, fp), result);

            if (write_length != 0) {
                my_memcpy(contents + offset, write_buffer, write_length);
                offset += write_length;
                length = MY_MAX(length, offset);
            }
            break;
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
        my_file_t *fp = my_fopen(filename, "w+");
        cloudlibc_do_random_test(fp);
    }
}
