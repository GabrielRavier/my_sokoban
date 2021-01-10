/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares miscellaneous functions from libmy
*/

#pragma once

#include "features.h"
#include <stddef.h>
#include <stdbool.h>

int my_compute_power_rec(int number, int power) MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_CONST;
int my_compute_square_root(int number) MY_ATTR_WARN_UNUSED_RESULT;
bool my_is_prime(unsigned number) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_find_prime_sup(int number) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
char *my_revstr(char *string);
char *my_strupcase(char *string);
char *my_strlowcase(char *string);
char *my_strcapitalize(char *string);
bool my_str_isalpha(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;
bool my_str_isnum(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;
bool my_str_islower(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;
bool my_str_isupper(const char *string) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;
bool my_str_isprintable(const char *string) MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_PURE;
size_t my_count_byte_occurences(const char *first, const char *last,
    char character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;
bool my_show_word_array(char *const *table) MY_ATTR_WARN_UNUSED_RESULT;
char **my_str_to_word_array(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
