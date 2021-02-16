/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines do_write
*/

#include "my/internal/stdio.h"

#if !LIBMY_USE_LIBC_FILE

// We unset the offset correct flag because of O_APPEND
ssize_t my_internal_file_do_write(MY_FILE *fp, const unsigned char *buffer,
    ssize_t count)
{
    ssize_t write_result = fp->write(fp->internal_data, buffer, count);

    fp->flags &= ~MY_FILE_FLAG_IS_OFFSET_CORRECT;
    return (write_result);
}
#endif
