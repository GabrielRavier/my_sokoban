/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fileno
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

Test(my_fileno, illumos)
{
    cr_assert_eq(my_fileno(my_stdin), STDIN_FILENO);
    cr_assert_eq(my_fileno(my_stdout), STDOUT_FILENO);
    cr_assert_eq(my_fileno(my_stderr), STDERR_FILENO);
}

Test(my_fileno, bionic_invalidated_fd)
{
    cr_assert_eq(my_fclose(my_stdin), 0);
    errno = 0;
    cr_assert_eq(my_fileno(my_stdin), -1);
    cr_assert_eq(errno, EBADF);
}

// TODO: Add relevent illumos tests when we support fmemopen, open_memstream,
// open_wmemstream, fdopen or freopen
// TODO: Add relevant cloudlibc tests when we support fdopen or fmemopen
