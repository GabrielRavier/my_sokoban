/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines creat
*/

#include "my/fcntl.h"
#include <fcntl.h>

int my_creat(const char *pathname, mode_t mode)
{
    return my_open(pathname, O_CREAT | O_WRONLY | O_TRUNC, mode);
}
