/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares stdio-related entities
*/

#pragma once

#include "features.h"
#include <stdio.h>
#include <stdarg.h>

/// Writes the given character to stdout
int my_putchar(int character);

/// Writes the given character to the given file descriptor
int my_dputc(int character, int fd);

/// Writes the given string to the given file descriptor
int my_dputs(const char *string, int fd);

/// Write the given string and a trailing newline to stdout
int my_puts(const char *string);

/// Writes formatted output to stdout
int my_printf(const char *format, ...) MY_ATTR_FORMAT(printf, 1, 2);

/// Like my_printf, except it takes a va_list instead of a variables amount of
/// arguments
int my_vprintf(const char *format, va_list arguments)
    MY_ATTR_FORMAT(printf, 1, 0);

/// Writes formatted output to the given file descriptor
int my_dprintf(int fd, const char *format, ...) MY_ATTR_FORMAT(printf, 2, 3);

/// Like my_dprintf, except it takes a va_list instead of a variables amount of
/// arguments
int my_vdprintf(int fd, const char *format, va_list arguments)
    MY_ATTR_FORMAT(printf, 2, 0);

/// Allocate a string large enough to hold the formatted output (including the
/// null terminator), write formatted output to it and return a pointer to it
/// through the first argument
int my_asprintf(char **result_string_ptr, const char *format, ...)
    MY_ATTR_FORMAT(printf, 2, 3) MY_ATTR_WARN_UNUSED_RESULT;

/// Like my_asprintf, except it takes a va_list instead of a variables amount of
/// arguments
int my_vasprintf(char **result_string_ptr, const char *format,
    va_list arguments) MY_ATTR_FORMAT(printf, 2, 0) MY_ATTR_WARN_UNUSED_RESULT;

static inline void my_fclose_ptr(FILE **ptr)
{
    if (*ptr)
        fclose(*ptr);
}

#define MY_CLEANUP_FCLOSE __attribute__((cleanup(my_fclose_ptr)))
