/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Does an unsigned subtraction of two bigints
*/

#include "my_bigint_internal.h"
#include "my_bigint.h"
#include "my.h"

static unsigned char get_digit(struct my_bigint smaller_greater_num[2], size_t i, bool carry)
{
    if (i < smaller_greater_num[0].num_digits)
        return smaller_greater_num[1].number[i] -
            smaller_greater_num[0].number[i] - carry;
    else
        return smaller_greater_num[1].number[i] - carry;
}

void my_bigint_sub_unsigned(
    struct my_bigint *result, const struct my_bigint *operand2)
{
    bool which_bigger = my_bigint_compare_unsigned(result, operand2) > 0;
    struct my_bigint smaller_greater_num[2];
    bool carry = false;
    signed char digit;
    my_bigint_at_least_digits(
        result, MY_MAX(result->num_digits, operand2->num_digits) + 1);
    smaller_greater_num[0] = which_bigger ? *operand2 : *result;
    smaller_greater_num[1] = which_bigger ? *result : *operand2;
    result->num_digits = 1;

    for (size_t i = 0; i < smaller_greater_num[1].num_digits; ++i) {
        digit = get_digit(smaller_greater_num, i, carry);
        if (digit < 0) {
            carry = true;
            digit += 10;
        } else
            carry = false;
        result->number[i] = digit;
        if (digit != 0)
            result->num_digits = i + 1;
    }
}
