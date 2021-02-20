/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines setup_write_buffer
*/

#include "my/internal/stdio.h"

#if !LIBMY_USE_LIBC_FILE

bool my_internal_file_setup_write(my_file_t *fp)
{
    if (!(fp->flags & MY_FILE_FLAG_WRITE)) {
        if (!(fp->flags & MY_FILE_FLAG_READ_WRITE)) {
            fp->flags |= MY_FILE_FLAG_ERROR;
            return (false);
        }
        if (fp->flags & MY_FILE_FLAG_READ) {
            fp->flags &= ~MY_FILE_FLAG_READ;
            fp->buffer_ptr = fp->buffer.base;
        }
        fp->flags |= MY_FILE_FLAG_WRITE;
    }
    if (fp->buffer.base == NULL)
        my_internal_file_make_buffer(fp);
    if (fp->flags & MY_FILE_FLAG_LINE_BUFFERED) {
        fp->write_space_left = 0;
        fp->line_buffer_size = -fp->buffer.size;
    } else
        fp->write_space_left = (fp->flags & MY_FILE_FLAG_NOT_BUFFERED) ? 0 :
            fp->buffer.size;
    return (true);
}
#endif
