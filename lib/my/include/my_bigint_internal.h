/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Internal bigint functions
*/

#include "my_bigint.h"

// Makes sure that num has at least the required amount of digits in it (reallocates if needed) 
void my_bigint_at_least_digits(struct my_bigint *num, size_t required_digits);
