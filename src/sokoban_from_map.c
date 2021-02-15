/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_from_map
*/

#include "sokoban_from_map.h"
#include "sokoban_map.h"
#include <ncurses.h>

static int finish_sokoban(int result)
{
    endwin();
    return (result);
}

static bool all_boxes_on_storage_locations(const struct sokoban_map *map)
{
    for (size_t i = 0; i < map->lines * map->columns; ++i)
        if (map->squares[i].character == 'O')
            return (false);
    return (true);
}

static bool is_good_square(char character)
{
    return (character == ' ' || character == 'P' || character == 'O');
}

static bool no_boxes_can_move(struct sokoban_map *map)
{
    for (size_t y = 0; y < map->lines; ++y)
        for (size_t x = 0; x < map->columns; ++x)
            if (map->squares[y * map->columns + x].character == 'X') {
                if ((is_good_square(sokoban_map_get_square(map, x, y - 1)) &&
                    is_good_square(sokoban_map_get_square(map, x, y + 1))) ||
                    (is_good_square(sokoban_map_get_square(map, x - 1, y)) &&
                    is_good_square(sokoban_map_get_square(map, x + 1, y))))
                    return (false);
            }
    return (true);
}

int sokoban_from_map(struct sokoban_map *map)
{
    initscr();
    cbreak();
    while (true) {
        if (all_boxes_on_storage_locations(map))
            return (finish_sokoban(0));
        if (no_boxes_can_move(map))
            return (finish_sokoban(1));
    }
}
