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

static bool parse_first_char(char first_char, int *open_flags_read_write_type,
    int *open_flags_always)
{
    switch (first_char) {
    case 'r':
        *open_flags_read_write_type = O_RDONLY;
        *open_flags_always = 0;
        break;
    case 'w':
    case 'a':
        *open_flags_read_write_type = O_WRONLY;
        *open_flags_always = O_CREAT | (first_char == 'w' ? O_TRUNC : O_APPEND);
        break;
    default:
        return (false);
    }
    return (true);
}

// Having + meaning read and write. We ignore b
int my_internal_file_parse_mode(const char *mode, int *open_flags)
{
    int open_flags_read_write_type;
    int open_flags_always;

    if (!parse_first_char(mode[0], &open_flags_read_write_type,
        &open_flags_always)) {
        errno = EINVAL;
        return (0);
    }
    if (mode[1] == '+' || (mode[1] == 'b' && mode[2] == '+'))
        open_flags_read_write_type = O_RDWR;
    *open_flags = open_flags_read_write_type | open_flags_always;
    return ((open_flags_read_write_type == O_WRONLY) ? MY_FILE_FLAG_WRITE :
        (open_flags_read_write_type == O_RDONLY) ? MY_FILE_FLAG_READ :
        MY_FILE_FLAG_READ_WRITE);
}
#endif
