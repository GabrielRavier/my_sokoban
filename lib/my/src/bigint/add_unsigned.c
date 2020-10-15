/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Adds two unsigned bigints
*/

#include "my_bigint_internal.h"
#include "my.h"

void my_bigint_add_unsigned(
    struct my_bigint *result, const struct my_bigint *operand2)
{
    size_t required_digits =
        MY_MAX(my_strlen(result->number), my_strlen(operand2->number)) + 1;
    bool carry = false;
    unsigned char total;
    my_bigint_at_least_digits(result, required_digits);

    for (size_t i = 0; (i < my_strlen(operand2->number)) || (carry); ++i) {
        if (i == my_strlen(result->number))
            result->number[i + 1] = '\0';

        total = result->number[i] +
            (i < my_strlen(operand2->number) ? operand2->number[i] : 0) + carry;
        result->number[i] = total % 10;
        carry = (total >= 10);
    }
}
