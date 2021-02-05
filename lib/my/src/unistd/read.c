/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines read
*/

#include "my/unistd.h"
#include <unistd.h>

#if LIBMY_HAS_LIBC_READ

ssize_t my_read(int fd, void *buffer, size_t num_bytes)
{
    return (read(fd, buffer, num_bytes));
}

#else

ssize_t my_read(int fd, void *buffer, size_t num_bytes)
{
    return (-1);
}

#endif
