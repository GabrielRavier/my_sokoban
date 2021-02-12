/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines flush
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"
#include <errno.h>

#if LIBMY_USE_LIBC_FILE

int my_fflush(MY_FILE *fp)
{
    return (fflush(fp));
}

#else

int my_fflush(MY_FILE *fp)
{
    if (fp == NULL)
        return (my_internal_file_all_for_each(
            my_internal_file_flush_skip_non_write));
    if (!(fp->flags & (MY_FILE_FLAG_WRITE | MY_FILE_FLAG_READ_WRITE))) {
        errno = EBADF;
        return (EOF);
    }
    return (my_internal_file_flush_skip_non_write(fp));
}

#endif
