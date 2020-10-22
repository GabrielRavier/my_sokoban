/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Displays the contents of an array of words
*/

#include "my/misc.h"
#include "my/stdio.h"
#include <stddef.h>
#include <stdio.h>

bool my_show_word_array(char *const *table)
{
    for (size_t i = 0; table[i] != NULL; ++i)
        if (my_puts(table[i]) == EOF)
            return (false);
    return (true);
}
