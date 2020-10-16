/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Makes sure the string is big enough to contain the required amount of digits
*/

#include "my_bigint_internal.h"
#include "my.h"
#include <stdlib.h>

void my_bigint_at_least_digits(struct my_bigint *num, size_t required_digits)
{
    unsigned char *old_number = num->number;

    if (num->num_digits < required_digits) {
        num->number = (unsigned char *)malloc(required_digits);
        my_memcpy(num->number, old_number, num->num_digits);

        free(old_number);
    }
}
