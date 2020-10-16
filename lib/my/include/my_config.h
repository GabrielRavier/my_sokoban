/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares internal macros for non-portable stuff like attributes
*/

#pragma once

#ifdef __GNUC__
    #define MY_ATTRIBUTE(attr) __attribute__(attr)
#else
    #define MY_ATTRIBUTE(attr)
#endif

#define MY_ATTR_WARN_UNUSED_RESULT MY_ATTRIBUTE((warn_unused_result))

