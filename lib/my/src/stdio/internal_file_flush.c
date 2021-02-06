/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines internal_file_flush
*/

#include "my/internal/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <errno.h>
#include <stdbool.h>

#if !LIBMY_USE_LIBC_STDIO

static bool make_buffer(MY_FILE *file)
{
    static char stdout_buffer[BUFSIZ];

    if (file == my_stdout) {
        if (my_isatty(my_stdout->fd) || errno == ENOSYS) {
            file->flag |= MY_FILE_FLAG_NOT_BUFFERED;
            return (false);
        }
        file->buffer_base = stdout_buffer;
        file->buffer_ptr = stdout_buffer;
        return (false);
    }
    file->buffer_base = my_malloc(BUFSIZ);
    if (file->buffer_base == NULL) {
        file->flag |= MY_FILE_FLAG_NOT_BUFFERED;
        return (false);
    }
    file->flag |= MY_FILE_FLAG_BUFFER_MALLOCED;
    return (true);
}

static bool do_buffered(MY_FILE *file, ssize_t *bytes_to_write,
    ssize_t *bytes_written, int c)
{
    if (file->buffer_base == NULL) {
        if (!make_buffer(file))
            return (false);
    }
    else {
        *bytes_to_write = file->buffer_ptr - file->buffer_base;
        if (*bytes_to_write > 0) {
            file->buffer_ptr = file->buffer_base;
            *bytes_written = my_write(file->fd, file->buffer_base,
                *bytes_to_write);
        }
    }
    *file->buffer_base = c;
    file->buffer_ptr = file->buffer_base + 1;
    file->buffer_count = BUFSIZ - 1;
    return (true);
}

int my_internal_file_flush(int c, MY_FILE *file)
{
    ssize_t bytes_to_write = 0;
    ssize_t bytes_written = 0;
    char c_as_char = c;

    if (file->flag & MY_FILE_FLAG_READ_WRITE) {
        file->flag |= MY_FILE_FLAG_WRITE;
        file->flag &= ~MY_FILE_FLAG_EOF;
    }
    while (true) {
        if (file->flag & MY_FILE_FLAG_NOT_BUFFERED) {
            bytes_to_write = 1;
            bytes_written = my_write(file->fd, &c_as_char, bytes_to_write);
            file->buffer_count = 0;
        } else if (!do_buffered(file, &bytes_to_write, &bytes_written, c))
            continue;
        break;
    }
    if (bytes_to_write != bytes_written) {
        file->flag |= MY_FILE_FLAG_ERROR;
        return (EOF);
    }
    return ((unsigned char)c);
}

#endif
