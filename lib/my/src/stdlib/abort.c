/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines abort
*/

#include "my/stdlib.h"

void __gcov_flush(void);

#ifndef LIBMY_COVERAGE
    #define __gcov_flush()
#endif

void my_abort(void)
{
    __builtin_trap();
}
