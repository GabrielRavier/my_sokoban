/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines lseek
*/

#include "my/unistd.h"
#include <unistd.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_LSEEK

off_t my_lseek(int fd, off_t offset, int whence)
{
    return (lseek(fd, offset, whence));
}

#else

off_t my_lseek(int fd, off_t offset, int whence)
{
    errno = ENOSYS;
    return ((off_t)-1);
}

#endif
