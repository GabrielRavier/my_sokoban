/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map
*/

#pragma once

#include "my/features.h"
#include <sys/types.h>
#include <stddef.h>
#include <stdbool.h>

// The map is made out of an array of squares, with the corresponding entity
// underneath determined by its character (non-existent squares are '\0's)
// is_o_underneath lets us know what a movable entity has under it (O or nothing
// ?).
struct sokoban_map_square {
    char character;
    bool is_o_underneath;
};

struct sokoban_map_position {
    ssize_t x;
    ssize_t y;
};

struct sokoban_map {
    size_t columns;
    size_t lines;
    struct sokoban_map_square *squares;
    struct sokoban_map_position player_pos;
};

char sokoban_map_get_square(const struct sokoban_map *map,
    const struct sokoban_map_position *pos) MY_ATTR_PURE;
void sokoban_map_move_square(struct sokoban_map *map,
    const struct sokoban_map_position *src_pos,
    const struct sokoban_map_position *dest_pos_diff);
struct sokoban_map sokoban_map_copy(const struct sokoban_map *map);
