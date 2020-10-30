/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests to_string_base
*/

#include "my/bigint.h"
#include <criterion/criterion.h>

static void do_test(const char *string, const char *base)
{
    struct my_bigint *as_bigint = my_bigint_strtol_base_str(string, NULL, base);
    struct my_string *as_string = my_bigint_to_string_base(as_bigint, base);
    cr_assert_str_eq(as_string->string, string);
}

Test(my_bigint_to_string_base, simple_test)
{
    do_test("0", "01");
    do_test("0", "01234567");
    do_test("0", "0123456789");
    do_test("10010000110100111101", "01");
    do_test("132651365214654632", "01234567");
    do_test("31740329187592381543219847328147329843213921839012839012839021839012", "0123456789");
    do_test("3174032918759238154321984732814732984321392183901283901283902183901223482301947389021749830274890231748903217489032174890231748902317489032749083217489032174890321740893217498321", "0123456789");
    do_test("3174032918759238fadfbcadfbcfdacf13267847235632112", "0123456789abcdef");
}
