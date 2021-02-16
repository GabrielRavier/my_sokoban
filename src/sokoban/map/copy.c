/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map_copy
*/

#include "../map.h"
#include "my/assert.h"
#include "my/stdlib.h"
#include "my/string.h"

struct sokoban_map sokoban_map_copy(const struct sokoban_map *map)
{
    struct sokoban_map result;

    result.lines = map->lines;
    result.columns = map->columns;
    result.player_pos = map->player_pos;
    result.squares = (struct sokoban_map_square *)my_malloc(
        sizeof(*result.squares) * result.lines * result.columns);
    MY_ASSERT(result.squares != NULL);
    my_memcpy(result.squares, map->squares, sizeof(*result.squares) *
        result.lines * result.columns);
    return (result);
}
