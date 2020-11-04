/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares entities from parse_conversion_info.c
*/

#pragma once

struct my_printf_conversion_info {
    char conversion_specifier;
};

void parse_printf_flags(struct my_printf_conversion_info *conversion_info,
    const char **to_parse);
void parse_printf_field_width(struct my_printf_conversion_info *conversion_info,
    const char **to_parse);
void parse_printf_precision(struct my_printf_conversion_info *conversion_info,
    const char **to_parse);
void parse_printf_length(struct my_printf_conversion_info *conversion_info,
    const char **to_parse);
