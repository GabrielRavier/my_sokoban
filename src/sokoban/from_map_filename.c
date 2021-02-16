/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_from_map_filename
*/

#include "from_map_filename.h"
#include "from_map_string.h"
#include "../filename_to_string.h"
#include "my/my_string.h"
#include "my/stdio.h"
#include <unistd.h>

int sokoban_from_map_filename(const char *filename)
{
    struct my_string *map_string = filename_to_string(filename);
    int result;

    if (map_string == NULL) {
        my_dputs("Failure to read map file\n", STDERR_FILENO);
        return (84);
    }
    result = sokoban_from_map_string(map_string);
    my_string_free(map_string);
    return (result);
}
