/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Sets an initialized bigint from a string
*/

#include "my/bigint.h"
#include "my/misc.h"
#include "my/string.h"
#include "my/assert.h"
#include <stdlib.h>

// Maybe add stuff like skipping whitespace in the future ? idk
struct my_bigint *my_bigint_new_from_str(const char *str)
{
    struct my_bigint *result = malloc(sizeof(struct my_bigint));

    if (*str == '-') {
        result->is_negative = true;
        ++str;
    } else
        result->is_negative = false;
    if (!my_str_isnum(str))
        return (false);
    while (*str == '0' && *(str + 1) != '\0')
        ++str;
    result->number = (unsigned char *)my_strdup(str);
    MY_ASSERT(result->number != NULL);
    result->num_digits = my_strlen(str);
    my_revstr((char *)result->number);
    for (size_t i = 0; i < result->num_digits; ++i)
        result->number[i] -= '0';
    return result;
}
