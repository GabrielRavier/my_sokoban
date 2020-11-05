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
#include <stdint.h>
#include <limits.h>

static char *combined_libc = NULL;

static void compare_all_libc_to_stdout()
{
    cr_assert_stdout_eq_str(combined_libc);
    free(combined_libc);
}

MY_ATTRIBUTE((format(printf, 1, 2))) static void compare_printfs(const char *format, ...)
{
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

    if (combined_libc) {
        char *old_combined_libc = combined_libc;
        asprintf(&combined_libc, "%s%s", combined_libc, result_libc);
        free(old_combined_libc);
    }
    else
        asprintf(&combined_libc, "%s", result_libc);

    free(result_us);
    free(result_libc);
}

Test(my_printf, simple_string, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("Hello world");
    compare_printfs("0123456789");
}

Test(my_printf, format_percent_sign, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%% %l% aaa");
}

Test(my_printf, format_s, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%s", "string");
    compare_printfs("%s %s", "string1", "string2");
}

Test(my_printf, format_decimal, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%d %d", 1239, -1239);
}

Test(my_printf, format_integer, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%i %i", 1239, -1239);
}

Test(my_printf, format_unsigned, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%u", 1239);
}

Test(my_printf, format_octal, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%o", 01123);
    compare_printfs("%#.o", 0);
}

Test(my_printf, format_hex_lowercase, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%x %x", 0x1234, 0xabcd);
}

Test(my_printf, format_hex_uppercase, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%X %X", 0x1234, 0xABCD);
}

Test(my_printf, format_precision_string, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const char array[5] = {'a', 'b', 'c', 'n', 'o'};
    compare_printfs("%.*s", 3, array);
}

Test(my_printf, too_many_args, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%d %d", 123, 456, 789);
}

Test(my_printf, through_int_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const int values[] = {INT_MIN, -17, -1, 0, 1, 17, 4711, 65535, INT_MAX};

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
        compare_printfs("%010d", values[i]);
        compare_printfs("%010x", values[i]);
        compare_printfs("%010X", values[i]);
        compare_printfs("%010o", values[i]);
        compare_printfs("%#10x", values[i]);
        compare_printfs("%#10X", values[i]);
        compare_printfs("%#10o", values[i]);
        compare_printfs("%0#10x", values[i]);
        compare_printfs("%0#10X", values[i]);
        compare_printfs("%0#10o", values[i]);
        compare_printfs("%#010x", values[i]);
        compare_printfs("%#010X", values[i]);
        compare_printfs("%#010o", values[i]);
        compare_printfs("%-10d", values[i]);
        compare_printfs("%-10x", values[i]);
        compare_printfs("%-10X", values[i]);
        compare_printfs("%-10o", values[i]);
        compare_printfs("%-#10x", values[i]);
        compare_printfs("%-#10X", values[i]);
        compare_printfs("%-#10o", values[i]);
    }
}

Test(my_printf, through_long_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const long values[] = {LONG_MIN, -17, -1, 0, 1, 17, 4711, 65535, LONG_MAX};

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%ld", values[i]);
        compare_printfs("%lx", values[i]);
        compare_printfs("%lX", values[i]);
        compare_printfs("%lo", values[i]);
        compare_printfs("%#lx", values[i]);
        compare_printfs("%#lX", values[i]);
        compare_printfs("%10ld", values[i]);
        compare_printfs("%10lx", values[i]);
        compare_printfs("%10lX", values[i]);
        compare_printfs("%10lo", values[i]);
        compare_printfs("%#10lx", values[i]);
        compare_printfs("%#10lX", values[i]);
        compare_printfs("%#10lo", values[i]);
        compare_printfs("%-10ld", values[i]);
        compare_printfs("%-10lx", values[i]);
        compare_printfs("%-10lX", values[i]);
        compare_printfs("%-10lo", values[i]);
        compare_printfs("%-#10lx", values[i]);
        compare_printfs("%-#10lX", values[i]);
        compare_printfs("%-#10lo", values[i]);
    }
}

