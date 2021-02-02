/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Helper for strtol to get past norm
*/

#pragma once

#include <stdint.h>

#define TYPE intmax_t
#define TYPE_UNSIGNED uintmax_t
#define TYPE_MIN INTMAX_MIN
#define TYPE_MAX INTMAX_MAX
#define INTERNAL_FUNC_NAME my_strtoimax_internal

#include "../stdlib/strto_generic.h"
