/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements strtol_base_str for bigint
*/

#include "my/bigint.h"
#include "my/internal/strtol_base_str_part2.h"
#include "my/string.h"

static void set_end_num_ptr(char **end_num_ptr, char *value)
{
    if (end_num_ptr != NULL)
        *end_num_ptr = value;
}

struct my_bigint *my_bigint_strtol_base_str(const char *num_ptr,
    char **end_num_ptr, const char *base)
{
    struct my_bigint *result = my_bigint_new_from_int(0);
    unsigned char current_digit;
    int base_width = (int)my_strlen(base);

    while (true) {
        if (!my_find_digit_from_base(num_ptr++, base, &current_digit)) {
            set_end_num_ptr(end_num_ptr, (char *)(num_ptr - 1));
            break;
        }
        my_bigint_mul_int(result, base_width);
        my_bigint_add_int(result, current_digit);
    }
    return result;
}
