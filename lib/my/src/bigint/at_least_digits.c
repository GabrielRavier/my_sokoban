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
    char *old_number = num->number;
    
    if (my_strlen(num->number) < required_digits) {
        num->number = malloc(required_digits + 1);
        my_memcpy(num->number, old_number, my_strlen(old_number) + 1);

        free(old_number);
    }
}
