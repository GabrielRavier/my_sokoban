/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines cleanup
*/

#include "my/internal/stdio.h"

__attribute__((destructor)) void my_internal_file_cleanup(void)
{
    my_internal_file_all_for_each(my_internal_file_flush_skip_non_write);
}
