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
#include <wchar.h>

// These functions returns a string to be prefixed to the output if doing right
// alignment in a way that need a prefix before the alignment (i.e. flag_0)
typedef struct my_string *(*formatter_func_t)(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);

size_t asprintf_utf32_char_to_utf8(char *destination, wchar_t wide_char);
void asprintf_append_number_base(struct my_string *destination,
    uintmax_t number, int base, bool is_uppercase);
struct my_string *asprintf_format_signed_integer(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_unsigned_integer(
    struct my_string *destination, va_list *arguments,
    struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_char(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_cstring(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_decimal_float(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_percent_sign(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_pointer(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
struct my_string *asprintf_format_n(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info);
