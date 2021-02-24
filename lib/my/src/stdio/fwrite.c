/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fwrite
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

size_t my_fwrite(const void *MY_RESTRICT buffer, size_t size, size_t count,
    my_file_t *fp)
{
    return (fwrite(buffer, size, count, fp));
}
#else
size_t my_fwrite(const void *MY_RESTRICT buffer_param, size_t size,
    size_t count, my_file_t *fp)
{
    size_t result = 0;
    __auto_type buffer = (unsigned char *)buffer_param;

    if (size)
        for (; result < count; ++result) {
            for (size_t i = 0; i < size; ++i)
                my_putc(*buffer++, fp);
            if (my_ferror(fp))
                break;
        }
    return (result);
}
#endif
