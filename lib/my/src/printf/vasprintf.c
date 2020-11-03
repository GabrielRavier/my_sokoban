/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_vasprintf
*/

#include "my/stdio.h"
#include "my/my_string.h"
#include <stdlib.h>

int my_vasprintf(char **result_string_ptr, const char *format,
    va_list arguments)
{
    struct my_string *result = my_string_new();
    size_t resulting_length;

    *result_string_ptr = result->string;
    resulting_length = result->length;
    free(result);
    return (int)resulting_length;
}
