/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares functions from libmy
*/

#pragma once

#include "my/config.h"
#include <stddef.h>

size_t my_strlen(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strnlen(const char *string, size_t length) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strcpy(char *destination, const char *source);
char *my_strncpy(char *destination, const char *source, size_t n);
char *my_strdup(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strndup(const char *string, size_t length) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strcat(char *destination, const char *source);
char *my_strncat(char *destination, const char *source, size_t n);
char *my_strchr(const char *str, int character) MY_ATTR_WARN_UNUSED_RESULT;
int my_strcmp(const char *string1,
    const char *string2) MY_ATTR_WARN_UNUSED_RESULT;
int my_strncmp(const char *string1, const char *string2,
    size_t n) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strstr(const char *haystack,
    const char *needle) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strspn(const char *str,
    const char *accept) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strcspn(const char *str,
    const char *reject) MY_ATTR_WARN_UNUSED_RESULT;
void *my_memcpy(void *destination, const void *source, size_t size);
void *my_memset(void *ptr, int character, size_t length);
void *my_memchr(const void *ptr, int character,
    size_t length) MY_ATTR_WARN_UNUSED_RESULT;
