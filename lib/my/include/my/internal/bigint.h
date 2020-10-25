/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares internal bigint functions
*/

#include "my/bigint.h"

// Makes sure that num has at least the required amount of digits in it
// (reallocates if needed)
void my_bigint_at_least_digits(struct my_bigint *num, size_t required_digits);