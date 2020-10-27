/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares bigint-related functions
*/

#pragma once

#include "my/config.h"
#include "my/my_string.h"
#include <unistd.h>
#include <stdbool.h>

// The number is stored as an array of char, with a value of 0 to 9 (integer,
// not characters)
struct my_bigint {
    struct my_string *number;
    bool is_negative;
};

// Creates a new bigint, based on the contents of str
struct my_bigint *my_bigint_new_from_str(const char *str)
    MY_ATTR_WARN_UNUSED_RESULT;

// Creates a new bigint, based on the contents of the passed integer
struct my_bigint *my_bigint_new_from_int(int x)
    MY_ATTR_WARN_UNUSED_RESULT;

// Copies source into destination
void my_bigint_assign(struct my_bigint *destination,
    const struct my_bigint *source);

// result += operand2
void my_bigint_add(struct my_bigint *result, const struct my_bigint *operand2);

// Same as above, but does not handle signs
void my_bigint_add_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2);

// result -= operand2
void my_bigint_sub(struct my_bigint *result,
    const struct my_bigint *operand2);

// Same as above, but does not handle signs
void my_bigint_sub_unsigned(struct my_bigint *result,
    const struct my_bigint *operand2);

// result *= operand2
void my_bigint_mul(struct my_bigint *result,
    const struct my_bigint *operand2);

// Returns either -1 (operand1 < operand2), 0 (operand1 == operand2)
// or 1 (operand1 > operand2)
int my_bigint_compare(const struct my_bigint *operand1,
    const struct my_bigint *operand2) MY_ATTR_WARN_UNUSED_RESULT;

// Same as above, but does not handle signs
int my_bigint_compare_unsigned(const struct my_bigint *operand1,
    const struct my_bigint *operand2) MY_ATTR_WARN_UNUSED_RESULT;

// Prints num to the given fd
bool my_bigint_dprint(int fd,
    const struct my_bigint *num) MY_ATTR_WARN_UNUSED_RESULT;

// Destructs the passed bigint and the associated data.
void my_bigint_free(struct my_bigint *num);
