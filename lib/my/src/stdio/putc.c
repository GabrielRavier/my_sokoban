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
    if (--stream->buffer_count >= 0) {
        *stream->buffer_ptr++ = c;
        return ((unsigned char)c);
    }
    return (my_internal_file_flush(c, stream));
}

#endif
