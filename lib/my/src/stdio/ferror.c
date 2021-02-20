/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines ferror
*/

#include "my/stdio.h"
#include <stdbool.h>

#if LIBMY_USE_LIBC_FILE

int my_ferror(my_file_t *fp)
{
    return (ferror(fp));
}
#else
int my_ferror(my_file_t *fp)
{
    return ((bool)(fp->flags & MY_FILE_FLAG_ERROR));
}
#endif
