/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares internal macros for non-portable stuff like attributes
*/

#pragma once

#ifdef __GNUC__
    #define MY_ATTRIBUTE(attr) __attribute__(attr)
    #define MY_PRETTY_FUNCTION __extension__ __PRETTY_FUNCTION__
    #define MY_GCC_AT_LEAST_VER(major, minor) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((major) << 16) + (minor))
#else
    #define MY_ATTRIBUTE(attr)
    #define MY_PRETTY_FUNCTION __func__
    #define MY_GNUC_PREREQ(major, minor) 0
#endif

#define MY_ATTR_WARN_UNUSED_RESULT MY_ATTRIBUTE((warn_unused_result))
#define MY_ATTR_CONST MY_ATTRIBUTE((const))
#define MY_ATTR_NOTHROW MY_ATTRIBUTE((nothrow))
#define MY_ATTR_NONNULL(parameters) MY_ATTRIBUTE((nonnull parameters))
#define MY_ATTR_ALLOC_SIZE(parameters) MY_ATTRIBUTE((alloc_size parameters))
#define MY_ATTR_PURE MY_ATTRIBUTE((pure))
#define MY_ATTR_MALLOC MY_ATTRIBUTE((malloc))
#define MY_ATTR_FALLTHROUGH MY_ATTRIBUTE((fallthrough))
#define MY_ATTR_NORETURN MY_ATTRIBUTE((noreturn))
#define MY_ATTR_FORMAT(archetype, string_index, first_to_check) \
    MY_ATTRIBUTE((format(archetype, string_index, first_to_check)))
#define MY_ATTR_UNUSED MY_ATTRIBUTE((unused))
#if MY_GCC_AT_LEAST_VER(10, 0)
    #define MY_ATTR_ACCESS(parameters) MY_ATTRIBUTE((access parameters))
#else
    #define MY_ATTR_ACCESS(parameters)
#endif
