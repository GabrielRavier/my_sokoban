/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines flush_skip_non_write
*/

#include "my/internal/stdio.h"

#if !LIBMY_USE_LIBC_FILE

int my_internal_file_flush_skip_non_write(my_file_t *fp)
{
    const unsigned char *base_it = fp->buffer.base;
    ssize_t bytes_written;
    ssize_t bytes_to_write = fp->buffer_ptr - fp->buffer.base;

    if (!(fp->flags & MY_FILE_FLAG_WRITE) || fp->buffer.base == NULL)
        return (0);
    fp->buffer_ptr = fp->buffer.base;
    fp->write_space_left = fp->flags & (MY_FILE_FLAG_NOT_BUFFERED |
        MY_FILE_FLAG_LINE_BUFFERED) ? 0 : fp->buffer.size;
    while (bytes_to_write > 0) {
        bytes_written = my_internal_file_do_write(fp->internal_data, base_it,
            bytes_to_write);
        if (bytes_written <= 0) {
            fp->flags |= MY_FILE_FLAG_ERROR;
            return (EOF);
        }
        bytes_to_write -= bytes_written;
        base_it += bytes_written;
    }
    return (0);
}
#endif
