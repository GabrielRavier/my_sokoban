/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fclose
*/

#include "my/stdio.h"
#include "my/cpp-like/iterator.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <errno.h>

#if LIBMY_USE_LIBC_FILE

int my_fclose(MY_FILE *file)
{
    return (fclose(file));
}

#else

int my_fclose(MY_FILE *file)
{
    int result = EOF;

    if (file->flag & (MY_FILE_FLAG_READ | MY_FILE_FLAG_WRITE |
        MY_FILE_FLAG_READ_WRITE)) {
        result = my_fflush(file);
        if (my_close(file->fd) < 0)
            result = EOF;
        if (file->flag & MY_FILE_FLAG_BUFFER_MALLOCED)
            my_free(file->buffer_base);
    }
    file->buffer_count = 0;
    file->buffer_base = NULL;
    file->buffer_ptr = NULL;
    file->buffer_size = 0;
    file->flag = 0;
    file->fd = 0;
    return (result);
}

static __attribute__((destructor)) void cleanup_all_files(void)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(g_my_files); ++i)
        my_fclose(&g_my_files[i]);
}

#endif
