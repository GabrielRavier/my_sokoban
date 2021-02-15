/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines make_buffer
*/

#include "my/internal/stdio.h"
#include "my/cpp-like/algorithm.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include "my/sys/stat.h"
#include <errno.h>

#if !LIBMY_USE_LIBC_FILE

static void finish(MY_FILE *fp, size_t buffer_size, bool could_be_tty,
    int buffer_flags)
{
    fp->buffer.base = my_malloc(buffer_size);
    if (fp->buffer.base == NULL) {
        fp->flags |= MY_FILE_FLAG_NOT_BUFFERED;
        my_internal_file_make_buffer(fp);
        return;
    }
    fp->flags |= MY_FILE_FLAG_BUFFER_MALLOCED;
    fp->buffer.size = buffer_size;
    fp->buffer_ptr = fp->buffer.base;
    if ((could_be_tty && my_isatty(my_fileno(fp))) || (fp == my_stdout &&
        errno == ENOSYS))
        fp->flags |= MY_FILE_FLAG_LINE_BUFFERED;
    fp->flags |= buffer_flags;
}

// If we're already unbuffered, that's easy to handle. Otherwise, determine the
// buffering, try to create a buffer (fallback to unbuffered if that's
// impossible) and handle ttys (if we don't have isatty and the call to it
// failed because we can't have it)
void my_internal_file_make_buffer(MY_FILE *fp)
{
    size_t buffer_size;
    int buffer_flags;
    bool could_be_tty;

    if (fp->flags & MY_FILE_FLAG_NOT_BUFFERED) {
        fp->buffer.base = fp->one_char_read_buffer;
        fp->buffer.size = 1;
        fp->buffer_ptr = fp->buffer.base;
        return;
    }
    buffer_flags = my_internal_file_determine_buffering(fp, &buffer_size,
        &could_be_tty);
    finish(fp, buffer_size, could_be_tty, buffer_flags);
}

#endif
