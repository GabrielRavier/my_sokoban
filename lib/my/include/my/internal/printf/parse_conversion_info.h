/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares entities from parse_conversion_info.c
*/

#pragma once

#include "../../features.h"
#include <stdbool.h>
#include <stdarg.h>

enum my_printf_length_modifier {
    PRINTF_LENGTH_MODIFIER_NONE,
    PRINTF_LENGTH_MODIFIER_CHAR,
    PRINTF_LENGTH_MODIFIER_SHORT,
    PRINTF_LENGTH_MODIFIER_LONG,
    PRINTF_LENGTH_MODIFIER_LONG_LONG,
    PRINTF_LENGTH_MODIFIER_INTMAX,
    PRINTF_LENGTH_MODIFIER_SIZE_T,
    PRINTF_LENGTH_MODIFIER_PTRDIFF_T,
};

// We reuse PRINTF_LENGTH_MODIFIER_LONG_LONG for long double, for glibc
// compatibility
struct my_printf_conversion_info {
    bool flag_minus;
    bool flag_plus;
    bool flag_space;
    bool flag_hash;
    bool flag_0;
    int field_width;
    int precision;
    enum my_printf_length_modifier length_modifier;
    char conversion_specifier;
};

int my_asprintf_parse_int(const char **to_parse);
void my_parse_printf_flags(struct my_printf_conversion_info *conversion_info,
    const char **to_parse);
bool my_parse_printf_field_width(
    struct my_printf_conversion_info *conversion_info, const char **to_parse,
    va_list *arguments) MY_ATTR_WARN_UNUSED_RESULT;
bool my_parse_printf_precision(
    struct my_printf_conversion_info *conversion_info, const char **to_parse,
    va_list *arguments) MY_ATTR_WARN_UNUSED_RESULT;
void my_parse_printf_length_modifier(
    struct my_printf_conversion_info *conversion_info, const char **to_parse);

#define INTERNAL_MAKE_FLAG_CASE(character, info_field_to_set) \
    case character:                                           \
        conversion_info->info_field_to_set = true
#define INTERNAL_DO_MODIFIER(modifier_string, modifier_value)       \
    do {                                                            \
        if (parse_single_length_modifier(conversion_info, to_parse, \
            modifier_string, modifier_value))                       \
            return;                                                 \
    } while (0)
