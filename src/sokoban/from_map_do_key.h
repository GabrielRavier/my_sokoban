/*
** EPITECH PROJECT, 2021
** do_sokoban
** File description:
** Declares sokoban_from_map_do_key
*/

#pragma once

struct sokoban_map;

void sokoban_from_map_do_key(struct sokoban_map *map,
    const struct sokoban_map *map_backup, int key);
