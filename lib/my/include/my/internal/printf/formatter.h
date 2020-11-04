/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares formatting functions
*/

#pragma once

#include "my/my_string.h"
#include "parse_conversion_info.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

typedef void (*formatter_func_t)(struct my_string *destination,
    va_list arguments, const struct my_printf_conversion_info *format_info);

void asprintf_append_number_base(struct my_string *destination,
    uintptr_t number, int base, bool is_uppercase);
void asprintf_format_signed_integer(struct my_string *destination, va_list arguments,
    const struct my_printf_conversion_info *format_info);
void asprintf_format_unsigned_integer(struct my_string *destination, va_list arguments,
    const struct my_printf_conversion_info *format_info);
void asprintf_format_char(struct my_string *destination, va_list arguments,
    const struct my_printf_conversion_info *format_info);
void asprintf_format_cstring(struct my_string *destination, va_list arguments,
    const struct my_printf_conversion_info *format_info);
