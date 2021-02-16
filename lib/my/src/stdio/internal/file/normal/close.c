/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines normal_close
*/

#include "my/internal/stdio.h"
#include "my/unistd.h"

#if !LIBMY_USE_LIBC_FILE

int my_internal_file_normal_close(void *internal_data)
{
    return (my_close(my_fileno((MY_FILE *)internal_data)));
}
#endif
