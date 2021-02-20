/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fstat
*/

#include "my/sys/stat.h"
#include <errno.h>

#if LIBMY_HAS_LIBC_FSTAT

int my_fstat(int fd, struct stat *buf)
{
    return (fstat(fd, buf));
}
#else
int my_fstat(int fd, struct stat *buf)
{
    errno = ENOSYS;
    return (-1);
}
#endif
