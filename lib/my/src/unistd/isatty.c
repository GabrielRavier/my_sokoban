/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines isatty
*/

#include "my/unistd.h"
#include <unistd.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_ISATTY

int my_isatty(int fd)
{
    return (isatty(fd));
}

#else

int my_isatty(int fd)
{
    errno = ENOSYS;
    return (0);
}

#endif
