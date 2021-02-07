/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines flush
*/

#include "my/stdio.h"
#include "my/unistd.h"

#if LIBMY_USE_LIBC_FILE

int my_fflush(MY_FILE *file)
{
    return (fflush(file));
}

#else

int my_fflush(MY_FILE *file)
{
    ssize_t bytes_to_write;

    if ((file->flag & (MY_FILE_FLAG_NOT_BUFFERED | MY_FILE_FLAG_WRITE)) ==
        MY_FILE_FLAG_WRITE && file->buffer_base != NULL) {
        bytes_to_write = file->buffer_ptr - file->buffer_base;
        if (bytes_to_write <= 0)
            return (0);
        file->buffer_ptr = file->buffer_base;
        file->buffer_count = (file->flag & (MY_FILE_FLAG_LINE_BUFFERED |
            MY_FILE_FLAG_NOT_BUFFERED)) ? 0 : file->buffer_size;
        if (my_write(file->fd, file->buffer_base, bytes_to_write) !=
            bytes_to_write) {
            file->flag |= MY_FILE_FLAG_ERROR;
            return (EOF);
        }
    }
    return (0);
}

#endif
