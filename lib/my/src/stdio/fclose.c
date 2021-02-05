/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fclose
*/

#include "my/stdio.h"
#include <errno.h>

#if USE_LIBC_STDIO

int my_fclose(MY_FILE *stream)
{
    return (fclose(stream));
}

#else

int my_fclose(MY_FILE *stream)
{
    errno = ENOSYS;
    return (EOF);
}

#endif
