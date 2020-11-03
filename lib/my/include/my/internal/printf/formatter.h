/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares formatting functions
*/

#pragma once

#include "my/my_string.h"
#include <stdarg.h>

typedef void (*formatter_func_t)(struct my_string *destination,
    va_list arguments, char format_char);

void asprintf_append_number_base(struct my_string *destination, long number,
    int base);
void asprintf_format_integer(struct my_string *destination, va_list arguments,
    char format_char);
void asprintf_format_char(struct my_string *destination, va_list arguments,
    char format_char);
void asprintf_format_cstring(struct my_string *destination, va_list arguments,
    char format_char);
