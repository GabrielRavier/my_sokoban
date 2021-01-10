/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares ctype-related functions from libmy
*/

#pragma once

#include "features.h"
#include <ctype.h>

// Checks for any printable character (including space)
int my_isprint(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Checks for an uppercase character
int my_isupper(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Checks for an alphanumeric character
int my_isalnum(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Checks for a digit
int my_isdigit(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Checks for an alphabetic character
int my_isalpha(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Checks for whitespace characters
int my_isspace(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Checks for a lowercase character
int my_islower(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Converts an uppercase letter to lowercase
int my_tolower(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
// Converts a lowercase letter to uppercase
int my_toupper(int character)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST MY_ATTR_NOTHROW;
