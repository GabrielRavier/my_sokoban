/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines normal_seek
*/

#include "my/internal/stdio.h"
#include "my/stdio.h"
#include "my/unistd.h"

#if !LIBMY_USE_LIBC_FILE

my_fpos_t my_internal_file_normal_seek(void *internal_data, my_fpos_t offset,
    int whence)
{
    MY_FILE *fp = (MY_FILE *)internal_data;

    return (my_lseek(my_fileno(fp), (off_t)offset, whence));
}

#endif
