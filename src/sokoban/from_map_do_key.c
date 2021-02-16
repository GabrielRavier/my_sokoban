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
    char player_move_square, char two_ahead_square, int x_move, int y_move)
{
    if (player_move_square == ' ' || player_move_square == 'O')
        return (true);
    if (player_move_square == 'X' && (two_ahead_square == ' ' ||
        two_ahead_square == 'O')) {
        sokoban_map_move_square(map, map->player_pos.x + x_move,
            map->player_pos.y + y_move, x_move, y_move);
        return (true);
    }
    return (false);
}

static void try_move(struct sokoban_map *map, int key)
{
    int x_move = (key == KEY_RIGHT) - (key == KEY_LEFT);
    int y_move = (key == KEY_DOWN) - (key == KEY_UP);
    char player_move_square = sokoban_map_get_square(map, map->player_pos.x +
        x_move, map->player_pos.y + y_move);
    char two_ahead_square = sokoban_map_get_square(map, map->player_pos.x +
        x_move * 2, map->player_pos.y + y_move * 2);
    bool should_move_player = do_box_and_check_player_move(map,
        player_move_square, two_ahead_square, x_move, y_move);

    if (should_move_player) {
        sokoban_map_move_square(map, map->player_pos.x, map->player_pos.y,
            x_move, y_move);
        map->player_pos.x += x_move;
        map->player_pos.y += y_move;
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
