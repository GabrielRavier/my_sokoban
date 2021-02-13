/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines write_to_buffer
*/

#include "my/internal/stdio.h"
#include <errno.h>

#if !LIBMY_USE_LIBC_FILE

// We set write_space_left to make sure we couldn't possibly overflow it with
// sufficient putc calls (if we can't write)
// We then check whether the buffer is completely full and flush if that is the
// case, or if the buffer is completely full after adding c, or if the file is
// line buffered and c == '\n' 
// The unbuffered case is taken care of by its one byte buffer, which will
// always be full after putting c into it
int my_internal_file_write_to_buffer(MY_FILE *fp, int c)
{
    unsigned char c_uchar = c;
    ssize_t bytes_in_buffer = fp->buffer_ptr - fp->buffer.base;

    fp->write_space_left = fp->line_buffer_size;
    if (!my_internal_file_can_write(fp)) {
        errno = EBADF;
        return (EOF);
    }
    if (bytes_in_buffer >= fp->buffer.size) {
        if (my_fflush(fp) != 0)
            return (EOF);
        bytes_in_buffer = 0;
    }
    --fp->write_space_left;
    *fp->buffer_ptr++ = c_uchar;
    return (((++bytes_in_buffer == fp->buffer.size || (fp->flags &
        MY_FILE_FLAG_LINE_BUFFERED && c_uchar == '\n')) &&
        (my_fflush(fp) != 0)) ? EOF : c_uchar);
}

#endif
