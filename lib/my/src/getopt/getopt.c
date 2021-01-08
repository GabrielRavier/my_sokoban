/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines getopt
*/

#include "my/getopt.h"
#include "my/stdio.h"
#include "my/string.h"
#include "my/ctype.h"
#include <unistd.h>
#include <stdbool.h>

struct do_option_args {
    char **argv;
    const char *optstring;
    const char *option;
    const char *argument;
    int *optposition;
};

// Returns whether we should return early
static bool do_option_with_arg(const struct do_option_args *args)
{
    if (args->argument[*args->optposition + 1] != '\0') {
        ++optind;
        optarg = (char *)&args->argument[*args->optposition + 1];
        *args->optposition = 1;
    } else {
        if (args->argv[optind + 1] == NULL) {
            if (opterr && *args->optstring != ':')
                my_dprintf(STDERR_FILENO,
                    "%s: option requires an argument: %c\n", args->argv[0],
                    optopt);
            return (false);
        }
        *args->optposition = 1;
        optind += 2;
        optarg = args->argv[optind - 1];
    }
    return (true);
}

static int do_option(const struct do_option_args *args)
{
    if (args->option[1] == ':')
        return (do_option_with_arg(args) ? (optopt) : (*args->optstring == ':' ?
            ':' : '?'));
    if (args->argument[++*args->optposition] == '\0') {
        *args->optposition = 1;
        ++optind;
    }
    return (optopt);
}

static bool check_ret_min_1(const char *argument)
{
    if (argument && (my_strcmp(argument, "--") == 0)) {
        ++optind;
        return (true);
    }
    if (argument == NULL || argument[0] != '-' || !my_isalnum(argument[1]))
        return (true);
    return (false);
}

int my_getopt(int argc, char **argv, const char *optstring)
{
    static int optposition = 1;
    const char *argument;
    const char *option;

    (void)argc;
    if (optind == 0) {
        optind = 1;
        optposition = 1;
    }
    argument = argv[optind];
    if (check_ret_min_1(argument))
        return (-1);
    optopt = argument[optposition];
    option = my_strchr(optstring, optopt);
    if (option)
        return (do_option(&((const struct do_option_args){argv, optstring,
            option, argument, &optposition})));
    if (opterr && *optstring != ':')
        my_dprintf(STDERR_FILENO, "%s: illegal option: %c\n", argv[0], optopt);
    return ('?');
}
