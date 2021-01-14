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
#else
    #define MY_ATTRIBUTE(attr)
    #define MY_PRETTY_FUNCTION __func__
#endif

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
    #define MY_GCC_AT_LEAST_VER(major, minor) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((major) << 16) + (minor))
#else
    #define MY_GCC_AT_LEAST_VER(major, minor) 0
#endif

#if defined(__clang_major__) && defined(__clang_minor__)
    #define MY_CLANG_AT_LEAST_VER(major, minor) \
        ((__clang_major__ << 16) + __clang_minor__ >= ((major) << 16) + (minor))
#else
    #define MY_CLANG_AT_LEAST_VER(major, minor) 0
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

#if !MY_GCC_AT_LEAST_VER(2, 92)
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
        #define MY_RESTRICT restrict
    #else
        #define MY_RESTRICT
    #endif
#else
    #define MY_RESTRICT __restrict
#endif
