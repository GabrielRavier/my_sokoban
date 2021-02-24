/*
** EPITECH PROJECT, 2021
** my_sokoban
** File description:
** Defines sokoban_from_map_do_print
*/

#include "from_map_do_print.h"
#include "map.h"
#include "my/cpp-like/algorithm.h"
#include <ncurses.h>
#include <stdbool.h>

static bool terminal_too_small(struct sokoban_map *map)
{
    int maxx;
    int maxy;

    getmaxyx(stdscr, maxy, maxx);
    return (maxx < map->columns || maxy < map->lines);
}

static void print_please_enlarge_terminal(void)
{
    int maxx;
    int maxy;

    clear();
    getmaxyx(stdscr, maxy, maxx);
    mvaddstr(maxy / 2, MY_MAX(0, maxx / 2 - (20 / 2)), "Enlarge the terminal");
}

static void print_map(struct sokoban_map *map)
{
    clear();
    for (size_t y = 0; y < map->lines; ++y)
        for (size_t x = 0; x < map->columns; ++x) {
            if (map->squares[y * map->columns + x].character == '\n')
                continue;
            if (map->squares[y * map->columns + x].character == '\0')
                mvaddch(y, x, ' ');
            else
                mvaddch(y, x, map->squares[y * map->columns + x].character);
        }
}

void sokoban_from_map_do_print(struct sokoban_map *map)
{
    if (terminal_too_small(map))
        print_please_enlarge_terminal();
    else
        print_map(map);
}
