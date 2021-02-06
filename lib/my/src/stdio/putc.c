/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines putc
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"

#if LIBMY_USE_LIBC_FILE

int my_putc(int c, MY_FILE *stream)
{
    return (putc(c, stream));
}

#else

int my_putc(int c, MY_FILE *stream)
{
    return (--stream->buffer_count >= 0 ? *stream->buffer_ptr++ = (unsigned)c :
        my_internal_file_flush((unsigned)c, stream));
}

#endif
