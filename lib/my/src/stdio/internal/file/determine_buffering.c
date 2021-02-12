/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines determin_buffering
*/

#include "my/internal/stdio.h"
#include "my/sys/stat.h"
#include <errno.h>

#if !LIBMY_USE_LIBC_FILE

// The file could be a tty if the file is a character device. Also, we only
// optimize fseek if it is a regular file and the seek function points to the
// "normal" seek function
int my_internal_file_determine_buffering(MY_FILE *fp, size_t *buffer_size,
    bool *could_be_tty)
{
    struct stat stat_buffer;

    if (fp->fd < 0 || my_fstat(fp->fd, &stat_buffer) < 0) {
        *could_be_tty = (fp == my_stdout && errno == ENOSYS);
        *buffer_size = BUFSIZ;
        return (MY_FILE_FLAG_NO_FSEEK_OPT);
    }
    *could_be_tty = S_ISCHR(stat_buffer.st_mode);
    if (stat_buffer.st_blksize <= 0) {
        *buffer_size = BUFSIZ;
        return (MY_FILE_FLAG_NO_FSEEK_OPT);
    }
    *buffer_size = stat_buffer.st_blksize;
    return (S_ISREG(stat_buffer.st_mode) && fp->seek ==
        &my_internal_file_normal_seek ? MY_FILE_FLAG_FSEEK_OPT :
        MY_FILE_FLAG_NO_FSEEK_OPT);
}

#endif
