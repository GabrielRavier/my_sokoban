/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares miscellaneous entities
*/

#pragma once

#include "features.h"
#include <stddef.h>
#include <stdbool.h>

/// Recursively calculates number to the power of power
int my_compute_power_rec(int number, int power) MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_CONST;

/// Calculates a square root (if it is a whole number)
int my_compute_square_root(int number) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;

/// Returns whether the number is prime
bool my_is_prime(unsigned number) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;

/// Finds the smallest prime number that is >= to number
int my_find_prime_sup(int number) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;

/// Reverses a string
char *my_revstr(char *string);

/// Puts every letter of a string into uppercase
char *my_strupcase(char *string);

/// Puts every letter of a string into lowercase
char *my_strlowcase(char *string);

/// Capitalizes the first letter of each word
char *my_strcapitalize(char *string);

/// Checks if the passed string only contains alphabetical characters
bool my_str_isalpha(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;

/// Check if the passed string only contains digits
bool my_str_isnum(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;

/// Check if the passed string only contains lowercase characters
bool my_str_islower(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;

/// Check if the passed string only contains uppercase characters
bool my_str_isupper(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;

/// Check if the passed string only contains printable characters
bool my_str_isprintable(const char *string) MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_PURE;

/// Counts the amount of times a byte appears in a range
size_t my_count_byte_occurences(const char *first, const char *last,
    char character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;

/// Displays the contents of an array of words
bool my_show_word_array(char *const *table) MY_ATTR_WARN_UNUSED_RESULT;

/// Splits a string into words
char **my_str_to_word_array(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
