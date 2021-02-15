/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines assert_fail
*/

#include "my/assert.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <unistd.h>

_Noreturn static void error_in_assert(void)
{
    const int ok_yeah_just_ignore_this_return_value = my_dputs(
        "\n\nCouldn't fully print assert error message\n", STDERR_FILENO);
    (void)ok_yeah_just_ignore_this_return_value;
    my_abort();
}

void my_assert_fail(const char *expression, const char *file_name,
    int line_number, const char *function_name)
{
    if (my_printf("%s:%d: %s: Assertion '%s' failed.\n", file_name,
        line_number, function_name, expression) < 0)
        error_in_assert();
    my_abort();
}
