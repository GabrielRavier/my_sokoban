/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines open
*/

#include "my/fcntl.h"
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_OPEN

int my_open(const char *pathname, int flags, ...)
{
    mode_t mode = 0;
    va_list arg;

    if (flags & O_CREAT) {
        va_start(arg, flags);
        mode = va_arg(arg, mode_t);
        va_end(arg);
    }
    return (open(pathname, flags, mode));
}
#else
int my_open(const char *pathname, int flags, ...)
{
    errno = ENOSYS;
    return (-1);
}
#endif