Test(my_printf, through_long_long_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const long long values[] = {LLONG_MIN, LONG_MIN, -17, -1, 0, 1, 17, 4711, 65535, LONG_MAX, LLONG_MAX};

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%lld", values[i]);
        compare_printfs("%llx", values[i]);
        compare_printfs("%llX", values[i]);
        compare_printfs("%llo", values[i]);
        compare_printfs("%#llx", values[i]);
        compare_printfs("%#llX", values[i]);
        compare_printfs("%10lld", values[i]);
        compare_printfs("%10llx", values[i]);
        compare_printfs("%10llX", values[i]);
        compare_printfs("%10llo", values[i]);
        compare_printfs("%#10llx", values[i]);
        compare_printfs("%#10llX", values[i]);
        compare_printfs("%#10llo", values[i]);
        compare_printfs("%-10lld", values[i]);
        compare_printfs("%-10llx", values[i]);
        compare_printfs("%-10llX", values[i]);
        compare_printfs("%-10llo", values[i]);
        compare_printfs("%-#10llx", values[i]);
        compare_printfs("%-#10llX", values[i]);
        compare_printfs("%-#10llo", values[i]);
    }
}

Test(my_printf, through_size_t_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const size_t values[] = {0, 1, 2, 200, SIZE_MAX};

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%zd", values[i]);
        compare_printfs("%zx", values[i]);
        compare_printfs("%zX", values[i]);
        compare_printfs("%zo", values[i]);
        compare_printfs("%#zx", values[i]);
        compare_printfs("%#zX", values[i]);
        compare_printfs("%10zu", values[i]);
        compare_printfs("%10zx", values[i]);
        compare_printfs("%10zX", values[i]);
        compare_printfs("%10zo", values[i]);
        compare_printfs("%#10zx", values[i]);
        compare_printfs("%#10zX", values[i]);
        compare_printfs("%#10zo", values[i]);
        compare_printfs("%-10zu", values[i]);
        compare_printfs("%-10zx", values[i]);
        compare_printfs("%-10zX", values[i]);
        compare_printfs("%-10zo", values[i]);
        compare_printfs("%-#10zx", values[i]);
        compare_printfs("%-#10zX", values[i]);
        compare_printfs("%-#10zo", values[i]);
    }
}

#ifdef LIBMY_FLOATING_POINT_CLUDGE

Test(my_printf, through_float_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const double values[] = { -99999, -99, -17.4, -4.3, -3.0, -1.5, -1, 0, 0.1, 0.2342374852, 0.2340007,
        3.1415926, 14.7845, 34.24758, 9999, 9999999 };

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%f", values[i]);
        compare_printfs("%10f", values[i]);
        compare_printfs("%010f", values[i]);
        compare_printfs("%.2f", values[i]);
        compare_printfs("%.0f", values[i]);
        compare_printfs("%7.0f", values[i]);
        compare_printfs("%5.2f", values[i]);
        compare_printfs("%0f", values[i]);
        compare_printfs("%#f", values[i]);
        compare_printfs("%e", values[i]);
        compare_printfs("%10e", values[i]);
        compare_printfs("%.2e", values[i]);
        compare_printfs("%7.0e", values[i]);
        compare_printfs("%5.2e", values[i]);
        compare_printfs("%0e", values[i]);
        compare_printfs("%#e", values[i]);
        compare_printfs("%E", values[i]);
        compare_printfs("%10E", values[i]);
        compare_printfs("%.2E", values[i]);
        compare_printfs("%7.0E", values[i]);
        compare_printfs("%5.2E", values[i]);
        compare_printfs("%0E", values[i]);
        compare_printfs("%#E", values[i]);
        compare_printfs("%g", values[i]);
        compare_printfs("%10g", values[i]);
        compare_printfs("%.2g", values[i]);
        compare_printfs("%7.0g", values[i]);
        compare_printfs("%5.2g", values[i]);
        compare_printfs("%0g", values[i]);
        compare_printfs("%#g", values[i]);
        compare_printfs("%G", values[i]);
        compare_printfs("%10G", values[i]);
        compare_printfs("%.2G", values[i]);
        compare_printfs("%7.0G", values[i]);
        compare_printfs("%5.2G", values[i]);
        compare_printfs("%0G", values[i]);
        compare_printfs("%#G", values[i]);
    }
}

#endif

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
