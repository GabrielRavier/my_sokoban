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

    my_bigint_assign(remainder, num);
    while (my_bigint_compare(remainder, divisor) >= 0) {
        my_bigint_free(k);
        k = my_bigint_new_from_int(1);
        my_bigint_assign(x, divisor);
        while (true) {
            my_bigint_mul_int(my_bigint_assign(t, x), 2);
            if (my_bigint_compare(t, remainder) >= 0)
                break;
            my_bigint_assign(x, t);
            my_bigint_mul_int(k, 2);
        }
        my_bigint_add(quotient, k);
        my_bigint_sub(remainder, x);
    }
}

void my_bigint_div_mod(const struct my_bigint *num,
    const struct my_bigint *divisor, struct my_bigint *quotient,
    struct my_bigint *remainder)
{
    struct my_bigint *copy = my_bigint_new_from_int(0);

    if (my_bigint_compare_int(divisor, 0) < 0) {
        my_bigint_div_mod(num, my_bigint_neg(my_bigint_assign(copy, divisor)),
            quotient, remainder);
        my_bigint_free(copy);
        my_bigint_neg(quotient);
    } else if (my_bigint_compare_int(num, 0) < 0) {
        my_bigint_div_mod(my_bigint_neg(my_bigint_assign(copy, num)), divisor,
            quotient, remainder);
        my_bigint_neg(quotient);
        if (my_bigint_compare_int(remainder, 0) != 0)
            my_bigint_assign(remainder,
                my_bigint_sub(my_bigint_assign(copy, divisor), remainder));
        my_bigint_free(copy);
    } else
        my_bigint_div_mod_unsigned(num, divisor, quotient, remainder);
}
