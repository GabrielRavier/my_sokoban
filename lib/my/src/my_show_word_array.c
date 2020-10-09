/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays the contents of an array of words
*/

#include "my.h"
#include <stddef.h>

int my_show_word_array(char *const *table)
{
    for (size_t i = 0; table[i] != NULL; ++i)
        my_puts(table[i]);

    return 0;
}
