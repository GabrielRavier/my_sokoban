/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Adds two unsigned bigints
*/

#include "my/internal/bigint.h"
#include "my/macros.h"

void my_bigint_add_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    size_t required_digits =
        MY_MAX(result->num_digits, operand2->num_digits) + 1;
    bool carry = false;
    unsigned char total;
    my_bigint_at_least_digits(result, required_digits);

    for (size_t i = 0; (i < operand2->num_digits) || carry; ++i) {
        if (i == result->num_digits) {
            result->number[i] = 0;
            ++result->num_digits;
        }
        total = result->number[i] +
            (i < operand2->num_digits ? operand2->number[i] : 0) + carry;
        result->number[i] = total % 10;
        carry = (total >= 10);
    }
}
