/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fileno
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

int my_fileno(MY_FILE *stream)
{
    return (fileno(stream));
}

#else

int my_fileno(MY_FILE *stream)
{
    return stream->fd;
}

#endif
