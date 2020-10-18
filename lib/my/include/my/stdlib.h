/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares functions from libmy
*/

#pragma once

#include "my/config.h"
#include <stddef.h>

void my_qsort(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *));
void my_qsort_r(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *, void *),
    void *argument);
void *my_realloc_size(void *ptr, size_t new_length,
    size_t original_length) MY_ATTR_WARN_UNUSED_RESULT;
