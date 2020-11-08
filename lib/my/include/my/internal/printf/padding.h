/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares entities from padding.c
*/

#pragma once

#include "my/internal/printf/formatter.h"
#include "my/my_string.h"
#include <stddef.h>

struct asprintf_do_padding_params {
    struct my_string *destination;
    size_t destination_length_before_conversion;
    struct my_string *prefixed_string;
    struct my_printf_conversion_info *conversion_info;
    formatter_func_t formatting_func;
};

void asprintf_do_padding(const struct asprintf_do_padding_params *params);
