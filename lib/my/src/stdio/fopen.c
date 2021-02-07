/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fopen
*/

#include "my/stdio.h"
#include "my/unistd.h"
#include "my/fcntl.h"
#include "my/cpp-like/iterator.h"
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#if LIBMY_USE_LIBC_FILE

MY_FILE *my_fopen(const char *filename, const char *mode)
{
    return (fopen(filename, modes));
}

#else

static int make_file(const char *filename, bool read_write)
{
    int result = my_creat(filename, 0666);

    if (read_write && result >= 0) {
        my_close(result);
        result = my_open(filename, O_RDWR);
    }
    return (result);
}

static MY_FILE *finish_open(MY_FILE *file, int fd, bool read_write, bool read)
{
    if (fd < 0)
        return (NULL);
    file->buffer_count = 0;
    file->fd = fd;
    if (read_write)
        file->flag |= MY_FILE_FLAG_READ_WRITE;
    else if (read)
        file->flag |= MY_FILE_FLAG_READ;
    else
        file->flag |= MY_FILE_FLAG_WRITE;
    return (file);
}

static MY_FILE *do_open(MY_FILE *file, const char *filename, const char *mode,
    bool read_write)
{
    int fd;

    switch (*mode) {
    case 'w':
        fd = make_file(filename, read_write);
        break;
    case 'a':
        fd = my_open(filename, read_write ? O_RDWR : O_WRONLY);
        if (fd < 0 && errno == ENOENT)
            fd = make_file(filename, read_write);
        if (fd >= 0)
            my_lseek(fd, 0, SEEK_END);
        break;
    case 'r':
        fd = my_open(filename, read_write ? O_RDWR : O_RDONLY);
        break;
    default:
        return (NULL);
    }
    return (finish_open(file, fd, read_write, *mode == 'r'));
}

MY_FILE *my_fopen(const char *filename, const char *mode)
{
    MY_FILE *result;

    for (result = &g_my_files[0]; result->flag & (MY_FILE_FLAG_READ |
        MY_FILE_FLAG_WRITE | MY_FILE_FLAG_READ_WRITE); ++result)
        if (result == &g_my_files[MY_ARRAY_SIZE(g_my_files) - 1])
            return (NULL);
    return (do_open(result, filename, mode, mode[1] == '+'));
}

#endif
