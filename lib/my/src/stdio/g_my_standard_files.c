/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines g_my_files
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"
#include <unistd.h>


#if !LIBMY_USE_LIBC_FILE

// This is to make sure cleanup is referenced whenever someone uses my_file_t
// interfaces
const void (*g_my_internal_file_standard_files_cleanup_reference)(void) =
    &my_internal_file_cleanup;

// stdin, stdout and stderr have special info for them at program initialization
// time
my_file_t g_my_standard_files[3] = {
    [STDIN_FILENO] = {.fd = STDIN_FILENO, .flags = MY_FILE_FLAG_READ,
        .internal_data = g_my_standard_files + STDIN_FILENO,
        .read = &my_internal_file_normal_read,
        .write = &my_internal_file_normal_write,
        .seek = &my_internal_file_normal_seek,
        .close = &my_internal_file_normal_close},
    [STDOUT_FILENO] = {.fd = STDOUT_FILENO, .flags = MY_FILE_FLAG_WRITE,
        .internal_data = g_my_standard_files + STDOUT_FILENO,
        .read = &my_internal_file_normal_read,
        .write = &my_internal_file_normal_write,
        .seek = &my_internal_file_normal_seek,
        .close = &my_internal_file_normal_close},
    [STDERR_FILENO] = {.fd = STDERR_FILENO,
        .flags = MY_FILE_FLAG_WRITE | MY_FILE_FLAG_NOT_BUFFERED,
        .internal_data = g_my_standard_files + STDERR_FILENO,
        .read = &my_internal_file_normal_read,
        .write = &my_internal_file_normal_write,
        .seek = &my_internal_file_normal_seek,
        .close = &my_internal_file_normal_close},
};
#endif
