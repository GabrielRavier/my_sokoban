/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fileno
*/

#include "../tests_header.h"
#include "my/stdio.h"
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

// TODO: Add relevent illumos tests when we support fmemopen, open_memstream,
// open_wmemstream, fdopen or freopen
// TODO: Add relevant cloudlibc tests when we support fdopen or fmemopen
