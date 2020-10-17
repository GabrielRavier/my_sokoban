/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares functions from libmy
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "my_config.h"

int my_putchar(int character) MY_ATTR_WARN_UNUSED_RESULT;
int my_dputc(int character, int fd) MY_ATTR_WARN_UNUSED_RESULT;
bool my_putnbr(int number) MY_ATTR_WARN_UNUSED_RESULT;
bool my_putnbr_base(int number, const char *base) MY_ATTR_WARN_UNUSED_RESULT;
bool my_putnbr_base_width(int number, const char *base, size_t width) MY_ATTR_WARN_UNUSED_RESULT;
char *my_nbr_to_string(int number) MY_ATTR_WARN_UNUSED_RESULT;
char *my_nbr_to_string_base(int number, const char *base) MY_ATTR_WARN_UNUSED_RESULT;
char *my_nbr_to_string_base_width(int number, const char *base, size_t width) MY_ATTR_WARN_UNUSED_RESULT;
void my_swap(int *a, int *b);
int my_dputs(const char *string, int fd) MY_ATTR_WARN_UNUSED_RESULT;
int my_puts(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strlen(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
int my_getnbr(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
int my_getnbr_base(const char *string, const char *base) MY_ATTR_WARN_UNUSED_RESULT;
// Internal, should probably be moved to some place like
// include/getnbr-internal.h or something
bool my_find_digit_from_base(const char *digit_character_ptr, const char *base,
    unsigned char *digit_ptr) MY_ATTR_WARN_UNUSED_RESULT;
void my_sort_int_array(int *array, int size);
int my_compute_power_rec(int number, int power) MY_ATTR_WARN_UNUSED_RESULT;
int my_compute_square_root(int number) MY_ATTR_WARN_UNUSED_RESULT;
int my_is_prime(int number) MY_ATTR_WARN_UNUSED_RESULT;
int my_find_prime_sup(int number) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strcpy(char *destination, const char *source);
char *my_strncpy(char *destination, const char *source, int n);
char *my_strchr(const char *str, int character) MY_ATTR_WARN_UNUSED_RESULT;
char *my_revstr(char *string);
char *my_strstr(const char *haystack, const char *needle) MY_ATTR_WARN_UNUSED_RESULT;
int my_strcmp(const char *string1, const char *string2) MY_ATTR_WARN_UNUSED_RESULT;
int my_strncmp(const char *string1, const char *string2, size_t n) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strupcase(char *string);
char *my_strlowcase(char *string);
char *my_strcapitalize(char *string);
int my_str_isalpha(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
int my_str_isnum(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
int my_str_islower(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
int my_str_isupper(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
int my_str_isprintable(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strcat(char *destination, const char *source);
char *my_strncat(char *destination, const char *source, int n);
int my_isprint(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_isupper(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_isalnum(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_isdigit(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_isalpha(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_islower(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_tolower(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
int my_toupper(int character) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;
bool my_checked_multiply(int lhs, int rhs, int *result) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strspn(const char *str, const char *accept) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strcspn(const char *str, const char *reject) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_strnlen(const char *string, size_t length) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strdup(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
char *my_strndup(const char *string, size_t length) MY_ATTR_WARN_UNUSED_RESULT;
size_t my_count_byte_occurences(const char *first, const char *last,
    char character) MY_ATTR_WARN_UNUSED_RESULT;
void my_qsort(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *));
void my_qsort_r(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *, void *),
    void *argument);
void *my_memcpy(void *destination, const void *source, size_t size);
void *my_memchr(const void *ptr, int character, size_t length) MY_ATTR_WARN_UNUSED_RESULT;
void *my_memset(void *ptr, int character, size_t length);
void *my_realloc_size(void *ptr, size_t new_length, size_t original_length) MY_ATTR_WARN_UNUSED_RESULT;
bool my_show_word_array(char *const *table) MY_ATTR_WARN_UNUSED_RESULT;
char **my_str_to_word_array(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
float my_fabsf(float x) MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_CONST;

// ONLY USE THIS MACRO WITH ARRAYS, NEVER WITH POINTERS
#define MY_COUNTOF(array) ((sizeof(array)) / (sizeof(array[0])))

#define MY_MAX(a, b) ((a) > (b) ? (a) : (b))
