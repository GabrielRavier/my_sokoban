/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Appends a formatted string to a my_string
*/

#include "my/my_string.h"
#include "my/internal/my_string.h"
#include "my/stdio.h"
#include "my/string.h"
#include <stdlib.h>

struct my_string *my_string_append_vprintf(struct my_string *self,
    const char *format, va_list arguments)
{
    int asprintf_length;
    char *asprintf_result;
    
    if (self == NULL || format == NULL)
        return NULL;
    asprintf_length = my_vasprintf(&asprintf_result, format, arguments);
    if (asprintf_length >= 0) {
        my_string_append(self, asprintf_result, asprintf_length);
        free(asprintf_result);
    }
    return self;
}
