/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares bigint-related functions
*/

#pragma once

#include <unistd.h>
#include <stdbool.h>

// This is a basic implementation, but I ain't too much of an expert so I
// wouldn't really be confident in doing a complicated usual-style
// implementation
struct my_bigint {
    bool is_negative;
    char *number;
};

bool my_bigint_set_str(struct my_bigint *num, const char *str);
void my_bigint_add(struct my_bigint *result, const struct my_bigint *operand2);
void my_bigint_add_unsigned(struct my_bigint *result, const struct my_bigint *operand2);
void my_bigint_sub(struct my_bigint *result, const struct my_bigint *operand2);
void my_bigint_sub_unsigned(struct my_bigint *result, const struct my_bigint *operand2);
int my_bigint_compare_unsigned(
    const struct my_bigint *operand1, const struct my_bigint *operand2);
void my_bigint_dprint(int fd, const struct my_bigint *num);
void my_bigint_free(const struct my_bigint *num);
