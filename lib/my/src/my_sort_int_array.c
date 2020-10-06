/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Sorts an integer array in ascending order
*/

#include "my.h"
#include <stdbool.h>

// This returns a pointer to the smallest int object between first and last
static int *find_smallest(int *first, int *last)
{
    int *smallest;
    if (first == last)
        return last;

    smallest = first;
    ++first;
    while (first != last) {
        if (*first < *smallest)
            smallest = first;
        ++first;
    }

    return smallest;
}

// This does a simple selection sort
void my_sort_int_array(int *first, int size)
{
    int *last = first + size;
    for (int *i = first; i != last; ++i) {
        int *selection = find_smallest(i, last);
        my_swap(selection, i);
    }
}
