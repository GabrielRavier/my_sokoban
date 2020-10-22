/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares my_string-related functions
*/

#pragma once

#include <stddef.h>

// This contains a null-terminated string (for easy usage with C APIs), but can
// still contain embedded NULs if you want
struct my_string {
    size_t length;
    size_t allocated_size;
    char *string;
};

// Creates a new, empty, my_string
struct my_string *my_string_new(void);

// Creates a new my_string from the first size bytes of string
struct my_string *my_string_new_from_string(const char *string, size_t length);

// Appends length bytes from string to self
struct my_string *my_string_append(
    struct my_string *self, const char *string, size_t length);

// Inserts length bytes from string to self at pos. A precondition is that
// string is not a substring of self (i.e. directly located within self->string)
struct my_string *my_string_insert(
    struct my_string *self, const char *string, size_t length, size_t position);

// Destructs the passed string and the associated data. If you instead want to free
// the my_string but gain ownership of self->string, just do free(self)
void my_string_free(struct my_string *self);

