/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares utility-related entities
*/

#include "../macros.h"

/// Exchanges the given values
#define MY_SWAP(a, b) \
    do { \
        __auto_type MY_MAKE_UNIQUE_IDENTIFIER(_swap_tmp) = (a); \
        (a) = (b); \
        (b) = MY_MAKE_UNIQUE_IDENTIFIER(_swap_tmp); } while (0)
