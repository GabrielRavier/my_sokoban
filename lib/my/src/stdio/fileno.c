/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fileno
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

int my_fileno(MY_FILE *fp)
{
    return (fileno(fp));
}

#else

int my_fileno(MY_FILE *fp)
{
    return fp->fd;
}

#endif
