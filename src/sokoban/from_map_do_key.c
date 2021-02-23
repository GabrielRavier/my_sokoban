/*
** EPITECH PROJECT, 2021
** do_sokoban
** File description:
** Defines sokoban_from_map_do_key
*/

#include "from_map_do_key.h"
#include "map.h"
#include "my/stdlib.h"
#include <ncurses.h>
#include <stdbool.h>

static bool do_box_and_check_player_move(struct sokoban_map *map,
    char player_move_square, char two_ahead_square,
    const struct sokoban_map_position *dest_pos_diff)
{
    if (player_move_square == ' ' || player_move_square == 'O')
        return (true);
    if (player_move_square == 'X' && (two_ahead_square == ' ' ||
        two_ahead_square == 'O')) {
        sokoban_map_move_square(map, &((struct sokoban_map_position){
            map->player_pos.x + dest_pos_diff->x, map->player_pos.y +
            dest_pos_diff->y}), dest_pos_diff);
        return (true);
    }
    return (false);
}

static void try_move(struct sokoban_map *map, int key)
{
    struct sokoban_map_position dest_pos_diff = {.x = (key == KEY_RIGHT) -
        (key == KEY_LEFT), .y = (key == KEY_DOWN) - (key == KEY_UP)};
    char player_move_square = sokoban_map_get_square(map,
        &((struct sokoban_map_position){map->player_pos.x + dest_pos_diff.x,
        map->player_pos.y + dest_pos_diff.y}));
    char two_ahead_square = sokoban_map_get_square(map,
        &((struct sokoban_map_position){map->player_pos.x + dest_pos_diff.x * 2,
        map->player_pos.y + dest_pos_diff.y * 2}));
    bool should_move_player = do_box_and_check_player_move(map,
        player_move_square, two_ahead_square, &dest_pos_diff);

    if (should_move_player) {
        sokoban_map_move_square(map, &((struct sokoban_map_position){
            map->player_pos.x, map->player_pos.y}), &dest_pos_diff);
        map->player_pos.x += dest_pos_diff.x;
        map->player_pos.y += dest_pos_diff.y;
    }
}

void sokoban_from_map_do_key(struct sokoban_map *map,
    const struct sokoban_map *map_backup, int key)
{
    if (key == ' ') {
        my_free(map->squares);
        *map = sokoban_map_copy(map_backup);
    }
    if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT ||
        key == KEY_RIGHT)
        try_move(map, key);
}
