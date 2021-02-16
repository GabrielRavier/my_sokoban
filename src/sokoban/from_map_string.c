/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_from_map_string
*/

#include "from_map_string.h"
#include "from_map.h"
#include "map.h"
#include "my/cpp-like/algorithm.h"
#include "my/my_string.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <unistd.h>
#include <stdbool.h>

// The cast is there because __auto_type badly screws with constness
static size_t count_in_my_string(const struct my_string *str, char c)
{
    return (MY_COUNT((char *)str->string, str->string + str->length, c));
}

static bool validate_map_string(struct my_string *map_string)
{
    if (map_string->length == 0)
        return (false);
    if (map_string->string[map_string->length - 1] != '\n')
        my_string_append_char(map_string, '\n');
    return (!(my_strlen(map_string->string) != map_string->length || my_strspn(
        map_string->string, " \n#XOP") != map_string->length ||
        count_in_my_string(map_string, 'P') != 1 ||  count_in_my_string(
        map_string, 'O') != count_in_my_string(map_string, 'X') ||
        count_in_my_string(map_string, 'O') == 0) ||
        map_string->string[map_string->length - 1] != '\n');
}

static void do_fill_map(struct sokoban_map *map,
    const struct my_string *map_string)
{
    size_t string_it = 0;

    for (size_t y = 0; y < map->lines; ++y)
        for (size_t x = 0;; ++x) {
            if (map_string->string[string_it] == '\n') {
                my_memset(map->squares + y * map->columns + x, 0,
                    (map->columns - x) * sizeof(*map->squares));
                ++string_it;
                break;
            }
            map->squares[y * map->columns + x].character =
                map_string->string[string_it];
            map->squares[y * map->columns + x].is_o_underneath =
                map_string->string[string_it++] == 'O';
        }
}

static void string_to_map(struct sokoban_map *map,
    const struct my_string *map_string)
{
    const char *current_strchr = map_string->string;
    const char *strchr_result;

    map->columns = 0;
    while (true) {
        strchr_result = my_strchr(current_strchr, '\n');
        if (strchr_result == NULL)
            break;
        map->columns = MY_MAX(map->columns, strchr_result - current_strchr);
        current_strchr = strchr_result + 1;
    }
    map->lines = count_in_my_string(map_string, '\n');
    map->squares = my_malloc(sizeof(*map->squares) * map->lines * map->columns);
    do_fill_map(map, map_string);
    for (size_t y = 0; y < map->lines; ++y)
        for (size_t x = 0; x < map->columns; ++x)
            if (map->squares[y * map->columns + x].character == 'P')
                map->player_pos = (struct sokoban_map_position){x, y};
}

int sokoban_from_map_string(struct my_string *map_string)
{
    struct sokoban_map map;
    int result;

    if (!validate_map_string(map_string)) {
        my_dputs("Invalid map\n", STDERR_FILENO);
        return (84);
    }
    string_to_map(&map, map_string);
    result = sokoban_from_map(&map);
    my_free(map.squares);
    return (result);
}
