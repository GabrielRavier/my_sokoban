/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts and returns a number in a given base
*/

#include "my/misc.h"
#include "my/internal/getnbr_part2.h"
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
    const char *number_ptr = *number_ptr_ptr;
    const char *first_digit = number_ptr + my_strspn(number_ptr, " -+");

    *is_negative_ptr =
        ((my_count_byte_occurences(number_ptr, first_digit, '-') % 2));
    *number_ptr_ptr = first_digit;
}

// current_result must be a negative number, we check whether adding the digit
// will overflow below INT_MIN
// is_about_to_overflow
static bool is_about_to_overflow(int current_result,
    unsigned char current_digit, size_t base)
{
    int int_min_without_last_digit = INT_MIN / (int)base;
    int int_min_last_digit = -(INT_MIN % (int)base);

    return (current_result < int_min_without_last_digit ||
        (current_result == int_min_without_last_digit &&
            current_digit > int_min_last_digit));
}

// Handles the case where we were actually asked to get a positive number (and
// handle INT_MIN properly then)
static int handle_positive_negative_for_do_parse(int result, bool is_negative)
{
    if (!is_negative) {
        if (result == INT_MIN)
            return (0);
        result = -result;
    }
    return (result);
}

// We do the parse by using negative numbers and then negating in the end when
// we find a good result because the absolute of INT_MIN is larger than INT_MAX.
// This also handles overflow and the sign of the parsed number
// This assumes the base is 10 (which it is as of the writing of this comment),
// but may have to be adapted if re-used in a more generic function in the
// future
static int do_parse(const char *number_ptr, bool is_negative, const char *base,
    size_t base_width)
{
    int result = 0;
    unsigned char current_digit;

    while (true) {
        if (!my_find_digit_from_base(number_ptr++, base, &current_digit))
            break;
        if (is_about_to_overflow(result, current_digit, base_width))
            return (0);
        result *= (int)base_width;
        result -= current_digit;
    }
    return (handle_positive_negative_for_do_parse(result, is_negative));
}

int my_getnbr_base(const char *number_ptr, const char *base)
{
    bool is_negative;

    find_number(&number_ptr, &is_negative);
    return (do_parse(number_ptr, is_negative, base, my_strlen(base)));
}
