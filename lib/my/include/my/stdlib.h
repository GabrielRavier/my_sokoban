/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares stdlib-related functions from libmy
*/

#pragma once

#include "my/config.h"
#include <stdlib.h>
#include <stddef.h>

// Sort an array of num_elements elements of size element_size, pointed to by
// base. The contents are sorted in ascending order, according to the comparison
// function pointed to by comparison_function
void my_qsort(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *))
    MY_ATTR_NONNULL((1, 4));

// Same as my_qsort, except comparison_function takes a third argument, which
// will always be the fourth argument passed to my_qsort_r
void my_qsort_r(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *, void *),
    void *argument) MY_ATTR_NONNULL((1, 4));

// Changes the size of the memory block pointed to by ptr of original_length
// bytes to new_length bytes.
void *my_realloc_size(void *ptr, size_t new_length, size_t original_length)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_NOTHROW MY_ATTR_ALLOC_SIZE((2))
    MY_ATTR_MALLOC;

// This allows an arbitrary amount of signs before the number, and handles them
// appropriately, so this doesn't behave exactly identically to strtol. It also
// does not set errno
long my_strtol_base_str(const char *num_ptr, char **end_num_ptr,
    const char *base) MY_ATTR_NONNULL((1, 3)) MY_ATTR_NOTHROW;

// This is the actual strtol. Converts a string to a long integer.
long my_strtol(const char *num_ptr, char **end_num_ptr, int base)
    MY_ATTR_NONNULL((1)) MY_ATTR_NOTHROW;

// Computes the absolute value of an integer
int my_abs(int x) MY_ATTR_NOTHROW MY_ATTR_CONST MY_ATTR_WARN_UNUSED_RESULT;

// Causes abnormal process termination
void my_abort(void) MY_ATTR_NOTHROW MY_ATTR_NORETURN;

static inline void my_free_ptr(void *ptr)
{
    free(*(void **)ptr);
}

#define MY_CLEANUP_FREE __attribute__((cleanup(my_free_ptr)))
