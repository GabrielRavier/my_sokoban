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

struct getopt_state {
    int argc;
    char **argv;
    const char *optstring;
    char argument_character;
    const char *optstring_argument_position;
    int *ptr_optposition;
};

static int do_found_option(struct getopt_state *state)
{
    if (state->optstring_argument_position[1] == ':') {
        if (state->argv[optind][*state->ptr_optposition + 1] != '\0')
            optarg = &state->argv[optind++][*state->ptr_optposition + 1];
        else if (++optind >= state->argc) {
            my_dprintf(STDERR_FILENO, "%s: option requires an argument -- %c\n",
                state->argv[0], state->argument_character);
            *state->ptr_optposition = 1;
            return '?';
        } else
            optarg = state->argv[optind++];
        *state->ptr_optposition = 1;
    } else if (state->argv[optind][++*state->ptr_optposition] == '\0') {
        *state->ptr_optposition = 1;
        ++optind;
    }
    return (state->argument_character);
}

static int do_illegal_option(struct getopt_state *state)
{
    my_dprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n", state->argv[0],
        state->argument_character);
    if (state->argv[optind][++*state->ptr_optposition] == '\0') {
        ++optind;
        *state->ptr_optposition = 1;
    }
    return ('?');
}

static int do_option(struct getopt_state *state)
{
    state->argument_character = state->argv[optind][*state->ptr_optposition];
    if (state->argument_character != ':') {
        state->optstring_argument_position = my_strchr(state->optstring,
            state->argument_character);
        if (state->optstring_argument_position != NULL)
            return (do_found_option(state));
    }
    return do_illegal_option(state);
}

static void do_reset(struct getopt_state *state)
{
    if (optind == 0) {
        optind = 1;
        *state->ptr_optposition = 1;
    }
}

int my_getopt(int argc, char **argv, const char *optstring)
{
    static int optposition = 1;
    struct getopt_state state = {.argc = argc, .argv = argv,
        .optstring = optstring, .ptr_optposition = &optposition};

    optarg = NULL;
    do_reset(&state);
    if (*state.ptr_optposition == 1) {
        if (optind >= state.argc || state.argv[optind][0] != '-' ||
            state.argv[optind][1] == '\0')
            return (-1);
        if (my_strcmp(state.argv[optind], "--") == 0) {
            ++optind;
            return (-1);
        }
    }
    return (do_option(&state));
}
