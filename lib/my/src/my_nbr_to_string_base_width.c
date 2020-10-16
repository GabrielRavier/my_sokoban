/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Converts a number to a string, with base and width
*/

#include "my.h"
#include <stdlib.h>
#include <limits.h>

static const int WORK_BUFFER_SIZE = 1000;

// Converts an unsigned number into a string at buffer_end, going backwards
static char *core_number_converter(unsigned number, char *buffer_end,
    const char *base, size_t base_len)
{
    do {
        *--buffer_end = base[number % base_len];
        number /= base_len;
    } while (number != 0);

    return buffer_end;
}

// Handles concatenating the converted number and whatever amount of 0s we need
// to append to get the specified width
static char *finish_conversion(const char *converted_number_ptr,
    const char *buffer_end, size_t width)
{
    char *result;
    size_t converted_number_size = (size_t)(buffer_end - converted_number_ptr);
    if (converted_number_size > width)
        width = converted_number_size;

    result = (char *)malloc(width + 1);
    my_memset(result, '0', width - converted_number_size);
    my_memcpy(result, converted_number_ptr, converted_number_size);
    result[width] = '\0';

    return result;
}

// We convert the number into a string at a work buffer (we prepend a '-' for
// negative numbers). We can then prepend the padding (since we can determine
// the length of the converted string and whether it will be long enough) before
// returning the converted string from the buffer.
// Note: The buffer is *not* null-terminated
// Note: The conversion to unsigned in the call of core_number_converter will
// deal with INT_MIN : On all standard implementations (since C2x which mandates
// 2's complement) it will be converted to INT_MAX + 1 when converted to
// unsigned (the value of -INT_MIN (non-withstanding the non-representability of
// `-INT_MIN`)) We don't do the negation when we're asked to print INT_MIN
// because that'd be UB, and with wrapping overflow it just ends up being
// INT_MIN again
char *my_nbr_to_string_base_width(int number, const char *base, size_t width)
{
    char buffer[WORK_BUFFER_SIZE];
    char *buffer_end = (buffer + WORK_BUFFER_SIZE);
    char *converted_number_ptr;
    bool is_negative = (number < 0);

    if (is_negative && number != INT_MIN)
        number = -number;

    converted_number_ptr = core_number_converter(
        (unsigned)number, buffer_end, base, my_strlen(base));

    if (is_negative)
        *--converted_number_ptr = '-';

    return finish_conversion(converted_number_ptr, buffer_end, width);
}
