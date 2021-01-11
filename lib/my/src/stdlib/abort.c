/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines abort
*/

#include "my/stdlib.h"
#include "my/internal/coverage_flush.h"

// This uses __builtin_trap to avoid problems with restrictions (say, being
// forbidden from using abort(3))
void my_abort(void)
{
    MY_COVERAGE_FLUSH();
    __builtin_trap();
}
