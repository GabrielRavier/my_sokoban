/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines dgetc
*/

#include "my/stdio.h"
#include <unistd.h>

int my_dgetc(int fd)
{
    unsigned char result;
    if (read(fd, &result, sizeof(result)) < (ssize_t)sizeof(result))
        return (EOF);
    return (result);
}
