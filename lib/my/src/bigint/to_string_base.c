/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts a bigint to a string of a given base
*/

#include "my/bigint.h"
#include "my/string.h"

struct my_string *my_bigint_to_string_base(struct my_bigint *num,
    const char *base)
{
    struct my_string *result = my_string_new();
    struct my_bigint *tmp_mod_result = my_bigint_new_from_int(0);
    int base_len = (int)my_strlen(base);
    bool is_num_negative = num->is_negative;

    if (num->is_negative)
        num->is_negative = false;
    do {
        my_string_insert_char(result,
            base[my_bigint_to_int(my_bigint_mod_int(
                my_bigint_assign(tmp_mod_result, num), base_len))],
            0);
        my_bigint_div_int(num, base_len);
    } while (my_bigint_compare_int(num, 0));
    my_bigint_free(tmp_mod_result);
    if (is_num_negative)
        my_string_insert_char(result, '-', 0);
    return (result);
}
