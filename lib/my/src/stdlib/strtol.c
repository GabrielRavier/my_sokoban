/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_strtol
*/

#include "my/stdlib.h"
#include "my/ctype.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

#ifndef __clang__
    #pragma GCC diagnostic ignored "-Warith-conversion"
#endif
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wcast-qual"

enum strtol_num_type {
    STRTOL_NUM_TYPE_NONE,
    STRTOL_NUM_TYPE_NORMAL,
    STRTOL_NUM_TYPE_INVALID,
};

struct strtol_parse_state {
    enum strtol_num_type num_type;
    const char *num_ptr;
    char current_character;
    int base;
    bool is_negative;
};

static void do_preparsing(struct strtol_parse_state *state)
{
    do {
        state->current_character = *state->num_ptr++;
    } while (my_isspace(state->current_character));
    if (state->current_character == '-')
        state->is_negative = true;
    if (state->current_character == '-' || state->current_character == '+')
        state->current_character = *state->num_ptr++;
    if ((state->base == 0 || state->base == 16) &&
        state->current_character == '0' &&
        (my_tolower(*state->num_ptr) == 'x')) {
        ++state->num_ptr;
        state->current_character = *state->num_ptr++;
        state->base = 16;
    }
    if (state->base == 0)
        state->base = (state->current_character == '0') ? 8 : 10;
}

static bool do_base_char(struct strtol_parse_state *state)
{
    if (my_isdigit(state->current_character))
        state->current_character -= '0';
    else if (my_isalpha(state->current_character))
        state->current_character -=
            my_isupper(state->current_character) ? 'A' - 10 : 'a' - 10;
    else
        return (false);
    return (state->current_character < state->base);
}

static bool would_overflow(unsigned long current_result,
    struct strtol_parse_state *state, unsigned long min_val_without_last_digit,
    int min_val_last_digit)
{
    return (current_result > min_val_without_last_digit ||
        (current_result == min_val_without_last_digit &&
            state->current_character > min_val_last_digit));
}

static unsigned long do_parsing_loop(struct strtol_parse_state *state)
{
    unsigned long result = 0;
    unsigned long min_val = state->is_negative ? -(unsigned long)LONG_MIN :
        LONG_MAX;
    const int min_val_last_digit = (int)(min_val % (unsigned long)state->base);

    min_val /= (unsigned long)state->base;
    while (1) {
        if (!do_base_char(state))
            break;
        if (state->num_type == STRTOL_NUM_TYPE_INVALID ||
            would_overflow(result, state, min_val, min_val_last_digit))
            state->num_type = STRTOL_NUM_TYPE_INVALID;
        else {
            state->num_type = STRTOL_NUM_TYPE_NORMAL;
            result *= (unsigned long)state->base;
            result += (unsigned long)state->current_character;
        }
        state->current_character = *state->num_ptr++;
    }
    return (result);
}

long my_strtol(const char *num_ptr, char **end_num_ptr, int base)
{
    struct strtol_parse_state state = {STRTOL_NUM_TYPE_NONE, num_ptr, 0, base,
        false};
    unsigned long result;

    if (state.base < 0 || state.base == 1 || state.base > 36) {
        errno = EINVAL;
        return (0);
    }
    do_preparsing(&state);
    result = do_parsing_loop(&state);
    if (state.num_type == STRTOL_NUM_TYPE_INVALID) {
        result = state.is_negative ? (unsigned long)LONG_MIN : LONG_MAX;
        errno = ERANGE;
    } else if (state.is_negative)
        result = -result;
    if (end_num_ptr)
        *end_num_ptr = (state.num_type != STRTOL_NUM_TYPE_NONE) ?
            (char *)(state.num_ptr - 1) : (char *)num_ptr;
    return (long)(result);
}
