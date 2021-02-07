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
#include <stdint.h>

#if LIBMY_USE_LIBC_FILE
    #define MY_FILE FILE
    #define my_stdout stdout
#else

extern struct my_file_type {
    char *buffer_ptr;
    char *buffer_base;
    ssize_t buffer_count;
    ssize_t buffer_size;
    int fd;
    enum {
        MY_FILE_FLAG_READ = 1,
        MY_FILE_FLAG_WRITE = 2,
        MY_FILE_FLAG_READ_WRITE = 4,
        MY_FILE_FLAG_EOF = 8,
        MY_FILE_FLAG_NOT_BUFFERED = 16,
        MY_FILE_FLAG_LINE_BUFFERED = 32,
        MY_FILE_FLAG_BUFFER_MALLOCED = 64,
        MY_FILE_FLAG_ERROR = 128,
    } flag;
} g_my_files[1024];
typedef struct my_file_type MY_FILE;
#define my_stdin (&g_my_files[0])
#define my_stdout (&g_my_files[1])
#define my_stderr (&g_my_files[2])

#endif

/// Writes the given character to stdout
int my_putchar(int character);

/// Writes the given character to the given file descriptor
int my_dputc(int character, int fd);

/// Reads the next character from the given file descriptor
int my_dgetc(int fd);

/// Writes the given string to the given file descriptor
int my_dputs(const char *string, int fd) MY_ATTR_NONNULL((1));

/// Write the given string and a trailing newline to stdout
int my_puts(const char *string) MY_ATTR_NONNULL((1));

/// Writes formatted output to stdout
int my_printf(const char *MY_RESTRICT format, ...) MY_ATTR_FORMAT(printf, 1, 2);

/// Like my_printf, except it takes a va_list instead of a variables amount of
/// arguments
int my_vprintf(const char *MY_RESTRICT format, va_list arguments)
    MY_ATTR_FORMAT(printf, 1, 0);

/// Writes formatted output to the given file descriptor
int my_dprintf(int fd, const char *MY_RESTRICT format, ...)
    MY_ATTR_FORMAT(printf, 2, 3);

/// Like my_dprintf, except it takes a va_list instead of a variables amount of
/// arguments
int my_vdprintf(int fd, const char *MY_RESTRICT format, va_list arguments)
    MY_ATTR_FORMAT(printf, 2, 0);

/// Allocate a string large enough to hold the formatted output (including the
/// null terminator), write formatted output to it and return a pointer to it
/// through the first argument
int my_asprintf(char **MY_RESTRICT result_string_ptr,
    const char *MY_RESTRICT format, ...) MY_ATTR_FORMAT(printf, 2, 3)
    MY_ATTR_WARN_UNUSED_RESULT;

/// Like my_asprintf, except it takes a va_list instead of a variables amount of
/// arguments
int my_vasprintf(char **MY_RESTRICT result_string_ptr,
    const char *MY_RESTRICT format, va_list arguments)
    MY_ATTR_FORMAT(printf, 2, 0) MY_ATTR_WARN_UNUSED_RESULT;

// Open a file and create a new stream for it
MY_FILE *my_fopen(const char *MY_RESTRICT filename,
    const char *MY_RESTRICT mode) MY_ATTR_WARN_UNUSED_RESULT;

// Write a character to stream
int my_fputc(int c, MY_FILE *stream);
int my_putc(int c, MY_FILE *stream);

// Close stream
int my_fclose(MY_FILE *stream);

// Flush the passed stream
int my_fflush(MY_FILE *stream);

static inline void my_fclose_ptr(MY_FILE **ptr)
{
    if (*ptr)
        my_fclose(*ptr);
}

#define MY_CLEANUP_FCLOSE __attribute__((cleanup(my_fclose_ptr)))
