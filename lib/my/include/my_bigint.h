/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares bigint-related functions
*/

#pragma once

struct my_bigint
{
    int dummy;
};

void my_bigint_init_with_str(struct my_bigint *num, const char *str);
void my_bigint_add(struct my_bigint *result, const struct my_bigint *operand1, const struct my_bigint *operand2);
void my_bigint_print(const struct my_bigint *num);
