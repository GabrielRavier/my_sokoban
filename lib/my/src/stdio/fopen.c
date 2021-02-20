/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fopen
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"
#include "my/fcntl.h"
#include <fcntl.h>

#if LIBMY_USE_LIBC_FILE

my_file_t *my_fopen(const char *filename, const char *mode)
{
    return (fopen(filename, mode));
}
#else
static void setup_functions(my_file_t *fp)
{
    fp->internal_data = fp;
    fp->read = &my_internal_file_normal_read;
    fp->write = &my_internal_file_normal_write;
    fp->seek = &my_internal_file_normal_seek;
    fp->close = &my_internal_file_normal_close;
}

// We seek to the end on O_APPEND so that ftell gets the right result.
my_file_t *my_fopen(const char *filename, const char *mode)
{
    int open_flags;
    int file_flags = my_internal_file_parse_mode(mode, &open_flags);
    my_file_t *fp;

    if (file_flags == 0)
        return (NULL);
    fp = my_internal_file_find_ptr();
    fp->fd = my_open(filename, open_flags, 0666);
    if (my_fileno(fp) < 0) {
        fp->flags = 0;
        return (NULL);
    }
    fp->flags = file_flags;
    setup_functions(fp);
    if (open_flags & O_APPEND)
        fp->seek(fp->internal_data, 0, SEEK_END);
    return (fp);
}
#endif
