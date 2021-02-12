/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines parse_mode
*/

#include "my/internal/stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#if !LIBMY_USE_LIBC_FILE

// r means read, w means write and a means append
static const int open_flags_no_plus_array[UCHAR_MAX] = {
    ['r'] = O_RDONLY,
    ['w'] = O_WRONLY,
    ['a'] = O_WRONLY,
};

static const int open_flags_always_array[UCHAR_MAX] = {
    ['r'] = 0,
    ['w'] = O_CREAT | O_TRUNC,
    ['a'] = O_CREAT | O_APPEND,
};

static const int file_flags_array[UCHAR_MAX] = {
    ['r'] = MY_FILE_FLAG_READ,
    ['w'] = MY_FILE_FLAG_WRITE,
    ['a'] = MY_FILE_FLAG_WRITE,
};

// Having + meaning read and write. We ignore b
int my_internal_file_parse_mode(const char *mode, int *open_flags)
{
    const unsigned char *mode_uchar = (const unsigned char *)mode;
    int open_flags_no_plus = open_flags_no_plus_array[mode_uchar[0]];
    int open_flags_always = open_flags_always_array[mode_uchar[0]];
    int file_flags = file_flags_array[mode_uchar[0]];

    if (open_flags_no_plus == 0) {
        errno = EINVAL;
        return (0);
    }
    if (mode[1] == '+' || (mode[1] == 'b' && mode[2] == '+')) {
        file_flags = MY_FILE_FLAG_READ_WRITE;
        open_flags_no_plus = O_RDWR;
    }
    *open_flags = open_flags_no_plus | open_flags_always;
    return (file_flags);
}

#endif
