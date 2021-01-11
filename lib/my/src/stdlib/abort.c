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

// This uses __builtin_trap to avoid problems with restrictions (say, being
// forbidden from using abort(3))
void my_abort(void)
{
    __gcov_flush();
    __builtin_trap();
}
