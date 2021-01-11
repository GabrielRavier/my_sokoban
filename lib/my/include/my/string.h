/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares string-related entities
*/

#pragma once

#include "features.h"
#include <stddef.h>

/// Calcualtes the length of the given string
size_t my_strlen(const char *string) MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_NONNULL((1)) MY_ATTR_PURE MY_ATTR_ACCESS((read_only, 1));

/// Determines the length of the given string, with a maximum length
size_t my_strnlen(const char *string, size_t length) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1, 2));

/// Copies a string
char *my_strcpy(char *destination, const char *source) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((write_only, 1))
    MY_ATTR_ACCESS((read_only, 2));

/// Copies a string, except that at most n bytes of src are copied. If there is
/// no null byte among the first n bytes of src, the string placed in dest is
/// not null-terminated. If the length of src is less than n, strncpy writes
/// additional null bytes to dst to ensure a total of n bytes are written
char *my_strncpy(char *destination, const char *source, size_t n)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((write_only, 1, 3))
    MY_ATTR_ACCESS((read_only, 2, 3));

/// Duplicates the given string, returning an (identical) malloc-ed string
char *my_strdup(const char *string) MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_MALLOC MY_ATTR_NONNULL((1)) MY_ATTR_ACCESS((read_only, 1));

/// Duplicates the given string, with a maximum length
char *my_strndup(const char *string, size_t length) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1, 2));

/// Appends source onto destination 
char *my_strcat(char *destination, const char *source) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_write, 1))
    MY_ATTR_ACCESS((read_only, 2));

/// Appends at most n bytes of source onto destination
char *my_strncat(char *destination, const char *source, size_t n)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_write, 1))
    MY_ATTR_ACCESS((read_only, 2, 3));

/// Returns a pointer to the first occurence of the given character in
/// the given string
char *my_strchr(const char *str, int character) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));

/// Compares two strings
int my_strcmp(const char *string1, const char *string2) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((read_only, 1)) MY_ATTR_ACCESS((read_only, 2));

/// Compares at most n characters of two strings
int my_strncmp(const char *string1, const char *string2, size_t n)
    MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE
    MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_only, 1, 3))
    MY_ATTR_ACCESS((read_only, 2, 3));

/// Finds the first occurence of needle in haystack
char *my_strstr(const char *haystack, const char *needle) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((read_only, 1)) MY_ATTR_ACCESS((read_only, 2));

/// Calculates the length of the initial segment of the given string entirely
/// composed of bytes in accept
size_t my_strspn(const char *str, const char *accept) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((read_only, 1)) MY_ATTR_ACCESS((read_only, 2));

/// Calculates the length of the initial segment of the given string entirely
/// composed of bytes not in reject
size_t my_strcspn(const char *str, const char *reject) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((read_only, 1)) MY_ATTR_ACCESS((read_only, 2));

/// Copies size bytes of source into destination
void *my_memcpy(void *destination, const void *source, size_t size)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((write_only, 1, 3)) MY_ATTR_ACCESS((read_only, 2, 3));

/// Same as my_memcpy, except source and destination may overlap
void *my_memmove(void *destination, const void *source, size_t size)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((1, 2))
    MY_ATTR_ACCESS((write_only, 1, 3)) MY_ATTR_ACCESS((read_only, 2, 3));

/// Fills the first length bytes of destination with character
void *my_memset(void *destination, int character, size_t length) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1)) MY_ATTR_ACCESS((write_only, 1, 3));

/// Scans the first length bytes of ptr for the first instance of character
void *my_memchr(const void *ptr, int character, size_t length) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1, 3));

/// Compares the first length bytes of s1 and s2
int my_memcmp(const void *s1, const void *s2, size_t length) MY_ATTR_NOTHROW
    MY_ATTR_PURE MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_only, 1, 3))
    MY_ATTR_ACCESS((read_only, 2, 3));

/// Finds the start of the first occurence of the needle (of length
/// needle_length) in haystack (of length haystack_length)
void *my_memmem(const void *haystack, size_t haystack_length,
    const void *needle, size_t needle_length) MY_ATTR_NOTHROW MY_ATTR_PURE
    MY_ATTR_NONNULL((1, 3)) MY_ATTR_ACCESS((read_only, 1, 2))
    MY_ATTR_ACCESS((read_only, 3, 4));
