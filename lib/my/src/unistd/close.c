/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines close
*/

#include "my/unistd.h"
#include <unistd.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_CLOSE

int my_close(int fd)
{
    return (close(fd));
}
#else

int my_close(int fd)
{
    errno = ENOSYS;
    return (-1);
}
#endif
