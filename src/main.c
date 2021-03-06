/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines main
*/

#include "sokoban/from_map_filename.h"
#include "my/getopt.h"
#include "my/stdio.h"
#include <unistd.h>
#include <stdbool.h>

enum {
    ERROR_MAIN_RETVAL = 84,
};

static void usage(const char *argv0)
{
    my_printf("USAGE\n\t%s map\nDESCRIPTION\n\tmap  file representing the"
        " warehouse map, containing '#' for walls,\n\t     "
        "'P' for the player, 'X' for boxes and 'O' for storage locations.\n",
        argv0);
}

int main(int argc, char *argv[])
{
    int getopt_result;

    do {
        getopt_result = my_getopt(argc, argv, "h");
        if (getopt_result == 'h') {
            usage(argv[0]);
            return (0);
        }
        if (getopt_result == '?') {
            usage(argv[0]);
            return (ERROR_MAIN_RETVAL);
        }
    } while (getopt_result != -1);
    if (argv[optind] == NULL || argv[optind + 1] != NULL) {
        usage(argv[0]);
        return (ERROR_MAIN_RETVAL);
    }
    return (sokoban_from_map_filename(argv[optind]));
}
