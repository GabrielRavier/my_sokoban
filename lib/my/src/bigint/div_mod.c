/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements division and modulo for libmy
*/

#include "my/internal/bigint.h"
#include "my/assert.h"
#include <stdbool.h>

static void my_bigint_div_mod_unsigned(const struct my_bigint *num,
    const struct my_bigint *divisor, struct my_bigint *quotient,
    struct my_bigint *remainder)
{
    struct my_bigint *k = my_bigint_new_from_int(0);
    struct my_bigint *x = my_bigint_new_from_int(0);
    struct my_bigint *t = my_bigint_new_from_int(0);

    my_bigint_assign(remainder, num)->is_negative = false;
    while (my_bigint_compare_unsigned(remainder, divisor) >= 0) {
        my_bigint_free(k);
        k = my_bigint_new_from_int(1);
        my_bigint_assign(x, divisor)->is_negative = false;
        while (true) {
            my_bigint_add(my_bigint_assign(t, x), t);
            if (my_bigint_compare_unsigned(t, remainder) >= 0)
                break;
            my_bigint_assign(x, t);
            my_bigint_add(k, k);
        }
        my_bigint_add_unsigned(quotient, k);
        my_bigint_sub_unsigned(remainder, x);
    }
}

void my_bigint_div_mod(const struct my_bigint *num,
    const struct my_bigint *divisor, struct my_bigint *quotient,
    struct my_bigint *remainder)
{
    bool is_quotient_result_negative = false;
    bool is_remainder_result_result = false;

    if (num->is_negative) {
        is_quotient_result_negative = !is_quotient_result_negative;
        is_remainder_result_result = true;
    }
    if (divisor->is_negative)
        is_quotient_result_negative = !is_quotient_result_negative;
    my_bigint_div_mod_unsigned(num, divisor, quotient, remainder);
    if (is_quotient_result_negative)
        my_bigint_neg(quotient);
    if (is_remainder_result_result)
        my_bigint_neg(remainder);
}
