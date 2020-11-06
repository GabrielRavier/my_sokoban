/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares stdio-related functions from libmy
*/

#pragma once

#include "my/config.h"
#include <stdarg.h>

int my_putchar(int character);
int my_dputc(int character, int fd);
int my_dputs(const char *string, int fd);
int my_puts(const char *string);
int my_printf(const char *format, ...) MY_ATTR_FORMAT(printf, 1, 2);
int my_vprintf(const char *format, va_list arguments)
    MY_ATTR_FORMAT(printf, 1, 0);
int my_dprintf(int fd, const char *format, ...) MY_ATTR_FORMAT(printf, 2, 3);
int my_vdprintf(int fd, const char *format, va_list arguments)
    MY_ATTR_FORMAT(printf, 2, 0);
int my_asprintf(char **result_string_ptr, const char *format, ...)
    MY_ATTR_FORMAT(printf, 2, 3) MY_ATTR_WARN_UNUSED_RESULT;
int my_vasprintf(char **result_string_ptr, const char *format,
    va_list arguments) MY_ATTR_FORMAT(printf, 2, 0) MY_ATTR_WARN_UNUSED_RESULT;
