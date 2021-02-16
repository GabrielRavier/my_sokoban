/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines normal_write
*/

#include "my/internal/stdio.h"
#include "my/stdio.h"
#include "my/unistd.h"

#if !LIBMY_USE_LIBC_FILE

ssize_t my_internal_file_normal_write(void *internal_data,
    const unsigned char *buffer, ssize_t count)
{
    MY_FILE *fp = (MY_FILE *)internal_data;

    return (my_write(my_fileno(fp), buffer, count));
}
#endif
