/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Does an unsigned subtraction of two bigints
*/

#include "my/bigint.h"
#include "my/macros.h"

static signed char get_digit(const struct my_bigint *smaller_greater_num[2],
    size_t i, bool carry)
{
    if (i < smaller_greater_num[0]->number->length)
        return (smaller_greater_num[1]->number->string[i] -
            smaller_greater_num[0]->number->string[i] - carry);
    return (smaller_greater_num[1]->number->string[i] - carry);
}

struct my_bigint *my_bigint_sub_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    bool which_bigger = my_bigint_compare_unsigned(result, operand2) > 0;
    const struct my_bigint *smaller_greater_num[2];
    bool carry = false;
    signed char digit;

    smaller_greater_num[0] = which_bigger ? operand2 : result;
    smaller_greater_num[1] = which_bigger ? result : operand2;
    my_string_resize(result->number, smaller_greater_num[1]->number->length);
    for (size_t i = 0; i < smaller_greater_num[1]->number->length; ++i) {
        digit = get_digit(smaller_greater_num, i, carry);
        if (digit < 0) {
            carry = true;
            digit += 10;
        } else
            carry = false;
        result->number->string[i] = (unsigned char)digit;
    }
    return result;
}
