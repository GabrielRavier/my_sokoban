/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map_get_square
*/

#include "../map.h"

char sokoban_map_get_square(const struct sokoban_map *map,
    const struct sokoban_map_position *pos)
{
    return ((pos->x < 0 || pos->y < 0 || pos->x >= map->columns || pos->y >=
        map->lines) ? 0 : map->squares[pos->y * map->columns +
        pos->x].character);
}
