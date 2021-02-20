/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines putc
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"

#if LIBMY_USE_LIBC_FILE

int my_putc(int c, my_file_t *fp)
{
    return (putc(c, fp));
}
#else

int my_putc(int c, my_file_t *fp)
{
    unsigned char c_uchar = c;

    if (--fp->write_space_left >= 0 || (fp->write_space_left >=
        fp->line_buffer_size && c_uchar != '\n')) {
        *fp->buffer_ptr++ = c_uchar;
        return (c_uchar);
    } else
        return (my_internal_file_write_to_buffer(fp, c));
}
#endif
