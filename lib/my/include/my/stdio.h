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

typedef fpos_t my_fpos_t;
typedef FILE my_file_t;

    #define my_stdin stdin
    #define my_stdout stdout
    #define my_stderr stderr

#else

typedef off_t my_fpos_t;

// A buffer for the my_file_t implementation
struct my_file_buffer {
    ssize_t size;
    unsigned char *base;
};

// This is the structure we use to implement my_file_t
// fd is the file descriptor attached to the file (or -1 if we're not a file)
// offset is the current file offset from lseek
// internal_data is passed to read, write, seek and close
// line_buffer_size is either 0 or -buffer.size, this is to optimize putc
// buffer_ptr points to the next byte in the buffer
// one_char_read_buffer is the "buffer" we use when unbuffered or when malloc
// fails
// Whether flags is non-0 marks whether the file entry is used (used in
// find_ptr to determine which files are in use)
// MY_FILE_FLAG_FSEEK_OPT and MY_FILE_FLAG_NO_FSEEK_OPT both exist because we
// want to be able to distinguish the case where we haven't yet determined
// whether the optimization is possible
extern struct my_file_type {
    int fd;
    off_t offset;
    enum {
        MY_FILE_FLAG_READ = 1 << 0,
        MY_FILE_FLAG_WRITE = 1 << 1,
        MY_FILE_FLAG_READ_WRITE = 1 << 2,
        MY_FILE_FLAG_NOT_BUFFERED = 1 << 3,
        MY_FILE_FLAG_LINE_BUFFERED = 1 << 4,
        MY_FILE_FLAG_BUFFER_MALLOCED = 1 << 5,
        MY_FILE_FLAG_ERROR = 1 << 6,
        MY_FILE_FLAG_IS_OFFSET_CORRECT = 1 << 7,
        MY_FILE_FLAG_FSEEK_OPT = 1 << 8,
        MY_FILE_FLAG_NO_FSEEK_OPT = 1 << 9,
    } flags;
    void *internal_data;
    ssize_t (*read)(void *internal_data, unsigned char *buffer, ssize_t count);
    ssize_t (*write)(void *internal_data, const unsigned char *buffer,
        ssize_t count);
    my_fpos_t (*seek)(void *internal_data, my_fpos_t offset, int whence);
    int (*close)(void *internal_data);
    ssize_t write_space_left;
    ssize_t line_buffer_size;
    unsigned char *buffer_ptr;
    struct my_file_buffer buffer;
    unsigned char one_char_read_buffer[1];
} g_my_standard_files[3];

typedef struct my_file_type my_file_t;

    #define my_stdin (&g_my_standard_files[0])
    #define my_stdout (&g_my_standard_files[1])
    #define my_stderr (&g_my_standard_files[2])

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

// Open a file and create a new my_file_t for it
my_file_t *my_fopen(const char *MY_RESTRICT filename,
    const char *MY_RESTRICT mode) MY_ATTR_WARN_UNUSED_RESULT;

// Writes a character to fp
int my_fputc(int c, my_file_t *fp);
int my_putc(int c, my_file_t *fp);

// Closes the passed file
int my_fclose(my_file_t *fp);

// Flushes the passed file, or all of them if fp is NULL
int my_fflush(my_file_t *fp);

// Returns the file descriptor for the given file
int my_fileno(my_file_t *fp) MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT;

// Returns the error indicator for the given file
int my_ferror(my_file_t *fp) MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT;

// Writes size * n bytes from the given buffer to the given file
size_t my_fwrite(const void *MY_RESTRICT buffer, size_t size, size_t count,
    my_file_t *fp);

static inline void my_fclose_ptr(my_file_t **ptr)
{
    if (*ptr)
        my_fclose(*ptr);
}

#define MY_CLEANUP_FCLOSE __attribute__((cleanup(my_fclose_ptr)))
