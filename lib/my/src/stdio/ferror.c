/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines ferror
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

int my_ferror(MY_FILE *stream)
{
    return (ferror(stream));
}

#else

int my_ferror(MY_FILE *stream)
{
    return stream->flag & MY_FILE_FLAG_ERROR;
}

#endif
