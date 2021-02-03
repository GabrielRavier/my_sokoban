/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares some useful macros
*/

#pragma once

#define MY_PREPROCESSOR_CONCAT_YES_REALLY_EXPAND_THESE_ARGUMENTS(a, b) a##b
#define MY_PREPROCESSOR_CONCAT(a, b) \
    MY_PREPROCESSOR_CONCAT_YES_REALLY_EXPAND_THESE_ARGUMENTS(a, b)

/// Gives us a relatively unique identifier. Provide a prefix if you use this
/// several times on the same line
#define MY_MAKE_UNIQUE_IDENTIFIER(prefix) MY_PREPROCESSOR_CONCAT( \
    MY_PREPROCESSOR_CONCAT(__UNIQUE_IDENTIFIER, prefix), __LINE__)

/// Produces a build error if expression is non-zero, but still allows usage in
/// constant expressions
#define MY_BUILD_BUG_ON_NON_ZERO(expression) \
    ((int)(__extension__ sizeof(struct { int : (-!!(expression)); })))

/// Determines whether two expressions have the same type, though it does not
/// determine whether they have different qualifiers
#define MY_IS_SAME_TYPE(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

/// Fails to compile if the passed expression is not an array
#define MY_BUILD_BUG_ON_NON_ARRAY(array) \
    MY_BUILD_BUG_ON_NON_ZERO(MY_IS_SAME_TYPE((array), &(array)[0]))

/// Returns 1 if a > b, 0 if a == b and -1 if a < b
#define MY_THREE_WAY_CMP(a, b) \
    (__extension__ ({ \
        __auto_type MY_MAKE_UNIQUE_IDENTIFIER(_a) = (a); \
        __auto_type MY_MAKE_UNIQUE_IDENTIFIER(_b) = (b); \
        (MY_MAKE_UNIQUE_IDENTIFIER(_a) > MY_MAKE_UNIQUE_IDENTIFIER(_b)) - \
            (MY_MAKE_UNIQUE_IDENTIFIER(_a) < MY_MAKE_UNIQUE_IDENTIFIER(_b)); \
    }))
