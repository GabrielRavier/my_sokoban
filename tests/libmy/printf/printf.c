/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests printf
*/

#define _GNU_SOURCE
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/stdio.h"
#include "my/macros.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>

MY_ATTRIBUTE((format(printf, 1, 2))) static void compare_printfs(const char *format, ...)
{
    cr_redirect_stdout();

    va_list arguments;
    char *result_us, *result_libc;

    va_start(arguments, format);
    my_vprintf(format, arguments);
    va_end(arguments);

    va_start(arguments, format);
    my_vasprintf(&result_us, format, arguments);
    va_end(arguments);

    va_start(arguments, format);
    vasprintf(&result_libc, format, arguments);
    va_end(arguments);

    cr_assert_str_eq(result_us, result_libc);
    cr_assert_stdout_eq_str(result_libc);
}

Test(my_printf, simple_string)
{
    compare_printfs("Hello world");
}

Test(my_printf, format_s)
{
    compare_printfs("%s", "string");
}

Test(my_printf, format_decimal)
{
    compare_printfs("%d %d", 1239, -1239);
}

Test(my_printf, format_integer)
{
    compare_printfs("%i %i", 1239, -1239);
}

Test(my_printf, format_unsigned)
{
    compare_printfs("%u", 1239);
}

Test(my_printf, format_octal)
{
    compare_printfs("%o", 01123);
}

Test(my_printf, format_hex_lowercase)
{
    compare_printfs("%x %x", 0x1234, 0xabcd);
}

Test(my_printf, format_hex_uppercase)
{
    compare_printfs("%X %X", 0x1234, 0xABCD);
}

Test(my_printf, format_precision_string)
{
    const char array[5] = {'a', 'b', 'c', 'n', 'o'};
    compare_printfs("%.*s", 3, array);
}

Test(my_printf, too_many_args)
{
    compare_printfs("%d %d", 123, 456, 789);
}

Test(my_printf, through_int_checks)
{
    const int values[] = {INT_MIN, -17, -1, 0, 1, 17, 4711, 65535, INT_MAX};

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%d", values[i]);
        compare_printfs("%x", values[i]);
        compare_printfs("%X", values[i]);
        compare_printfs("%o", values[i]);
        compare_printfs("%#x", values[i]);
        compare_printfs("%#X", values[i]);
        compare_printfs("%10d", values[i]);
        compare_printfs("%10x", values[i]);
        compare_printfs("%10X", values[i]);
        compare_printfs("%10o", values[i]);
        compare_printfs("%#10x", values[i]);
        compare_printfs("%#10X", values[i]);
        compare_printfs("%#10o", values[i]);
        compare_printfs("%-10d", values[i]);
        compare_printfs("%-10x", values[i]);
        compare_printfs("%-10X", values[i]);
        compare_printfs("%-10o", values[i]);
        compare_printfs("%-#10x", values[i]);
        compare_printfs("%-#10X", values[i]);
        compare_printfs("%-#10o", values[i]);
    }
}

Test(my_printf, format_epitech_extension_capital_s)
{
    cr_redirect_stdout();
    my_printf("%S", "a\002\377b");
    cr_assert_stdout_eq_str("a\\2\\377b");
}

Test(my_printf, format_epitech_extension_b)
{
    cr_redirect_stdout();
    my_printf("%b", 022645);
    cr_assert_stdout_eq_str("10010110100101");
}
