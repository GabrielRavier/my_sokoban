/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements bigint multiplication
*/

#include "my/bigint.h"

void my_bigint_mul(struct my_bigint *result, const struct my_bigint *operand2)
{
    struct my_bigint *temporary_result = my_bigint_new_from_int(0);
    struct my_bigint *step_add = my_bigint_new_from_int(0);
    unsigned char carry = 0;
    unsigned char multiplied_digit;

    for (size_t i = 0; i < operand2->number->length; ++i) {
        if (i > 0) {
            my_string_append_char(step_add->number, i);
            step_add->number->string[i - 1] = 0;
        }
        for (size_t j = 0; j < result->number->length || carry > 0; ++j) {
            if ((i + j) > step_add->number->length)
                my_string_append_char(step_add->number, 0);
            if (j < result->number->length)
                multiplied_digit =
                    (result->number->string[j] * operand2->number->string[i]) +
                    carry;
            else
                multiplied_digit = carry;
            step_add->number->string[i + j] = multiplied_digit % 10;
            carry = multiplied_digit / 10;
        }
        my_bigint_add(temporary_result, step_add);
    }
    temporary_result->is_negative =
        (result->is_negative != operand2->is_negative);
    my_bigint_assign(result, temporary_result);
    my_bigint_free(temporary_result);
    my_bigint_free(step_add);
}
