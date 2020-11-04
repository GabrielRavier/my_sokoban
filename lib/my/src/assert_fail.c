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
    int ok_yeah_just_ignore_this_return_value = my_dputs(
        "\n\nCouldn't fully print assert error message", STDERR_FILENO);
    (void)ok_yeah_just_ignore_this_return_value;
    __builtin_trap();
}

// This uses __builtin_trap to avoid problems with restrictions (say, being
// forbidden from using abort(3))
void my_assert_fail(const char *expression, const char *file_name,
    int line_number, const char *function_name)
{
    const char *line_number_as_str = my_nbr_to_string(line_number);
    if (my_dputs(file_name, STDERR_FILENO) == EOF ||
        my_dputc(':', STDERR_FILENO) == EOF ||
        my_dputs(line_number_as_str, STDERR_FILENO) == EOF ||
        my_dputs(": ", STDERR_FILENO) == EOF ||
        my_dputs(function_name, STDERR_FILENO) == EOF ||
        my_dputs(": Assertion '", STDERR_FILENO) == EOF ||
        my_dputs(expression, STDERR_FILENO) == EOF ||
        my_dputs("' failed.\n", STDERR_FILENO) == EOF)
        error_in_assert();
    __builtin_trap();
}
