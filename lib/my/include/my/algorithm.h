/*
** EPITECH PROJECT, 2020
** navy
** File description:
** Declares algorithm macros
*/

#pragma once

#define MY_REPLACE(first_param, last, old_value, new_value) do { \
    __auto_type first = first_param; \
    for (; first != last; ++first) \
        if (*first == old_value) \
            *first = new_value; \
    } while(0);
