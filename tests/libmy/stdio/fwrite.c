/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fwrite
*/

#include "my/stdio.h"
#include "../tests_header.h"

Test(my_fwrite, dietlibc)
{
    char *name = tempnam(NULL, NULL);
    cr_assert_neq(name, NULL);

    my_file_t *fp = my_fopen(name, "wb");
    cr_assert_neq(fp, NULL);

    cr_assert_eq(my_fwrite("abcdefg", 1, 5, fp), 5);
    cr_assert_eq(my_fclose(fp), 0);
    free(name);
}

// Add tests from glibc when fdopen, tmpfile, getline is done
// Add tests from gnulib when setvbuf is done
