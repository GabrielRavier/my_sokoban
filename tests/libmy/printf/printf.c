/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests printf
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/stdio.h"
#include <unistd.h>

static void redirect_stdout(void)
{
    cr_redirect_stdout();
}

Test(my_printf, simple_string, .init = redirect_stdout)
{
    my_printf("Hello world");
    cr_assert_stdout_eq_str("Hello world");
}

Test(my_printf, format_s, .init = redirect_stdout)
{
    my_printf("%s", "string");
    cr_assert_stdout_eq_str("string");
}

Test(my_printf, format_decimal, .init = redirect_stdout)
{
    my_printf("%d", 1239);
    my_printf("%d", -1239);
    cr_assert_stdout_eq_str("1239-1239");
}

Test(my_printf, format_integer, .init = redirect_stdout)
{
    my_printf("%i", 1239);
    my_printf("%i", -1239);
    cr_assert_stdout_eq_str("1239-1239");
}

Test(my_printf, format_unsigned, .init = redirect_stdout)
{
    my_printf("%u", 1239);
    cr_assert_stdout_eq_str("1239");
}

Test(my_printf, format_octal, .init = redirect_stdout)
{
    my_printf("%o", 01123);
    cr_assert_stdout_eq_str("1123");
}

Test(my_printf, format_hex_lowercase, .init = redirect_stdout)
{
    my_printf("%x", 0x1234);
    my_printf("%x", 0xabcd);
    cr_assert_stdout_eq_str("1234abcd");
}

Test(my_printf, format_hex_uppercase, .init = redirect_stdout)
{
    my_printf("%X", 0x1234);
    my_printf("%X", 0xABCD);
    cr_assert_stdout_eq_str("1234ABCD");
}

Test(my_printf, format_epitech_extension_capital_s, .init = redirect_stdout)
{
    my_printf("%S", "a\002\377b");
    cr_assert_stdout_eq_str("a\\2\\377b");
}

Test(my_printf, format_epitech_extension_b, .init = redirect_stdout)
{
    my_printf("%b", 022645);
    cr_assert_stdout_eq_str("10010110100101");
}

Test(my_printf, format_precision_string, .init = redirect_stdout)
{
    const char array[5] = {'a', 'b', 'c', 'n', 'o'};
    my_printf("%.*s", 3, array);
    cr_assert_stdout_eq_str("abc");
}
