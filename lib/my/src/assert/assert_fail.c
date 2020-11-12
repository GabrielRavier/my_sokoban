/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Prints an error message for a failed assertion and exits
*/

#include "my/assert.h"
#include "my/misc.h"
#include "my/stdio.h"
#include <stdio.h>
#include <unistd.h>

MY_ATTR_NORETURN static void error_in_assert(void)
{
    const int ok_yeah_just_ignore_this_return_value = my_dputs(
        "\n\nCouldn't fully print assert error message", STDERR_FILENO);
    (void)ok_yeah_just_ignore_this_return_value;
    __builtin_trap();
}

// This uses __builtin_trap to avoid problems with restrictions (say, being
// forbidden from using abort(3))
void my_assert_fail(const char *expression, const char *file_name,
    int line_number, const char *function_name)
{
    if (my_printf("%s:%d: %s: Assertion '%s' failed.\n",
        file_name, line_number, function_name, expression) < 0)
        error_in_assert();
    __builtin_trap();
}
