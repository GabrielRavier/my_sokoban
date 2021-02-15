/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_from_map_string
*/

#include "sokoban_from_map_string.h"
#include "sokoban_from_map.h"
#include "sokoban_map.h"
#include "my/cpp-like/algorithm.h"
#include "my/my_string.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <unistd.h>
#include <stdbool.h>

static size_t count_in_my_string(struct my_string *str, char c)
{
    return (MY_COUNT(str->string, str->string + str->length, c));
}

static bool validate_map_string(struct my_string *map_string)
{
    char *first_p_occurence = my_strchr(map_string->string, 'P');

    return (!(my_strlen(map_string->string) != map_string->length || my_strspn(
        map_string->string, " \n#XOP") != map_string->length ||
        first_p_occurence == NULL || my_strchr(first_p_occurence + 1, 'P') !=
        NULL || count_in_my_string(map_string, 'O') != count_in_my_string(
        map_string, 'X')));
}

static void string_to_map(struct sokoban_map *map, struct my_string *map_string)
{
    size_t string_it;

    map->square_count = map_string->length - count_in_my_string(map_string,
        '\n');
    map->squares = my_malloc(sizeof(*map->squares) * map->square_count);
    string_it = 0;
    for (size_t i = 0; i < map->square_count; ++i) {
        while (map_string->string[string_it] == '\n')
            ++string_it;
        map->squares[i].character = map_string->string[string_it++];
        map->squares[i].is_x_underneath = map->squares[i].character == 'X';
    }
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
