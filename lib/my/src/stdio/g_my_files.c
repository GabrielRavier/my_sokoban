/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines g_my_files
*/

#include "my/stdio.h"
#include <unistd.h>

// stdin, stdout and stderr have special info for them
MY_FILE g_my_files[1024] = {
    [0] = {.flag = MY_FILE_FLAG_READ, .fd = STDIN_FILENO},
    [1] = {.flag = MY_FILE_FLAG_WRITE, .fd = STDOUT_FILENO},
    [2] = {.flag = MY_FILE_FLAG_WRITE | MY_FILE_FLAG_NOT_BUFFERED,
        .fd = STDERR_FILENO},
};
