/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines internal_file_flush
*/

#include "my/internal/stdio.h"
#include "my/cpp-like/algorithm.h"
#include "my/stdlib.h"
#include "my/sys/stat.h"
#include "my/unistd.h"
#include <errno.h>
#include <stdbool.h>

#if !LIBMY_USE_LIBC_STDIO

static bool make_buffer(MY_FILE *file)
{
    struct stat stat_buffer;

    file->buffer_size = my_fstat(my_fileno(file), &stat_buffer) < 0 ||
        stat_buffer.st_blksize < 0 ? BUFSIZ : stat_buffer.st_blksize;
    file->buffer_base = my_malloc(file->buffer_size);
    if (file->buffer_base == NULL) {
        file->flag |= MY_FILE_FLAG_NOT_BUFFERED;
        return (false);
    }
    file->flag |= MY_FILE_FLAG_BUFFER_MALLOCED;
    if (file == my_stdout && (my_isatty(my_fileno(my_stdout)) ||
        errno == ENOSYS)) {
        file->flag |= MY_FILE_FLAG_LINE_BUFFERED;
        file->buffer_ptr = file->buffer_base;
    }
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
            *bytes_written = my_write(my_fileno(file), file->buffer_base,
                *bytes_to_write);
        }
    }
    *file->buffer_base = c;
    file->buffer_ptr = file->buffer_base + 1;
    file->buffer_count = file->buffer_size - 1;
    return (true);
}

static bool do_line_buffered(MY_FILE *file, ssize_t *bytes_to_write,
    ssize_t *bytes_written, int c)
{
    if (file->flag & MY_FILE_FLAG_LINE_BUFFERED) {
        *file->buffer_ptr++ = c;
        if (file->buffer_ptr >= file->buffer_base + file->buffer_size ||
            c == '\n') {
            *bytes_to_write = file->buffer_ptr - file->buffer_base;
            *bytes_written = my_write(my_fileno(file), file->buffer_base,
                *bytes_to_write);
            file->buffer_ptr = file->buffer_base;
            file->buffer_count = 0;
        }
        return (true);
    }
    return (false);
}

static bool do_unbuffered(MY_FILE *file, ssize_t *bytes_to_write,
    ssize_t *bytes_written, int c)
{
    unsigned char c_as_uchar = c;

    if (file->flag & MY_FILE_FLAG_NOT_BUFFERED) {
        *bytes_to_write = 1;
        *bytes_written = my_write(my_fileno(file), &c_as_uchar,
            *bytes_to_write);
        file->buffer_count = 0;
        return (true);
    }
    return (false);
}

int my_internal_file_flush(int c, MY_FILE *file)
{
    ssize_t bytes_to_write = 0;
    ssize_t bytes_written = 0;

    if (file->flag & MY_FILE_FLAG_READ_WRITE) {
        file->flag |= MY_FILE_FLAG_WRITE;
        file->flag &= ~(MY_FILE_FLAG_EOF | MY_FILE_FLAG_READ);
    }
    if ((file->flag & MY_FILE_FLAG_WRITE) == 0)
        return (EOF);
    while (true)
        if (do_line_buffered(file, &bytes_to_write, &bytes_written, c) ||
            do_unbuffered(file, &bytes_to_write, &bytes_written, c) ||
            do_buffered(file, &bytes_to_write, &bytes_written, c))
            break;
    if (bytes_to_write != bytes_written) {
        file->flag |= MY_FILE_FLAG_ERROR;
        return (EOF);
    }
    return ((unsigned char)c);
}

#endif
