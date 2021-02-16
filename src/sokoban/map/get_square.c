/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_map_get_square
*/

#include "../map.h"

char sokoban_map_get_square(const struct sokoban_map *map, ssize_t x, ssize_t y)
{
    return ((x < 0 || y < 0 || x >= map->columns || y >= map->lines) ? 0 :
        map->squares[y * map->columns + x].character);
}
