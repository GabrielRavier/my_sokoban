/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_decimal_float
*/

#include "my/internal/printf/formatter.h"
#include "my/string.h"
#include "my/math.h"
#include "my/ctype.h"

static void handle_0(struct my_string *destination, uint64_t as_int,
    struct my_printf_conversion_info *format_info)
{
    int i = 0;

    format_info->precision = (format_info->precision == 0) ? 1 :
        format_info->precision + 2;
    if ((int64_t)as_int < 0) {
        my_string_append_char(destination, '-');
        ++i;
        ++format_info->precision;
    }
    while (i++ < format_info->precision)
        my_string_append_char(destination, '0');
    destination->string[destination->length - i +
        (destination->string[destination->length - i] == '0' ? 1 : 2)] = '.';
}

static void actually_do_format(struct my_string *destination, double to_print,
    struct my_printf_conversion_info *format_info)
{
    union {
        uint64_t as_int;
        double as_double;
    } u = { .as_double = to_print };
    int64_t exponent_base2 = ((u.as_int >> 52) & ((1 << 11) - 1)) - 1023;
    int64_t exponent_base10 = 1 + (int64_t)(exponent_base2
        * 0.30102999566398119802);

    if (to_print == 0.0) {
        handle_0(destination, u.as_int, format_info);
        return;
    }
}

// https://legacy.cs.indiana.edu/~dyb/pubs/FP-Printing-PLDI96.pdf
void asprintf_format_decimal_float(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    double double_argument = va_arg(arguments, double);
    const char *to_append;

    if (format_info->precision < 0)
        format_info->precision = 6;
    if (my_isinf(double_argument)) {
        to_append = (double_argument < 0) ?
            (my_isupper(format_info->conversion_specifier) ? "-INF" : "-inf") :
            (my_isupper(format_info->conversion_specifier) ? "INF" : "inf");
        my_string_append(destination, to_append, my_strlen(to_append));
        return;
    }
    if (my_isnan(double_argument)) {
        my_string_append(destination,
            my_isupper(format_info->conversion_specifier) ? "NAN" : "nan", 3);
        return;
    }
    actually_do_format(destination, double_argument, format_info);
}
