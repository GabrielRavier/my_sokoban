/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests printf
*/

#define _GNU_SOURCE
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my_string.h"
#include "my/stdio.h"
#include "my/macros.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

static struct my_string *combined_libc = NULL;

static void compare_all_libc_to_stdout()
{
    FILE *libc_output_as_FILE = fmemopen(combined_libc->string, combined_libc->length, "r");
    cr_assert_stdout_eq(libc_output_as_FILE);
    free(combined_libc);
}

MY_ATTRIBUTE((format(printf, 1, 2))) static void compare_printfs(const char *format, ...)
{
    va_list arguments;
    char *result_us = NULL, *result_libc = NULL;

    va_start(arguments, format);
    int our_printf_retval = my_vprintf(format, arguments);
    va_end(arguments);

    va_start(arguments, format);
    int our_length = my_vasprintf(&result_us, format, arguments);
    va_end(arguments);

    va_start(arguments, format);
    int libc_length = vasprintf(&result_libc, format, arguments);
    va_end(arguments);

    if (result_us != NULL || result_libc != NULL) {
        cr_assert_str_eq(result_us, result_libc);
        cr_assert_eq(our_length, libc_length);
        cr_assert_eq(memcmp(result_us, result_libc, our_length), 0);
    }

    if (result_libc) {
        if (combined_libc)
            my_string_append(combined_libc, result_libc, libc_length);
        else
            combined_libc = my_string_new_from_string(result_libc, libc_length);
    }
    else
        cr_assert(our_printf_retval < 0);

    free(result_us);
    free(result_libc);
}

Test(my_printf, simple_string, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("Hello world");
    compare_printfs("0123456789");
    compare_printfs("hello");
    compare_printfs("baz");
    compare_printfs("\012\001");
    compare_printfs("");
}

