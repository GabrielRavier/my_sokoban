/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines write
*/

#include "my/unistd.h"
#include <unistd.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_WRITE

ssize_t my_write(int fd, const void *buffer, size_t num_bytes)
{
    return (write(fd, buffer, num_bytes));
}
#else
ssize_t my_write(int fd, const void *buffer, size_t num_bytes)
{
    errno = ENOSYS;
    return (-1);
}
#endif
