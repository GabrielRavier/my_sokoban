/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares bigint-related functions
*/

#pragma once

#include "my/config.h"
#include <unistd.h>
#include <stdbool.h>

struct my_bigint {
    size_t num_digits;
    unsigned char *number;
    bool is_negative;
};

bool my_bigint_init_str(struct my_bigint *num,
    const char *str) MY_ATTR_WARN_UNUSED_RESULT;
void my_bigint_add(struct my_bigint *result, const struct my_bigint *operand2);
void my_bigint_add_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2);
void my_bigint_sub(struct my_bigint *result,
    const struct my_bigint *operand2);
void my_bigint_sub_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2);
int my_bigint_compare(const struct my_bigint *operand1,
    const struct my_bigint *operand2) MY_ATTR_WARN_UNUSED_RESULT;
int my_bigint_compare_unsigned(const struct my_bigint *operand1,
    const struct my_bigint *operand2) MY_ATTR_WARN_UNUSED_RESULT;
bool my_bigint_dprint(int fd,
    const struct my_bigint *num) MY_ATTR_WARN_UNUSED_RESULT;
void my_bigint_free(const struct my_bigint *num);
