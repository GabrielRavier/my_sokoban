/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares entities from handle_invalid.c
*/

#pragma once

#include "parse_conversion_info.h"
#include "../../my_string.h"
#include <stdbool.h>

// Returns whether we should just stop
// Exists because of glibc bullshit
bool my_asprintf_handle_invalid(struct my_string *destination,
    struct my_printf_conversion_info *conversion_info,
    bool *has_encountered_invalid);
