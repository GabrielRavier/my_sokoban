/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Sorts num_elements of size element_size in ascending order as decided by
** comparison_function
*/

#include "my.h"

static void swap_elements(char *elem1, char *elem2, size_t element_size)
{
    char tmp;

    do {
        tmp = *elem1;
        *elem1++ = *elem2;
        *elem2++ = tmp;
    } while (--element_size != 0);
}

static char *find_smallest_element(char *first, char *last, size_t element_size,
    int (*comparison_function)(const void *, const void *))
{
    char *smallest;
    if (first == last)
        return last;

    smallest = first;
    first += element_size;

    for (; first != last; first += element_size) {
        if (comparison_function(first, smallest) < 0)
            smallest = first;
    }

    return smallest;
}

void my_qsort(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *))
{
    char *first = (char *)base;
    char *last = first + (num_elements * element_size);

    for (char *it = first; it != last; it += element_size) {
        char *smallest =
            find_smallest_element(it, last, element_size, comparison_function);
        swap_elements(smallest, it, element_size);
    }
}
