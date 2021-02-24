/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines do_seek
*/

#include "my/internal/stdio.h"
#include <errno.h>

#if !LIBMY_USE_LIBC_FILE

static my_fpos_t finish_not_failed(my_file_t *fp, my_fpos_t seek_result)
{
    if (fp->flags & MY_FILE_FLAG_FSEEK_OPT) {
        fp->flags |= MY_FILE_FLAG_IS_OFFSET_CORRECT;
        fp->offset = seek_result;
    }
    return (seek_result);
}

my_fpos_t my_internal_file_do_seek(my_file_t *fp, my_fpos_t offset, int whence)
{
    int saved_errno = errno;
    int errno_from_seek;
    my_fpos_t seek_result;

    errno = 0;
    seek_result = fp->seek(fp->internal_data, offset, whence);
    errno_from_seek = errno;
    if (errno == 0)
        errno = saved_errno;
    if (seek_result < 0) {
        if (errno_from_seek == 0) {
            if (offset != 0 || whence != SEEK_CUR)
                fp->buffer_ptr = fp->buffer.base;
            fp->flags &= MY_FILE_FLAG_ERROR;
            errno = EINVAL;
        }
        fp->flags &= ~MY_FILE_FLAG_IS_OFFSET_CORRECT;
        return (-1);
    }
    return (finish_not_failed(fp, seek_result));
}
#endif
