/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares strtol_base_str_part2-related entities
*/

#pragma once

#include "../features.h"
#include <stdbool.h>

bool my_find_digit_from_base(const char *digit_character_ptr, const char *base,
    unsigned char *digit_ptr) MY_ATTR_WARN_UNUSED_RESULT;
