/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares entities from parse_conversion_info.c
*/

#pragma once

#include <stdbool.h>
#include <stdarg.h>

struct my_printf_conversion_info {
    bool flag_minus;
    bool flag_plus;
    bool flag_space;
    bool flag_hash;
    bool flag_0;
    int field_width;
    int precision;
    enum {
        PRINTF_LENGTH_MODIFIER_NONE,
        PRINTF_LENGTH_MODIFIER_CHAR,
        PRINTF_LENGTH_MODIFIER_SHORT,
        PRINTF_LENGTH_MODIFIER_LONG,
        PRINTF_LENGTH_MODIFIER_LONG_LONG,
        PRINTF_LENGTH_MODIFIER_INTMAX,
        PRINTF_LENGTH_MODIFIER_SIZE_T,
        PRINTF_LENGTH_MODIFIER_PTRDIFF_T,
        PRINTF_LENGTH_MODIFIER_LONG_DOUBLE,
        PRINTF_LENGTH_MODIFIER_DECIMAL32,
        PRINTF_LENGTH_MODIFIER_DECIMAL64,
        PRINTF_LENGTH_MODIFIER_DECIMAL128
    } length_modifier;
    char conversion_specifier;
};

void parse_printf_flags(struct my_printf_conversion_info *conversion_info,
    const char **to_parse);
void parse_printf_field_width(struct my_printf_conversion_info *conversion_info,
    const char **to_parse, va_list arguments);
void parse_printf_precision(struct my_printf_conversion_info *conversion_info,
    const char **to_parse, va_list arguments);
void parse_printf_length_modifier(
    struct my_printf_conversion_info *conversion_info, const char **to_parse);
