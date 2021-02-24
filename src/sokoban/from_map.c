/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_from_map
*/

#include "from_map.h"
#include "from_map_do_print.h"
#include "from_map_do_key.h"
#include "map.h"
#include "my/stdlib.h"
#include <ncurses.h>

static int finish_sokoban(int result, struct sokoban_map *map_backup)
{
    endwin();
    my_free(map_backup->squares);
    return (result);
}

MY_ATTR_PURE static bool all_boxes_on_storage_locations(
    const struct sokoban_map *map)
{
    for (size_t i = 0; i < map->lines * map->columns; ++i)
        if (map->squares[i].is_o_underneath && map->squares[i].character != 'X')
            return (false);
    return (true);
}

static bool is_good_square(char character)
{
    return (character == ' ' || character == 'P' || character == 'O');
}

MY_ATTR_PURE static bool no_boxes_can_move(struct sokoban_map *map)
{
    for (size_t y = 0; y < map->lines; ++y)
        for (size_t x = 0; x < map->columns; ++x)
            if (map->squares[y * map->columns + x].character == 'X') {
                if ((is_good_square(sokoban_map_get_square(map,
                    &((struct sokoban_map_position){x, y - 1}))) &&
                    is_good_square(sokoban_map_get_square(map,
                    &((struct sokoban_map_position){x, y + 1})))) ||
                    (is_good_square(sokoban_map_get_square(map,
                    &((struct sokoban_map_position){x - 1, y}))) &&
                    is_good_square(sokoban_map_get_square(map,
                    &((struct sokoban_map_position){x + 1, y})))))
                    return (false);
            }
    return (true);
}

int sokoban_from_map(struct sokoban_map *map)
{
    struct sokoban_map map_backup = sokoban_map_copy(map);

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    while (true) {
        if (all_boxes_on_storage_locations(map))
            return (finish_sokoban(0, &map_backup));
        if (no_boxes_can_move(map))
            return (finish_sokoban(1, &map_backup));
        sokoban_from_map_do_print(map);
        sokoban_from_map_do_key(map, &map_backup, getch());
    }
}
