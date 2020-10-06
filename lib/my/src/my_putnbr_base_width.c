/*
** EPITECH PROJECT, 2020
** Unix and C Lab Seminar - Day 07
** File description:
** Displays a number in a given base
*/

#include "my.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

// Converts an unsigned number into a string at buffer_end, going backwards
static char *core_number_converter(
    unsigned number, char *buffer_end, const char *base, size_t base_len)
{
    do {
        *--buffer_end = base[number % base_len];
        number /= base_len;
    } while (number != 0);

    return buffer_end;
}

static const int WORK_BUFFER_SIZE = 1000;

// We convert the number into a string at a work buffer (we prepend a '-' for
// negative numbers). We can then print the padding (since we can determine the
// length of the converted string and whether it will be long enough) before
// printing the converted string from the buffer. NOTE: The buffer is *not*
// null-terminated
// Note: The conversion to unsigned in the call of
// core_number_printer will deal with INT_MIN : On all standard implementations
// (since C2x which mandates 2's complement) it will be converted to INT_MAX + 1
// when converted to unsigned (the value of -INT_MIN (non-withstanding the
// non-representability of `-INT_MIN`))
// We don't do the negation when we're asked to print INT_MIN because that'd be
// UB, and with wrapping overflow it just ends up being INT_MIN again
int my_putnbr_base_width(int number, const char *base, int width)
{
    char buffer[WORK_BUFFER_SIZE];
    char *buffer_end = (buffer + WORK_BUFFER_SIZE);
    char *converted_number_ptr;
    bool is_negative = (number < 0);

    if (is_negative && number != INT_MIN)
        number = -number;

    converted_number_ptr =
        core_number_converter(number, buffer_end, base, my_strlen(base));

    if (is_negative)
        *--converted_number_ptr = '-';

    width -= (buffer_end - converted_number_ptr);
    while ((width--) > 0)
        my_putchar('0');

    while (converted_number_ptr != buffer_end)
        my_putchar(*converted_number_ptr++);

    return 0;
}
