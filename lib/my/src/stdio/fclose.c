/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fclose
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"
#include "my/stdlib.h"
#include <errno.h>

#if LIBMY_USE_LIBC_FILE

int my_fclose(MY_FILE *fp)
{
    return (fclose(fp));
}
#else

// First checks whether fp is open, then closes the file and frees it
// We set write_space_left to make sure we error if re-accessed
int my_fclose(MY_FILE *fp)
{
    int result;

    if (fp->flags == 0) {
        errno = EBADF;
        return (EOF);
    }
    result = fp->flags & MY_FILE_FLAG_WRITE ?
        my_internal_file_flush_skip_non_write(fp) : 0;
    if (fp->close != NULL && fp->close(fp->internal_data) < 0)
        result = EOF;
    if (fp->flags & MY_FILE_FLAG_BUFFER_MALLOCED)
        my_free(fp->buffer.base);
    fp->write_space_left = 0;
    fp->fd = -1;
    fp->flags = 0;
    return (result);
}
#endif
