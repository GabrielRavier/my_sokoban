/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map_move_square
*/

#include "../map.h"
#include "my/assert.h"

void sokoban_map_move_square(struct sokoban_map *map, ssize_t x, ssize_t y,
    ssize_t x_move, ssize_t y_move)
{
    char move_to_square = sokoban_map_get_square(map, x + x_move, y + y_move);

    MY_ASSERT(move_to_square == ' ' || move_to_square == 'O');
    map->squares[(y + y_move) * map->columns + (x + x_move)].character =
        map->squares[y * map->columns + x].character;
    map->squares[y * map->columns + x].character =
        map->squares[y * map->columns + x].is_o_underneath ? 'O' : ' ';
}
