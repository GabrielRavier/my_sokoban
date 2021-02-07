/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines internal_find_file_ptr
*/

#include "my/internal/stdio.h"
#include "my/cpp-like/iterator.h"
#include <errno.h>
#include <stdbool.h>

#if !LIBMY_USE_LIBC_FILE

static bool is_active(MY_FILE *stream)
{
    return stream->flag & (MY_FILE_FLAG_READ | MY_FILE_FLAG_WRITE |
        MY_FILE_FLAG_READ_WRITE);
}

// TODO implement some function to make more files. Note: Change name of
// g_my_files if this occurs as this would make anything that relies on it not
// work properly
MY_FILE *my_internal_find_file_ptr(void)
{
    MY_FILE **i_glue;

    for (MY_FILE *i = &g_my_files[0]; i <
        &g_my_files[MY_ARRAY_SIZE(g_my_files)]; ++i)
        if (!is_active(i))
            return (i);
    errno = ENOMEM;
    return (NULL);
}

#endif
