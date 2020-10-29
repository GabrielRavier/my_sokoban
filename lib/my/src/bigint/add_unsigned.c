/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Adds two unsigned bigints
*/

#include "my/internal/bigint.h"
#include "my/macros.h"

struct my_bigint *my_bigint_add_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    bool carry = false;
    unsigned char total;

    for (size_t i = 0; (i < operand2->number->length) || carry; ++i) {
        if (i == result->number->length) {
            my_string_append_char(result->number, 0);
            result->number->string[i] = 0;
        }
        total = result->number->string[i] +
            (i < operand2->number->length ? operand2->number->string[i] : 0) +
            carry;
        result->number->string[i] = total % 10;
        carry = (total >= 10);
    }
    return (result);
}
