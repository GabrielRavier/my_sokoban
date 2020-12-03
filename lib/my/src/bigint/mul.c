/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements bigint multiplication
*/

#include "my/bigint.h"

struct my_bigint_mul_internal_loop_bigint_args {
    struct my_bigint *result;
    struct my_bigint *step_add;
    const struct my_bigint *operand2;
};

static void remove_trailing_zeros(struct my_bigint *num)
{
    size_t i;

    for (i = num->number->length; i != 1; --i) {
        if (num->number->string[i - 1] != '\0')
            break;
    }
    my_string_resize(num->number, i);
}

static void my_bigint_mul_internal_loop(
    const struct my_bigint_mul_internal_loop_bigint_args *args,
    unsigned char *carry, size_t i)
{
    unsigned char multiplied_digit;

    for (size_t j = 0; j < args->result->number->length || *carry > 0; ++j) {
        if ((i + j) == args->step_add->number->length)
            my_string_append_char(args->step_add->number, 0);
        if (j < args->result->number->length)
            multiplied_digit = (args->result->number->string[j] *
                args->operand2->number->string[i]) + *carry;
        else
            multiplied_digit = *carry;
        args->step_add->number->string[i + j] = multiplied_digit % 10;
        *carry = multiplied_digit / 10;
    }
    remove_trailing_zeros(args->step_add);
}

static void set_result_sign(struct my_bigint *result,
    const struct my_bigint *operand1, const struct my_bigint *operand2)
{
    result->is_negative = (operand1->is_negative != operand2->is_negative) &&
        (my_bigint_compare_int(operand1, 0) != 0) &&
        (my_bigint_compare_int(operand2, 0) != 0);
}

struct my_bigint *my_bigint_mul(struct my_bigint *result,
    const struct my_bigint *operand2)
{
    struct my_bigint *temporary_result = my_bigint_new_from_int(0);
    struct my_bigint *step_add = my_bigint_new_from_int(0);
    unsigned char carry = 0;

    for (size_t i = 0; i < operand2->number->length; ++i) {
        if (i > 0) {
            my_string_resize(step_add->number, i);
            step_add->number->string[i - 1] = 0;
        }
        my_bigint_mul_internal_loop(
            &((struct my_bigint_mul_internal_loop_bigint_args){
                result, step_add, operand2 }), &carry, i);
        my_bigint_add(temporary_result, step_add);
    }
    set_result_sign(temporary_result, result, operand2);
    my_bigint_assign(result, temporary_result);
    my_bigint_free(temporary_result);
    my_bigint_free(step_add);
    return (result);
}

struct my_bigint *my_bigint_mul_int(struct my_bigint *result, int operand2)
{
    struct my_bigint *tmp = my_bigint_new_from_int(operand2);

    my_bigint_mul(result, tmp);
    my_bigint_free(tmp);
    return result;
}
