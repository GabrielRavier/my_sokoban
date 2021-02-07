/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fopen
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"
#include "my/fcntl.h"
#include "my/unistd.h"
#include <fcntl.h>
#include <stdbool.h>

#if LIBMY_USE_LIBC_FILE

MY_FILE *my_fopen(const char *filename, const char *mode)
{
    return (fopen(filename, modes));
}

#else

static MY_FILE *finish(MY_FILE *result, int fd, bool read_write, bool is_read)
{
    result->buffer_ptr = NULL;
    result->buffer_base = NULL;
    result->buffer_count = 0;
    result->buffer_size = 0;
    result->fd = fd;
    result->flag = (read_write) ? MY_FILE_FLAG_READ_WRITE : is_read ?
        MY_FILE_FLAG_READ : MY_FILE_FLAG_WRITE;
    return (result);
}

MY_FILE *my_fopen(const char *filename, const char *mode)
{
    MY_FILE *result = my_internal_find_file_ptr();
    bool read_write;
    int open_flags;
    int fd;

    if (result == NULL)
        return (NULL);
    read_write = mode[1] == '+';
    if (*mode != 'a' && *mode != 'r' && *mode != 'w')
        return (NULL);
    open_flags = (*mode == 'a') ? (O_CREAT | (read_write ? O_RDWR : O_WRONLY)) :
        (*mode == 'r') ? (read_write ? O_RDWR : O_RDONLY) : O_TRUNC | O_CREAT |
        (read_write ? O_RDWR : O_WRONLY);
    fd = my_open(filename, open_flags, 0666);
    if (fd < 0)
        return (NULL);
    if (*mode == 'a')
        my_lseek(fd, 0, SEEK_END);
    return (finish(result, fd, read_write, *mode == 'r'));
}

#endif
