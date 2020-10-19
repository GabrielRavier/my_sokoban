/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares assert-related entities from libmy
*/

#pragma once

#include "my/config.h"

void my_assert_fail(const char *expression, const char *file_name,
    int line_number, const char *function_name) MY_ATTR_NORETURN;

#define MY_ASSERT(expression)                           \
    ((bool)(expression) ? (void)0 :                     \
        my_assert_fail(#expression, __FILE__, __LINE__, \
        MY_PRETTY_FUNCTION))
