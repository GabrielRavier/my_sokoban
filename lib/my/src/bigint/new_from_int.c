/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements creating a bigint from an integer
*/

#include "my/bigint.h"
#include "my/assert.h"
#include <stdlib.h>

struct my_bigint *my_bigint_new_from_int(int x)
{
    struct my_bigint *result = malloc(sizeof(struct my_bigint));

    MY_ASSERT(result != NULL);
    result->is_negative = (x < 0);
    if (result->is_negative)
        x = -x;
    result->number = my_string_new_from_string(&((char){x % 10}), 1);
    x /= 10;
    while (x != 0) {
        my_string_append_char(result->number, x % 10);
        x /= 10;
    }
    return (result);
}
