/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts and returns a number in a given base
*/

#include "my/stdlib.h"
#include "my/misc.h"
#include "my/ctype.h"
#include "my/internal/strtol_base_str_part2.h"
#include "my/string.h"
#include <stdbool.h>
#include <limits.h>

// "digits" is defined as being anything from base
// the base is the length of the base string

// Sets *number_ptr_ptr to the location of the number (points to terminator if
// no number was found). This is very greedy and will try to find *any* number
// in the passed string, so unless there are no digits before the string is
// terminated, this will find it We set *is_negative_ptr depending whether '-'
// was found an even or odd amount of times before the number
static void find_number(const char **number_ptr_ptr, bool *is_negative_ptr)
{
    const char *const number_ptr = *number_ptr_ptr;
    const char *first_digit = number_ptr + my_strspn(number_ptr, "\t\v\f\n\r ");
    first_digit += my_strspn(first_digit, "-+");

    *is_negative_ptr =
        ((my_count_byte_occurences(number_ptr, first_digit, '-') % 2));
    *number_ptr_ptr = first_digit;
}

// current_result must be a negative number, we check whether adding the digit
// will overflow below LONG_MIN
static bool is_about_to_overflow(long current_result,
    unsigned char current_digit, size_t base)
{
    const long long_min_without_last_digit = LONG_MIN / (long)base;
    const long long_min_last_digit = -(LONG_MIN % (long)base);

    return (current_result < long_min_without_last_digit ||
        (current_result == long_min_without_last_digit &&
            current_digit > long_min_last_digit));
}

// Handles the case where we were actually asked to get a positive number (and
// handle LONG_MIN properly then)
static long handle_positive_negative_for_do_parse(long result, bool is_negative)
{
    if (!is_negative) {
        if (result == LONG_MIN)
            return LONG_MAX;
        result = -result;
    }
    return (result);
}

// We do the parse by using negative numbers and then negating in the end when
// we find a good result because the absolute of LONG_MIN is larger than
// LONG_MAX.
// This also handles overflow and the sign of the parsed number
// This assumes the base is 10 (which it is as of the writing of this comment),
// but may have to be adapted if re-used in a more generic function in the
// future
static long do_parse(const char *num_ptr, bool is_negative, const char *base,
    char **end_num_ptr)
{
    long result = 0;
    unsigned char current_digit;
    const size_t base_width = my_strlen(base);

    while (true) {
        if (!my_find_digit_from_base(num_ptr++, base, &current_digit)) {
            if (end_num_ptr != NULL)
                *end_num_ptr = (char *)(num_ptr - 1);
            break;
        }
        if (is_about_to_overflow(result, current_digit, base_width)) {
            if (end_num_ptr != NULL)
                *end_num_ptr = (char *)(num_ptr - 1);
            return (is_negative ? LONG_MIN : LONG_MAX);
        }
        result *= (long)base_width;
        result -= current_digit;
    }
    return (handle_positive_negative_for_do_parse(result, is_negative));
}

long my_strtol_base_str(const char *num_ptr, char **end_num_ptr,
    const char *base)
{
    bool is_negative;
    const char *const orig_ptr = num_ptr;

    find_number(&num_ptr, &is_negative);
    if (*num_ptr == '\0' || (my_strchr(base, *num_ptr) == NULL)) {
        if (end_num_ptr != NULL)
            *end_num_ptr = (char *)orig_ptr;
        return (0);
    }
    return (do_parse(num_ptr, is_negative, base, end_num_ptr));
}
