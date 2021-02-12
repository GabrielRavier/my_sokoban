/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines do_read
*/

#include "my/internal/stdio.h"
#include "my/cpp-like/limits.h"

#if !LIBMY_USE_LIBC_FILE

ssize_t my_internal_file_do_read(MY_FILE *fp, unsigned char *buffer,
    ssize_t count)
{
    ssize_t read_result = fp->read(fp->internal_data, buffer, count);

    if (read_result > 0) {
        if (fp->flags & MY_FILE_FLAG_IS_OFFSET_CORRECT) {
            if (fp->offset <= MY_NUMERIC_LIMITS_MAX(off_t) - read_result)
                fp->offset += read_result;
            else
                fp->flags &= ~MY_FILE_FLAG_IS_OFFSET_CORRECT;
        }
    } else if (read_result < 0)
        fp->flags &= ~MY_FILE_FLAG_IS_OFFSET_CORRECT;
    return (read_result);
}

#endif
