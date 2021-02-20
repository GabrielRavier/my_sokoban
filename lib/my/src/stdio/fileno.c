/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fileno
*/

#include "my/stdio.h"
#include <errno.h>

#if LIBMY_USE_LIBC_FILE

int my_fileno(my_file_t *fp)
{
    return (fileno(fp));
}
#else
int my_fileno(my_file_t *fp)
{
    int result = fp->fd;

    if (result == -1)
        errno = EBADF;
    return (result);
}
#endif
