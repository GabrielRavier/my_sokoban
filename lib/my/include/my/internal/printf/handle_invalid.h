/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares entities from handle_invalid.c
*/

#pragma once

#include "my/internal/printf/parse_conversion_info.h"
#include "my/my_string.h"
#include <stdbool.h>

// Returns whether we should just stop
// Exists because of glibc bullshit
bool asprintf_handle_invalid(struct my_string *destination,
    struct my_printf_conversion_info *conversion_info,
    bool *has_encountered_invalid);
