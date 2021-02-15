/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

// The map is made out of an array of squares, with the corresponding entity
// underneath determined by its character.
// is_x_underneath lets us know what a movable entity has under it
struct sokoban_square {
    char character;
    bool is_x_underneath;
};

struct sokoban_map {
    size_t square_count;
    struct sokoban_square *squares;
};
