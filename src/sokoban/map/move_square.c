/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map_move_square
*/

#include "../map.h"
#include "my/assert.h"

void sokoban_map_move_square(struct sokoban_map *map,
    const struct sokoban_map_position *src_pos,
    const struct sokoban_map_position *dest_pos_diff)
{
    char move_to_square = sokoban_map_get_square(map,
        &((struct sokoban_map_position){src_pos->x + dest_pos_diff->x,
        src_pos->y + dest_pos_diff->y}));

    MY_ASSERT(move_to_square == ' ' || move_to_square == 'O');
    map->squares[(src_pos->y + dest_pos_diff->y) * map->columns + (src_pos->x +
        dest_pos_diff->x)].character = map->squares[src_pos->y * map->columns +
        src_pos->x].character;
    map->squares[src_pos->y * map->columns + src_pos->x].character =
        map->squares[src_pos->y * map->columns + src_pos->x].is_o_underneath ?
        'O' : ' ';
}