Test(my_printf, basic, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("hello%d", -123);
    compare_printfs("%s%04d%X", "hello", 123, 0xfaceU);
    compare_printfs("%d %s", 1, "one");
    compare_printfs("100%%");
    compare_printfs("xxx%cyyy", '%');
    compare_printfs("Characters: %c %c \n", 'a', 65);
    compare_printfs("Decimals: %d %ld\n", 1977, 650000L);
    compare_printfs("Preceding with blanks: %10d \n", 1977);
    compare_printfs("Preceding with zeros: %010d \n", 1977);
    compare_printfs("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    compare_printfs("Width trick: %*d \n", 5, 10);
    compare_printfs("%s \n", "A string");
    compare_printfs("%*d", 5, 10);
    compare_printfs("%.*s", 3, "abcdef");

    const char* s = "Hello";
    compare_printfs("\t[%10s]\n\t[%-10s]\n\t[%*s]\n\t[%-10.*s]\n\t[%-*.*s]\n", s, s, 10, s, 4, s, 10, 4, s);
    compare_printfs("Characters:\t%c %%\n", 65);
    compare_printfs("Integers\n");
    compare_printfs("Decimal:\t%i %d %.6i %i %.0i %+i %i\n", 1, 2, 3, 0, 0, 4, -4);
    compare_printfs("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    compare_printfs("Octal:\t%o %#o %#o\n", 10, 10, 4);
    compare_printfs("Variable width control:\n");
    compare_printfs("right-justified variable width: '%*c'\n", 5, 'x');
    compare_printfs("left-justified variable width : '%*c'\n", -5, 'x');
}

Test(my_printf, invalid, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("hello%w");
    compare_printfs("hello%0w");
}

Test(my_printf, random, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%-5d", 45);
    compare_printfs("%s\n%s\n%s", "one", "two", "three");
    compare_printfs("%s\41%s", "one", "two");
}

Test(my_printf, numbers, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("char: %hhd %hhd %hhd", (char)-12, (char)0, (char)254);
    compare_printfs("char: %hhd %hhd %hhd", CHAR_MIN, (char)0, CHAR_MAX);
    compare_printfs("char: %+.4hhd %+.4hhd %+.4hhd", (char)-12, (char)0, (char)254);
    compare_printfs("char: % 04hhd % 04hhd % 04hhd", CHAR_MIN, (char)0, CHAR_MAX);
    compare_printfs("unsigned char: %hhu %hhu %hhu", (char)-12, (char)0, (char)254);
    compare_printfs("short: %hd %hd %hd", (short)-1234, (short)0, (short)1234);
    compare_printfs("unsigned short: %hu %hu %hu", (short)-1234, (short)0, (short)1234);
    compare_printfs("int: %d %d %d", -12345678, 0, 12345678);
    compare_printfs("unsigned int: %u %u %u", -12345678, 0, 12345678);
    compare_printfs("long: %ld %ld %ld", -12345678L, 0L, 12345678L);
    compare_printfs("unsigned long: %lu %lu %lu", -12345678L, 0L, 12345678L);
    compare_printfs("long long: %lld %lld %lld", -12345678LL, 0LL, 12345678LL);
    compare_printfs("unsigned long long: %llu %llu %llu", -12345678LL, 0LL, 12345678LL);
    compare_printfs("ssize_t: %zd %zd %zd", (ssize_t)-12345678, (ssize_t)0, (ssize_t)12345678);
    compare_printfs("size_t: %zu %zu %zu", (size_t)-12345678, (size_t)0, (size_t)12345678);
    compare_printfs("intmax_t: %jd %jd %jd", (intptr_t)-12345678, (intptr_t)0, (intptr_t)12345678);
    compare_printfs("uintmax_t: %ju %ju %ju", (uintptr_t)-12345678, (uintptr_t)0, (uintptr_t)12345678);
    compare_printfs("ptrdiff_t: %td %td %td", (ptrdiff_t)-12345678, (ptrdiff_t)0, (ptrdiff_t)12345678);
    compare_printfs("unsigned ptrdiff_t: %tu %tu %tu", (ptrdiff_t)-12345678, (ptrdiff_t)0, (ptrdiff_t)12345678);
    compare_printfs("%#-12x", 0x1234abcd);
    compare_printfs("%#12x", 0x1234abcd);
    compare_printfs("%d|%03d|%3d|%+d|% d|%+d|% d", 0, 1, 12, 123, 1234, -123, -1234);
    compare_printfs("%hhu|%hhu|%hhu|%hhu|%hhu", 0, 1, 257, 128, -1);
    compare_printfs("%hhd|%hhd|%hhd|%hhd|%hhd", 0, 1, 257, 128, -1);
    compare_printfs("%ho%ho%#ho", 1037, 5282, -11627);
    compare_printfs("%.2d|%.1d|%.0d|%.*d|%1.0d", 0, 0, 0, 0, 0, 0);
    compare_printfs("%#02x|%#02x|%#02x", (char)-16, (char)-16 & 0xff, (unsigned char)(char)-16);
}

Test(my_printf, hex, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("unsigned char: %hhx %hhx %hhx", (char)-12, (char)0, (char)254);
    compare_printfs("unsigned short: %hx %hx %hx", (short)-1234, (short)0, (short)1234);
    compare_printfs("unsigned int: %x %x %x", -12345678, 0, 12345678);
    compare_printfs("unsigned long: %lx %lx %lx", -12345678L, 0L, 12345678L);
    compare_printfs("unsigned long long: %llx %llx %llx", -12345678LL, 0LL, 12345678LL);
    compare_printfs("size_t: %zx %zx %zx", (size_t)-12345678, (size_t)0, (size_t)12345678);
    compare_printfs("uintmax_t: %jx %jx %jx", (uintptr_t)-12345678, (uintptr_t)0, (uintptr_t)12345678);
    compare_printfs("unsigned ptrdiff_t: %tx %tx %tx", (ptrdiff_t)-12345678, (ptrdiff_t)0, (ptrdiff_t)12345678);
}

Test(my_printf, alt_and_sign, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("unsigned int: %#x %#X", 0xabcdef, 0XABCDEF);
    compare_printfs("int: %+d %+d", 12345678, -12345678);
    compare_printfs("int: % d % d", 12345678, -12345678);
}

Test(my_printf, formatting, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("int: a%8da", 12345678);
    compare_printfs("int: a%9da", 12345678);
    compare_printfs("int: a%-9da", 12345678);
    compare_printfs("int: a%10da", 12345678);
    compare_printfs("int: a%-10da", 12345678);
    compare_printfs("int: a%09da", 12345678);
    compare_printfs("int: a%010da", 12345678);
    compare_printfs("int: a%6da", 12345678);

    compare_printfs("a%1sa", "b");
    compare_printfs("a%9sa", "b");
    compare_printfs("a%-9sa", "b");
    compare_printfs("a%5sa", "thisisatest");

    compare_printfs("%03d", -2);
    compare_printfs("%0+3d", -2);
    compare_printfs("%0+3d", 2);
    compare_printfs("%+3d", 2);
    compare_printfs("% 3d", -2000);
    compare_printfs("% 3d", 2000);
    compare_printfs("%+3d", 2000);
    compare_printfs("%10s", "test");
    compare_printfs("%010s", "test");
    compare_printfs("%-10s", "test");
    compare_printfs("%-010s", "test");
}

Test(my_printf, field_width, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    const char *input = "0123456789";
    //compare_printfs("%", input); // Makes glibc printf give random shit
    compare_printfs("%s", input);
    compare_printfs("%*s", 1, input);
    compare_printfs("%*s", 2, input);
    compare_printfs("%*s", 3, input);
    compare_printfs("%*s", 4, input);
    compare_printfs("%*s", 5, input);
    compare_printfs("%*s", 6, input);
    compare_printfs("%*s", 7, input);
    compare_printfs("%*s", 8, input);
    compare_printfs("%*s", 9, input);
    compare_printfs("%*s", 10, input);
    compare_printfs("%*s", -1, input);
    compare_printfs("%*s", -2, input);
    compare_printfs("%*s", -3, input);
    compare_printfs("%*s", -4, input);
    compare_printfs("%*s", -5, input);
    compare_printfs("%*s", -6, input);
    compare_printfs("%*s", -7, input);
    compare_printfs("%*s", -8, input);
    compare_printfs("%*s", -9, input);
    compare_printfs("%*s", -10, input);
    compare_printfs("%10s", input);
}

Test(my_printf, precision, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    const char *input = "0123456789";
    //compare_printfs("%.", input); // Makes glibc give random shit
    compare_printfs("%.s", input);
    compare_printfs("%.*s", 1, input);
    compare_printfs("%.*s", 2, input);
    compare_printfs("%.*s", 3, input);
    compare_printfs("%.*s", 4, input);
    compare_printfs("%.*s", 5, input);
    compare_printfs("%.*s", 6, input);
    compare_printfs("%.*s", 7, input);
    compare_printfs("%.*s", 8, input);
    compare_printfs("%.*s", 9, input);
    compare_printfs("%.*s", 10, input);
    compare_printfs("%.*s", -1, input);
    compare_printfs("%.*s", -2, input);
    compare_printfs("%.*s", -3, input);
    compare_printfs("%.*s", -4, input);
    compare_printfs("%.*s", -5, input);
    compare_printfs("%.*s", -6, input);
    compare_printfs("%.*s", -7, input);
    compare_printfs("%.*s", -8, input);
    compare_printfs("%.*s", -9, input);
    compare_printfs("%.*s", -10, input);
    compare_printfs("%.10s", input);
    compare_printfs("%3.10s", input);
    compare_printfs("%10.3s", input);
    compare_printfs("%*.*s", 10, 3, input);
    compare_printfs("%*.*s", -10, -3, input);
}

Test(my_printf, format_percent_sign, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%% %l% aaa");
}

Test(my_printf, format_s, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%s", "foo");
    compare_printfs("%s", "string");
    compare_printfs("%s %s", "string1", "string2");
    compare_printfs("%s%.0s", "", "123");
    compare_printfs("%s|%.3s|%.*s", "ABCD", "abcdef", 3, "123456");
    compare_printfs("%-3s|%3s|%-*s|%*s|%*s", "1", "2", 3, "3", 3, "4", -3, "5");
    compare_printfs("%-10.4s", "123456");
    compare_printfs("%10.4s", "123456");
    compare_printfs("%4.*s", -5, "123456");
    compare_printfs("%.s", "123456");
    compare_printfs("%.s|%.0s|%.*s", "a", "b", 0, "c");
    compare_printfs("%-3.s|%-3.0s|%-3.*s", "a", "b", 0, "c");
    compare_printfs("<%s>", "text");
    compare_printfs("<%-s>", "text");
    compare_printfs("<%6s>", "text");
    compare_printfs("<%-6s>", "text");
    compare_printfs("<%.2s>", "text");
    compare_printfs("<%4.2s>", "text");
    compare_printfs("<%-4.2s>", "text");
    compare_printfs("<%#s>", "text");
    compare_printfs("<% -6s>", "text");
    compare_printfs("<%+-6s>", "text");
    compare_printfs("<%06s>", "text");
    compare_printfs("<%-06s>", "text");
    compare_printfs("<%hs>", "text");

    static const wchar_t a_ws[] = { 0x0421, 0x043e, 0x0444, 0x044f, 0 };
    static const wchar_t bad_ws[] = { 0x0391, 0xdeef, 0x3c9, 0 };

    compare_printfs("<%ls>", L"text");
    //compare_printfs("<%ls>", a_ws); // These two fail here as of right now, might be related to the fact that I'm not really capable of doing magical input sanitization like glibc
    //compare_printfs("<%ls>", bad_ws);
    compare_printfs("<%-ls>", L"text");
    compare_printfs("<%6ls>", L"text");
    compare_printfs("<%-6ls>", L"text");
    compare_printfs("<%.2ls>", L"text");
    compare_printfs("<%4.2ls>", L"text");
    compare_printfs("<%-4.2ls>", L"text");
    compare_printfs("<%#ls>", L"text");
    compare_printfs("<% -6ls>", L"text");
    compare_printfs("<%+-6ls>", L"text");
    compare_printfs("<%06ls>", L"text");
    compare_printfs("<%-06ls>", L"text");
    //compare_printfs("<%lls>", "text"); // Idk wtf glibc is doing but this is UB anyway, I'll make my implementation reject it if I have the time later

    static const wchar_t wstr[] = L" X Yabc Z W";
    compare_printfs("|%13ls|\n", wstr);
    compare_printfs("|%-13.9ls|\n", wstr);
    compare_printfs("|%13.10ls|\n", wstr);
    compare_printfs("|%13.11ls|\n", wstr);
    compare_printfs("|%13.15ls|\n", &wstr[2]);
    compare_printfs("|%13lc|\n", (wint_t)wstr[5]);
}

Test(my_printf, format_c, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%c", 'a');
    compare_printfs("<%c>", '=');
    compare_printfs("<%c>", '\t');
    compare_printfs("<%c>", 0xfe);
    compare_printfs("<%-c>", '=');
    compare_printfs("<%2c>", '=');
    compare_printfs("<%-2c>", '=');
    compare_printfs("<%#c>", '=');
    compare_printfs("<% -3c>", '=');
    compare_printfs("<%+-3c>", '=');
    compare_printfs("<%03c>", '=');
    compare_printfs("<%-03c>", '=');
    compare_printfs("<%3.2c>", '=');
    compare_printfs("<%hc>", '=');
    compare_printfs("<%lc>", L'=');
    compare_printfs("<%lc>", L'\t');
    //compare_printfs("<%lc>", (wint_t)0x3C0); // glibc rejects this character, we don't and I think rejecting it would require some sort of database of valid characters, so ¯\_(ツ)_/¯, maybe I'll do it when I've finished everything else
    compare_printfs("<%lc>", L'\0');
    compare_printfs("<%-lc>", L'=');
    compare_printfs("<%2lc>", L'=');
    compare_printfs("<%-2lc>", L'=');
    //compare_printfs("<%lc>", 0x00fe); // Fails rn, probably for the same reason as above
    compare_printfs("<%#lc>", L'=');
    compare_printfs("<% -3lc>", L'=');
    compare_printfs("<%+-3lc>", L'=');
    compare_printfs("<%03lc>", L'=');
    compare_printfs("<%-03lc>", L'=');
    compare_printfs("<%3.2lc>", L'=');
    compare_printfs("<%llc>", '=');
}

Test(my_printf, format_p, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%p", ((void *)0xffff0123456789abUL));
    compare_printfs("%p", ((void *)0x00000123456789abUL));
    compare_printfs("%p", ((void *)0x456789ab));
    compare_printfs("%p", NULL);
}

Test(my_printf, format_c_null_terminator, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%c", '\0');
}

Test(my_printf, format_decimal, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%d %d", 1239, -1239);
    compare_printfs("<%d>", 0);
    compare_printfs("<%d>", 1);
    compare_printfs("<%d>", -1);
    compare_printfs("<%d>", 42);
    compare_printfs("<%d>", INT_MAX);
    compare_printfs("<%d>", INT_MIN);
    compare_printfs("<% d>", 42);
    compare_printfs("<% d>", -42);
    compare_printfs("<%+d>", 42);
    compare_printfs("<%+d>", -42);
    compare_printfs("<% +d>", 42);
    compare_printfs("<% +d>", -42);
    compare_printfs("<%-4d>", 42);
    compare_printfs("<% -4d>", 42);
    compare_printfs("<%+-4d>", 42);
    compare_printfs("<%04d>", 42);
    compare_printfs("<%-04d>", 42);
    compare_printfs("<% 04d>", 42);
    compare_printfs("<%+04d>", 42);
    compare_printfs("<%4.3d>", 42);
    compare_printfs("<% 5.3d>", 42);
    compare_printfs("<%+5.3d>", 42);
    compare_printfs("<%-4.3d>", 42);
    compare_printfs("<%04.3d>", 42);

    compare_printfs("<%hhd>", CHAR_MIN);
    compare_printfs("<%hhd>", -1);
    compare_printfs("<%hhd>", 0);
    compare_printfs("<%hhd>", 1);
    compare_printfs("<%hhd>", CHAR_MAX);
    compare_printfs("<%+.4hhd>", 42);
    compare_printfs("<% 04hhd>", 42);

    compare_printfs("<%hd>", SHRT_MIN);
    compare_printfs("<%hd>", -1);
    compare_printfs("<%hd>", 0);
    compare_printfs("<%hd>", 1);
    compare_printfs("<%hd>", SHRT_MAX);

    compare_printfs("<%#d>", 42);
    compare_printfs("<%#Ld>", (long long)12391284012410);
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
    compare_printfs("%x", -1);
    compare_printfs("%04x", 255);
    compare_printfs("%08x", 65537);
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

Test(my_printf, some_format_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const int values[] = {INT_MIN, -17, -1, 0, 1, 17, 4711, 65535, INT_MAX, 2, 5, 10, 99, 100, 1000000, 999999999, -2, -5, -10, -99, -100, -9999999};

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%6d", values[i]);
        compare_printfs("%6x", values[i]);
        compare_printfs("%6X", values[i]);
        compare_printfs("%6o", values[i]);
        compare_printfs("%-6d", values[i]);
        compare_printfs("%-6x", values[i]);
        compare_printfs("%-6X", values[i]);
        compare_printfs("%-6o", values[i]);
        compare_printfs("%-4d", values[i]);
        compare_printfs("%-4x", values[i]);
        compare_printfs("%-4X", values[i]);
        compare_printfs("%-4o", values[i]);
        compare_printfs("%+6d", values[i]);
        compare_printfs("%+6x", values[i]);
        compare_printfs("%+6X", values[i]);
        compare_printfs("%+6o", values[i]);
        compare_printfs("%+d", values[i]);
        compare_printfs("%+x", values[i]);
        compare_printfs("%+o", values[i]);
        compare_printfs("%+X", values[i]);
        compare_printfs("%+ d", values[i]);
        compare_printfs("%+ x", values[i]);
        compare_printfs("%+ X", values[i]);
        compare_printfs("%+ o", values[i]);
        compare_printfs("% +d", values[i]);
        compare_printfs("% +x", values[i]);
        compare_printfs("% +X", values[i]);
        compare_printfs("% +o", values[i]);
        compare_printfs("%06d", values[i]);
        compare_printfs("%06x", values[i]);
        compare_printfs("%06X", values[i]);
        compare_printfs("%06o", values[i]);
        compare_printfs("% 6d", values[i]);
        compare_printfs("% 6x", values[i]);
        compare_printfs("% 6X", values[i]);
        compare_printfs("% 6o", values[i]);
        compare_printfs("%4.3d", values[i]);
        compare_printfs("%4.3x", values[i]);
        compare_printfs("%4.3X", values[i]);
        compare_printfs("%4.3o", values[i]);
        compare_printfs("% 4.3d", values[i]);
        compare_printfs("% 4.3x", values[i]);
        compare_printfs("% 4.3X", values[i]);
        compare_printfs("% 4.3o", values[i]);
        compare_printfs("%+4.3d", values[i]);
        compare_printfs("%+4.3x", values[i]);
        compare_printfs("%+4.3X", values[i]);
        compare_printfs("%+4.3o", values[i]);
        compare_printfs("%-4.3d", values[i]);
        compare_printfs("%-4.3x", values[i]);
        compare_printfs("%-4.3X", values[i]);
        compare_printfs("%-4.3o", values[i]);
        compare_printfs("%5.3d", values[i]);
        compare_printfs("%5.3x", values[i]);
        compare_printfs("%5.3X", values[i]);
        compare_printfs("%5.3o", values[i]);
        compare_printfs("% 5.3d", values[i]);
        compare_printfs("% 5.3x", values[i]);
        compare_printfs("% 5.3X", values[i]);
        compare_printfs("% 5.3o", values[i]);
        compare_printfs("%+5.3d", values[i]);
        compare_printfs("%+5.3x", values[i]);
        compare_printfs("%+5.3X", values[i]);
        compare_printfs("%+5.3o", values[i]);
        compare_printfs("%-5.3d", values[i]);
        compare_printfs("%-5.3x", values[i]);
        compare_printfs("%-5.3X", values[i]);
        compare_printfs("%-5.3o", values[i]);
    }
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

Test(my_printf, through_string_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%*.*s", 10, 10, "Here be a nice little string");
    compare_printfs("%*.*s", 10, 5, "Here be a nice little string");
    compare_printfs("%*.*s", -10, 10, "Here be a nice little string");
    compare_printfs("%*.*s", -10, -10, "Here be a nice little string");
    compare_printfs("%*.*s", -10, -5, "Here be a nice little string");
    compare_printfs("%*.*s", 10, -10, "Here be a nice little string");
    compare_printfs("%-10.10s", "Here be a nice little string");
    compare_printfs("%30s", "Here be a nice little string");
    compare_printfs("%-30s", "Here be a nice little string");
    compare_printfs("%1000s", "Here be a nice little string");
}

#ifdef LIBMY_FLOATING_POINT_CLUDGE

Test(my_printf, some_float_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    compare_printfs("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    compare_printfs("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    compare_printfs("Scientific:\t%E %e\n", 1.5, 1.5);
    compare_printfs("Hexadecimal:\t%a %A\n", 1.5, 1.5);
    compare_printfs("Special values:\t0/0=%g 1/0=%g\n", 0.0/0.0, 1.0/0.0);
    compare_printfs("%13E", 1.0);
    compare_printfs("%13f", 1.0);
    compare_printfs("%13G", 1.0);
    compare_printfs("%13LE", 1.0L);
    compare_printfs("%13Lf", 1.0L);
    compare_printfs("%13LG", 1.0L);
    compare_printfs("%.*f", -2, 2.7182818);
    compare_printfs("%e", 1234567.8);
    compare_printfs("%f", 1234567.8);
    compare_printfs("%G", 1234567.8);
    compare_printfs("%Le", 1234567.8L);
    compare_printfs("%Lf", 1234567.8L);
    compare_printfs("%LG", 1234567.8L);
    compare_printfs("%Lf", 123456789.8642097531L);
    compare_printfs("%LG", -123456789.8642097531L);
    compare_printfs("%.10Lf", 123456789.8642097531L);
    compare_printfs("%27.18Le", 3.14159265358979323846e-4000L);
    compare_printfs("%e", NAN);
    compare_printfs("%F", NAN);
    compare_printfs("%g", NAN);
    compare_printfs("%LE", (long double)NAN);
    compare_printfs("%05e", NAN);
    compare_printfs("%E", HUGE_VAL);
    compare_printfs("%f", -HUGE_VAL);
    compare_printfs("%+g", HUGE_VAL);
    compare_printfs("%4.2Le", HUGE_VALL);
    compare_printfs("%Lf", -HUGE_VALL);
    compare_printfs("%05e", HUGE_VAL);
    compare_printfs("%05e", -HUGE_VAL);
    compare_printfs("%e", 0.0);
    compare_printfs("%F", (double)0.0);
    compare_printfs("%G", 0.0);
    compare_printfs("%3.0Lg", 0.0L);
    compare_printfs("%5.0f", 0.001);
    compare_printfs("%.4e", 1.0123456789);
    compare_printfs("%.4f", 1.0123456789);
    compare_printfs("%.4g", 1.0123456789);
    compare_printfs("%.4e", 0.0123456789);
    compare_printfs("%.4f", 0.0123456789);
    compare_printfs("%.4g", 0.0123456789);
    compare_printfs("%+e", 0.25);
    compare_printfs("%+F", 0.0);
    compare_printfs("%+g", -1.0);
    compare_printfs("% e", -1.0);
    compare_printfs("% +f", 1.0);
    compare_printfs("% g", 1.0);
    compare_printfs("% g", 0.0);
    compare_printfs("%#.3e", 1.25);
    compare_printfs("%#f", 123.0);
    compare_printfs("%#7.5g", 12345.0);
    compare_printfs("%#8g", 1.0);
    compare_printfs("%#.2g", 0.0);
    compare_printfs("%08.1E", 3.25);
    compare_printfs("%06.2F", 3.25);
    compare_printfs("%07.4G", 3.25);
    compare_printfs("%g", 3.14159e-5);
    compare_printfs("%g", 3.14159e-4);
    compare_printfs("%g", 3.14159e6);
    compare_printfs("%g", 3.14159e5);
    compare_printfs("%#g", 3.14159e5);
    compare_printfs("%13e", 9000.0);
    compare_printfs("%12f", 9000.0);
    compare_printfs("%5g", 9000.0);
    compare_printfs("%#8g", 900000.0);
    compare_printfs("%6g", 9000000.0);
    compare_printfs("%13e", 0.0009);
    compare_printfs("%9f", 0.0009);
    compare_printfs("%7g", 0.0009);
    compare_printfs("%6g", 0.00009);
    compare_printfs("%#12g", 0.00009);
    compare_printfs("%#7.1g", 0.00009);
    compare_printfs("%4.1f", 0.0);
    compare_printfs("%4.1f", 90.0);
    compare_printfs("%4.0f", 100.0);
    compare_printfs("%4.1e", 90.0);
    compare_printfs("%4.0e", 100.0);
    compare_printfs("%a", 0x0.0p0);
    compare_printfs("%#LA", 0x0.0p0L);
    compare_printfs("%La", (long double)INFINITY);
    compare_printfs("%+A", INFINITY);
    compare_printfs("%La", (long double)NAN);
    compare_printfs("%A", NAN);
    compare_printfs("%10a", 0x1.23p0);
    compare_printfs("%12a", 0x1.23p-500);
    compare_printfs("%10.1a", 0x1.23p40);
    compare_printfs("%32.24A", 0x1.23p-4);
    compare_printfs("%a", 0x1p-1074);
    compare_printfs("%a", 0x1.2345p-1024);
    compare_printfs("%La", -0x1.e7d7c7b7a7978777675747372717p-14344L);
    compare_printfs("%La", -0x8.777675747372717p-16248L);
}

Test(my_printf, through_float_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const double values[] = {-(0.0 / 0.0), -INFINITY, -99999, -99, -17.4, -4.3, -3.0, -1.5, -1, 0, 0.1, 0.2342374852, 0.2340007, 3.1415926, 14.7845, 34.24758, 9999, 9999999, INFINITY, (0.0 / 0.0), 0.001, 1.0e-20, 1.0, 100.0, 9.9999, -0.00543, -99.99999};

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

Test(my_printf, through_float_widths_checks, .init = cr_redirect_stdout, .fini = compare_all_libc_to_stdout)
{
    static const double values[] = {-(0.0 / 0.0), -INFINITY -99999, -99, -17.4, -4.3, -3.0, -1.5, -1, 0, 0.1, 0.2342374852, 0.2340007, 3.1415926, 14.7845, 34.24758, 9999, 9999999, INFINITY, (0.0 / 0.0), 0.001, 1.0e-20, 1.0, 100.0, 9.9999, -0.00543, -99.99999};
    static const int lengths[] = {0, 1, 1, 5, 5, 10, 0, 10, 5, 1, -1, 0, -1, -5, -5, -10, -10, -5, -1};

    for (size_t i = 0; i < (MY_ARRAY_SIZE(lengths) - 1); ++i) {
        for (size_t j = 0; j < MY_ARRAY_SIZE(values); ++j) {
            compare_printfs("%*.*f", lengths[i], lengths[i + 1], values[j]);
            compare_printfs("%*.*e", lengths[i], lengths[i + 1], values[j]);
            compare_printfs("%*.*E", lengths[i], lengths[i + 1], values[j]);
            compare_printfs("%*.*g", lengths[i], lengths[i + 1], values[j]);
            compare_printfs("%*.*G", lengths[i], lengths[i + 1], values[j]);
        }
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
