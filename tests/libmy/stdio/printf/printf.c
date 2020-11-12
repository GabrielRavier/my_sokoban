/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests printf
*/

#define _GNU_SOURCE
//#define STANDALONE // Define if this doesn't have my/macros.h
//#define NO_MY_VASPRINTF // Define if you don't have my_vasprintf
//#define LIBMY_FLOATING_POINT_CLUDGE // Define if you have implemented floating point
#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "my/stdio.h" // Modify this is this isn't the header that declares my_printf and others
#ifndef STANDALONE
    #include "my/macros.h"
#else
    #define MY_ATTRIBUTE(attr) __attribute__(attr)
    #define MY_ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

// Avoid getting shouted at 2000 times
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wformat"
    #pragma GCC diagnostic ignored "-Wformat-extra-args"
    #pragma GCC diagnostic ignored "-Wformat-zero-length"
    #ifndef __clang__
        #pragma GCC diagnostic ignored "-Wformat-overflow"
    #endif
#endif

// Stores all the output that the libc has given us during the current test
static FILE *libc_string_file = NULL;

// Compares the content of the combined libc output to stdout
static void compare_all_libc_to_stdout(void)
{
    cr_assert_stdout_eq(libc_string_file);
    fclose(libc_string_file);
}

// Redirects stdout and sets the locale to a sane value (useful for wchar_t tests)
static void do_init(void)
{
    cr_redirect_stdout();
    setlocale(LC_ALL, "en_US.utf8");
}

// Compares the output that our printf and the printf of the libc gives for a given format and arguments
MY_ATTRIBUTE((format(printf, 1, 2))) static void compare_printfs(const char *format, ...)
{
    va_list arguments;

    va_start(arguments, format);
    const int our_printf_retval = my_vprintf(format, arguments);
    va_end(arguments);

#ifndef NO_MY_VASPRINTF
    va_start(arguments, format);
    char *result_us = NULL;
    const int our_length = my_vasprintf(&result_us, format, arguments);
    va_end(arguments);
#endif

    va_start(arguments, format);
    char *result_libc = NULL;
    const int libc_length = vasprintf(&result_libc, format, arguments);
    va_end(arguments);

#ifndef NO_MY_VASPRINTF
    if (result_us != NULL || result_libc != NULL) {
        cr_assert_str_eq(result_us, result_libc);
        cr_assert_eq(our_length, libc_length);
        cr_assert_eq(memcmp(result_us, result_libc, our_length), 0);
    }
#endif
    cr_assert_eq(our_printf_retval, libc_length);

    if (result_libc) {
        if (!libc_string_file)
            libc_string_file = tmpfile();
        fwrite(result_libc, libc_length, 1, libc_string_file);
    }
    else
        cr_assert(our_printf_retval < 0);

#ifndef NO_MY_VASPRINTF
    free(result_us);
#endif
    free(result_libc);
}

Test(my_printf, simple_string, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("Hello world");
    compare_printfs("0123456789");
    compare_printfs("hello");
    compare_printfs("baz");
    compare_printfs("\012\001");
    compare_printfs("");
    compare_printfs(".");
    compare_printfs("aa");
}

Test(my_printf, basic, .init = do_init, .fini = compare_all_libc_to_stdout)
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
    compare_printfs("a%db%zdc%ue%zuf%xh%zxq%pe%sr", (int)-1, (uintptr_t)-2, (unsigned)-4, (uintptr_t)5, (unsigned)10, (uintptr_t)11, (void *)0x123, "_string_");
    compare_printfs("%-010d", 10);
    compare_printfs("%-010u", 4294967294);
    compare_printfs("%-0#10x", 2147483647);
    compare_printfs("%010X", 2147483647);
    compare_printfs("%+0#10o", 2147483647);
    compare_printfs("%05i", 2147483647);
    compare_printfs("%010c", 'A');
    compare_printfs("%-010s", "Oui une pomme sur un arbre sa tombe");
    compare_printfs("%020p", (void *)"str");
    compare_printfs("%%");
    compare_printfs("%-11C", L'1');
    compare_printfs("%d %s", 123, "456");
    compare_printfs("%010000d", 0);
    compare_printfs("%d", 12345);
    compare_printfs("%u", 54321);
    compare_printfs("%x", 0xABCD);
    compare_printfs("%o", 0123);
    compare_printfs("%k");
    compare_printfs("%lld", 1LL);
    compare_printfs("%lc", L'c');
    compare_printfs("%ls", L"foo");
    compare_printfs("%*d", 10, 12345);
    compare_printfs("%10.*d", 6, 12345);
    compare_printfs("%*.*d", 10, 6, 12345);
    compare_printfs("%d + %d = %d", 13, 7, 20);
}

Test(my_printf, invalid, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("hello%w");
    compare_printfs("hello%0w");
    compare_printfs("hello%");
    compare_printfs("hello%w%");
    compare_printfs("hello%w%d", 123);
    compare_printfs("hello%w%d%", 123);
    compare_printfs("% #18.2z\n");
    compare_printfs("%#04.2z");
    compare_printfs("%#04.2z\n");
    compare_printfs("%\001");
    compare_printfs("%0- +#w");
    compare_printfs("%0- +#1324.4321w");
    compare_printfs("%01.4321w");
    compare_printfs("%0.4321w");
    compare_printfs("% w");
}

Test(my_prinf, mismatch_length_conversion, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%hhc", 'a');
    compare_printfs("%hc", 'b');
    compare_printfs("%hhs", "foo");
    compare_printfs("%hs", "foo");
}

Test(my_printf, random, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%-5d", 45);
    compare_printfs("%s\n%s\n%s", "one", "two", "three");
    compare_printfs("%s\41%s", "one", "two");
    compare_printfs("%*s%*s%*s", -1, "one", -20, "two", -30, "three");
    compare_printfs("%07Lo", 040000000000ll);
    compare_printfs("printf (\"%%hhu\", %u) = %hhu\n", UCHAR_MAX + 2, UCHAR_MAX + 2);
    compare_printfs("printf (\"%%hu\", %u) = %hu\n", USHRT_MAX + 2, USHRT_MAX + 2);
}

Test(my_printf, numbers, .init = do_init, .fini = compare_all_libc_to_stdout)
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
    compare_printfs("%d-%d", INT_MIN, INT_MAX);
    compare_printfs("%u-%u", 0, UINT_MAX);
    compare_printfs("%x-%x", 0, UINT_MAX);
    compare_printfs("%zd-%zd", (size_t)LONG_MIN, (size_t)LONG_MAX);
    compare_printfs("%zd", (ssize_t)1);
    compare_printfs("%zu-%zu", (size_t)0, (size_t)ULONG_MAX);
    compare_printfs("%zx-%zx", (size_t)0, (size_t)ULONG_MAX);

    //Test support of size specifiers as in C99.
    compare_printfs("%ju %d\n", (uintmax_t) 12345671, 33, 44, 55);
    compare_printfs("%zu %d\n", (size_t) 12345672, 33, 44, 55);
    compare_printfs("%tu %d\n", (ptrdiff_t) 12345673, 33, 44, 55);

    compare_printfs("%i", -9);
    compare_printfs("%u %u %u %u %u %u", 0, 1, 0x7fff, 0x8000, 0x8001, 0xffff);

    compare_printfs("%d%d%d%d%d%d%d%d%d", 0, 1, 2, 3, 4, 5, 6, 7, 8);
    compare_printfs("%d %d %d", 9, 10, 11);
    compare_printfs("%d %d %d", 99, 100, 101);
    compare_printfs("%d %d %d", 999, 1000, 1001);
    compare_printfs("%d %d %d", 9999, 10000, 10001);
    compare_printfs("%ld %ld %ld", 99999L, 100000L, 100001L);
    compare_printfs("%ld %ld %ld", 999999L, 1000000L, 1000001L);
    compare_printfs("%ld %ld %ld", 9999999L, 10000000L, 10000001L);
    compare_printfs("%ld %ld %ld", 99999999L, 100000000L, 100000001L);
    compare_printfs("%ld %ld %ld", 999999999L, 1000000000L, 1000000001L);
    compare_printfs("%lu %lu %lu %lu", 2000000000ul, 3000000000ul, 4000000000ul, 0xffffffff);

    for (unsigned long long b1 = 1; b1; b1 <<= 8) {
        for (unsigned long long b2 = 1; b2; b2 <<= 4) {
            unsigned long long x = b1 | b2;
            compare_printfs("%lld", x);
            compare_printfs("%llu", x);
            compare_printfs("%#llo", x);
            compare_printfs("%#llx", x);
            compare_printfs("%#llX", x);
            x -= 1;
            compare_printfs("%lld", x);
            compare_printfs("%llu", x);
            compare_printfs("%#llo", x);
            compare_printfs("%#llx", x);
            compare_printfs("%#llX", x);
            x = ~(b1 | b2);
            compare_printfs("%lld", x);
            compare_printfs("%llu", x);
            compare_printfs("%#llo", x);
            compare_printfs("%#llx", x);
            compare_printfs("%#llX", x);
            x += 1;
            compare_printfs("%lld", x);
            compare_printfs("%llu", x);
            compare_printfs("%#llo", x);
            compare_printfs("%#llx", x);
            compare_printfs("%#llX", x);
        }
    }

    compare_printfs("bad format:\t\"%w\"\n");
    compare_printfs("nil pointer (padded):\t\"%10p\"\n", (void *) NULL);

    compare_printfs("decimal negative:\t\"%d\"\n", -2345);
    compare_printfs("octal negative:\t\"%o\"\n", -2345);
    compare_printfs("hex negative:\t\"%x\"\n", -2345);
    compare_printfs("long decimal number:\t\"%ld\"\n", -123456L);
    compare_printfs("long octal negative:\t\"%lo\"\n", -2345L);
    compare_printfs("long unsigned decimal number:\t\"%lu\"\n", -123456L);
    compare_printfs("zero-padded LDN:\t\"%010ld\"\n", -123456L);
    compare_printfs("left-adjusted ZLDN:\t\"%-010ld\"\n", -123456L);
    compare_printfs("space-padded LDN:\t\"%10ld\"\n", -123456L);
    compare_printfs("left-adjusted SLDN:\t\"%-10ld\"\n", -123456L);
    compare_printfs("%#03x\n", 1);
}

Test(my_printf, hex, .init = do_init, .fini = compare_all_libc_to_stdout)
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

Test(my_printf, alt_and_sign, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("unsigned int: %#x %#X", 0xabcdef, 0XABCDEF);
    compare_printfs("int: %+d %+d", 12345678, -12345678);
    compare_printfs("int: % d % d", 12345678, -12345678);
    compare_printfs("% +d.%+ d", 10, 11);
}

Test(my_printf, formatting, .init = do_init, .fini = compare_all_libc_to_stdout)
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
    compare_printfs("%3d - %3d", 1, 0);
    compare_printfs("%3d - %3d", -1, 123);
    compare_printfs("%3d - %3d", -1, -123);
    compare_printfs("%3d - %3d", 12, 1234);
    compare_printfs("%3d - %3d", -12, -1234);
    compare_printfs("%03d - %03d", 1, 0);
    compare_printfs("%03d - %03d", -1, 123);
    compare_printfs("%03d - %03d", -1, -123);
    compare_printfs("%03d - %03d", 12, 1234);
    compare_printfs("%03d - %03d", -12, -1234);
    compare_printfs("%.*s%c", 4, "hello world", '!');
    compare_printfs("%.*s%c", INT_MAX/2, "hello world", '!');
    compare_printfs("%.*s%c", INT_MAX-1, "hello world", '!');
    compare_printfs("%.*s%c", INT_MAX, "hello world", '!');
    compare_printfs("%.*s%c", -1, "hello world", '!');
}

Test(my_printf, field_width, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    const char *input = "0123456789";
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
    compare_printfs("a%08xz", 0x123456);
    compare_printfs("a%5dz", 1234);
    compare_printfs("a%05dz", 1234);
    compare_printfs("a%8dz", 1234);
    compare_printfs("a%-8dz", 1234);
    compare_printfs("A%-11sZ", "abcdef");
    compare_printfs("A%s:%dZ", "hello", 1234);
    compare_printfs("a%03d:%d:%02dz", 5, 5, 5);
    compare_printfs("%2147483648s%c", "hello world", '!');
    compare_printfs("%5.s", "xyz");
}

Test(my_printf, precision, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    const char *input = "0123456789";
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
    compare_printfs("%.4000d %d", 1234567, 99);
    compare_printfs("%.*d %d", 4000, 1234567, 99);
    compare_printfs("%.4000d %d", -1234567, 99);
    compare_printfs("%.4000u %d", 1234567, 99);
    compare_printfs("%.4000o %d", 1234567, 99);
    compare_printfs("%.4000x %d", 1234567, 99);
    compare_printfs("%#.4000x %d", 1234567, 99);
    compare_printfs("%.4000s %d", input, 99);
    compare_printfs("%.2147483646s%c", "hello world", '!');
    compare_printfs("%.2147483647s%c", "hello world", '!');
    compare_printfs("%.2147483648s%c", "hello world", '!');
    compare_printfs("%.2147483658s%c", "hello world", '!');
    compare_printfs("%20.10d", 5);
    compare_printfs("%-20.10d", 5);
    compare_printfs("%-#20.10x", 0x1337);
    compare_printfs("%#20.10x", 0x1337);
    compare_printfs("%04.*o", 3, 33);
    compare_printfs("%09.*u", 7, 33);
    compare_printfs("%04.*x", 3, 33);
    compare_printfs("%04.*X", 3, 33);
}

Test(my_printf, format_percent_sign, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%%");
    compare_printfs("%% %l% aaa");
    compare_printfs("%%%% ");
    compare_printfs("%10%");
    compare_printfs("%.10%");
    compare_printfs("%010%");
    compare_printfs("%-10%");
    compare_printfs("%#10%");
    compare_printfs("%+10%");
    compare_printfs("% 10%");
    compare_printfs("% +-#010.10%");
}

Test(my_printf, format_s, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%s", "foo");
    compare_printfs("%s", "abcdef");
    compare_printfs("%s", "string");
    compare_printfs("a%sb", (char *)NULL);
    compare_printfs("a%5sb", (char *)NULL);
    compare_printfs("a%.5sb", (char *)NULL);
    compare_printfs("a%74sb", (char *)NULL);
    compare_printfs("a%.74sb", (char *)NULL);
    compare_printfs("a%1sb", (char *)NULL);
    compare_printfs("Hello%.3sworld", (char *)NULL);
    compare_printfs("a%.1sb", (char *)NULL);
    compare_printfs("a%0sb", (char *)NULL);
    compare_printfs("a%.0sb", (char *)NULL);
    compare_printfs("a%6sb", (char *)NULL);
    compare_printfs("a%.6sb", (char *)NULL);
    compare_printfs("a%7sb", (char *)NULL);
    compare_printfs("a%.7sb", (char *)NULL);
    compare_printfs("<%*.*s>", 2, 2, NULL);
    compare_printfs("<%*.*s>", 2, 8, NULL);
    compare_printfs("<%*.*s>", 8, 2, NULL);
    compare_printfs("<%*.*s>", 8, 8, NULL);
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
    compare_printfs("a%*sc", -3, "b");
    compare_printfs("a%-*sc", 3, "b");
    compare_printfs("a%-*sc", -3, "b");
    compare_printfs("<%s>", "text");
    compare_printfs("<%-s>", "text");
    compare_printfs("<%6s>", "text");
    compare_printfs("<%-6s>", "text");
    compare_printfs("<%.2s>", "text");
    compare_printfs("<%4.2s>", "text");
    compare_printfs("<%-4.2s>", "text");
    compare_printfs(".*s", 3, "12345");
    compare_printfs(".*s", 6, "12345");
    compare_printfs("-6s", "12345");
    compare_printfs("-10s", "12345");
    compare_printfs("<%#s>", "text");
    compare_printfs("<% -6s>", "text");
    compare_printfs("<%+-6s>", "text");
    compare_printfs("<%06s>", "text");
    compare_printfs("<%-06s>", "text");
    compare_printfs("<%hs>", "text");
    compare_printfs("%s", "");
    compare_printfs("%s", "A");
    compare_printfs("%s", "123456789\001\177\200\201\377");
    compare_printfs("%0s %+s %-s % s %#s", "A", "B", "C", "D", "E");
    compare_printfs("%1s.%2s.%5s.%10.2s", "A", "B", "C", "D");
    compare_printfs("%.0s.%.1s.%.10s", "ABCDEF", "abcdef", "0123456789");

    static const wchar_t ws[] = { 0x0421, 0x043e, 0x0444, 0x044f, 0 };

    compare_printfs("<%ls>", L"text");
    compare_printfs("%ls\n", L"Hawaï");
    compare_printfs("%.0ls", L"foo");
    compare_printfs("<%ls>", ws);
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
    compare_printfs("<%lls>", L"text");
    compare_printfs("a%lsb", (wchar_t *)NULL);
    compare_printfs("a%5lsb", (wchar_t *)NULL);
    compare_printfs("a%.5lsb", (wchar_t *)NULL);
    compare_printfs("a%74lsb", (wchar_t *)NULL);
    compare_printfs("a%.74lsb", (wchar_t *)NULL);
    compare_printfs("a%1lsb", (wchar_t *)NULL);
    compare_printfs("a%.1lsb", (wchar_t *)NULL);
    compare_printfs("a%0lsb", (wchar_t *)NULL);
    compare_printfs("a%.0lsb", (wchar_t *)NULL);
    compare_printfs("a%6lsb", (wchar_t *)NULL);
    compare_printfs("a%.6lsb", (wchar_t *)NULL);
    compare_printfs("a%7lsb", (wchar_t *)NULL);
    compare_printfs("a%.7lsb", (wchar_t *)NULL);

    static const wchar_t wstr[] = L" X Yabc Z W";
    compare_printfs("|%13ls|\n", wstr);
    compare_printfs("|%-13.9ls|\n", wstr);
    compare_printfs("|%13.10ls|\n", wstr);
    compare_printfs("|%13.11ls|\n", wstr);
    compare_printfs("|%13.15ls|\n", &wstr[2]);
    compare_printfs("|%13lc|\n", (wint_t)wstr[5]);

    wchar_t wz [3] = L"@@";
    wchar_t wn [3] = L"@@@";
    compare_printfs("%ls", wz);
    compare_printfs("%4ls", wz);
    compare_printfs("%4ls", wn);
    compare_printfs("%9ls", wz);
    compare_printfs("%9ls", wn);
    compare_printfs("%10ls", wz);

    compare_printfs("<%ls>", ws);
    compare_printfs("<%-ls>", ws);
    compare_printfs("<%9ls>", ws);
    compare_printfs("<%-9ls>", ws);
    compare_printfs("<%.4ls>", ws);
    compare_printfs("<%.3ls>", ws);
    compare_printfs("<%6.4ls>", ws);
    compare_printfs("<%3.3ls>", ws);
    compare_printfs("<%-6.4ls>", ws);
    compare_printfs("<%-3.3ls>", ws);
    compare_printfs("%ls", L"{Ȧ嵥YVD󢩯E󚽥ԯd幊.WʄꙄ񪪥􊚽X񟤸죩򴝕,?ӄ󈔏Ɇ򥰢7􄥶ÿoᜫ𸍳膗n𹨛A͊NƐ@$򅳸ʴ򩃣H(ä닛򪾆۝.Ӿƕƣmꟊɏ󺯑R𴾿쌷63貭񉍏񲞴ٶഷ򆮐򭵊򞏠˷GǱ$V󒞔桃f켱Ū𺃨䕭𔌘ɠtߌ򗰺~z󶇫񱕕쇕鎑󌒻󣊯");
}

Test(my_printf, format_c, .init = do_init, .fini = compare_all_libc_to_stdout)
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
    for (int i = (CHAR_MIN - 1000); i < CHAR_MAX + 1000; ++i)
        compare_printfs("%c", i);
    compare_printfs("%c%c%c%c%c", 001, 0177, 0200, 0201, 0377);
    compare_printfs("%0c %+c %-c % c %#c", 'A', 'B', 'C', 'D', 'E');
    compare_printfs("%.c %.0c %.1c %.99c", 'A', 'B', 'C', 'D');
    compare_printfs("%1c.%2c.%5c.%10.2c", 'A', 'B', 'C', 'D', 'E');
    compare_printfs("%-1c.%-2c.%-10c", 'A', 'B', 'C');
    compare_printfs("%255c", 'F');
    compare_printfs("%-255c", 'G');
    compare_printfs("<%lc>", L'=');
    compare_printfs("<%lc>", L'\t');
    compare_printfs("<%lc>", (wint_t)0x3C0);
    compare_printfs("<%lc>", L'\0');
    compare_printfs("<%-lc>", L'=');
    compare_printfs("<%2lc>", L'=');
    compare_printfs("<%-2lc>", L'=');
    compare_printfs("<%lc>", 0x00fe);
    compare_printfs("<%#lc>", L'=');
    compare_printfs("<% -3lc>", L'=');
    compare_printfs("<%+-3lc>", L'=');
    compare_printfs("<%03lc>", L'=');
    compare_printfs("<%-03lc>", L'=');
    compare_printfs("<%3.2lc>", L'=');
    compare_printfs("<%llc>", '=');
    compare_printfs("<%lc>", L'=');
    compare_printfs("<%lc>", L'\t');
    compare_printfs("<%lc>", L'è');
    compare_printfs("<%llc>", L'è');
    compare_printfs("<%lc>", 0x00fe);
    compare_printfs("<%lc>", 0x03c0);
    compare_printfs("<%lc>", 0x123456);
    compare_printfs("<%C>", L'=');
    compare_printfs("<%C>", L'\t');
    compare_printfs("<%C>", L'è');
    compare_printfs("<%C>", L'è');
    compare_printfs("<%C>", 0x00fe);
    compare_printfs("<%C>", 0x03c0);
    compare_printfs("<%C>", 0x123456);
    compare_printfs("<%-lc>", L'=');
    compare_printfs("<%-lc>", 0x03c0);
    compare_printfs("<%2lc>", L'=');
    compare_printfs("<%3lc>", 0x03c0);
    compare_printfs("<%-2lc>", L'=');
    compare_printfs("<%-3lc>", 0x03c0);
    compare_printfs("<%#c>", '=');
    compare_printfs("<% -3c>", '=');
    compare_printfs("<%+-3c>", '=');
    compare_printfs("<%03c>", '=');
    compare_printfs("<%-03c>", '=');
    compare_printfs("<%3.2c>", '=');
    compare_printfs("<%hc>", '=');
    compare_printfs("<%#lc>", 0x03c0);
    compare_printfs("<% -4lc>", 0x03c0);
    compare_printfs("<%+-4lc>", 0x03c0);
    compare_printfs("<%04lc>", 0x03c0);
    compare_printfs("<%-04lc>", 0x03c0);
    compare_printfs("<%4.5lc>", 0x03c0);
    compare_printfs("<%4.3lc>", 0x03c0);
    compare_printfs("<%4.1lc>", 0x03c0);
    compare_printfs("<%llc>", 0xfe);
}

Test(my_printf, format_p, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%p", ((void *)0xffff0123456789abUL));
    compare_printfs("%p", ((void *)0x00000123456789abUL));
    compare_printfs("%p", ((void *)0x456789ab));
    compare_printfs("%p", (void *)NULL);
    compare_printfs("%p %p %p", (void *)1, (void *)0xabcd, (void *)0xef02);
}

Test(my_printf, format_c_null_terminator, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%c", '\0');
}

Test(my_printf, format_decimal, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%d %d", 1239, -1239);
    compare_printfs("%d", -123456789);
    compare_printfs("%d", 137);
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

    for (int i = -100; i < 100; ++i)
        compare_printfs("%d", i);

    compare_printfs("%.3d\n", 42);
    compare_printfs("%.10d\n", 12345);
    compare_printfs("%.1d\n", 0);
    compare_printfs("%.0d\n", 0);
    compare_printfs("%.0d\n", 1);
    compare_printfs("%.0d\n", 123);

    compare_printfs("%d", 0);
    compare_printfs("%d", 12345);
    compare_printfs("%d %d %d %d %d %d", (int)-32768, -32767, -1, 0, 1, 32767);
    compare_printfs("%0d %0d %0d", 0, 1, -1);
    compare_printfs("%+d %+d %+d", 0, 1, -1);
    compare_printfs("%-d %-d %-d", 0, 1, -1);
    compare_printfs("%#d %#d %#d", 0, 1, -1);
    compare_printfs("% d % d % d", 0, 1, -1);
    compare_printfs("%04d.%04d.%04d.%04d.%04d.%04d.%04d", 0, 1, -1, 1234, -123, 12345, -1234);
    compare_printfs("%08.4d", 1);
    compare_printfs("%08.0d", 1);
    compare_printfs("%08.d", 1);
    compare_printfs("%.0d", 0);
    compare_printfs("%.0d %.0d", 1, -1);
    compare_printfs("%.1d %.1d %.1d", 0, 1, -1);
    compare_printfs("%.2d %.2d %.2d", 0, 1, -1);
    compare_printfs("%.4d %.4d %.4d %.4d %.4d %.4d", 0, 1, 12, 123, 1234, 12345);
    compare_printfs("%1d.%1d.%1d", 0, 1, -1);
    compare_printfs("%2d.%2d.%2d", 1, 12, 123);
    compare_printfs("%4d.%4d.%4d.%4d", -1, -12, -123, -1234);
    compare_printfs("%#4d.%#4d", 12, -13);
    compare_printfs("% 4d.% 4d", 14, -15);
    compare_printfs("%+4d.%+4d", 16, -17);
    compare_printfs("%-4d.%-4d", 18, -19);
    compare_printfs("%8.4d.%8.4d.%8.4d.%8.4d", 1, -1, 1234, -1234);
    compare_printfs("%08.4d.%#8.4d.% 8.4d.%+8.4d", 12, 13, 14, 15);
    compare_printfs("%-8.4d.%-8.4d.%-8.4d.%-8.4d", 1, 123, 1234, 12345);
    compare_printfs("%-8.4d.%-8.4d.%-8.4d.%-8.4d", -1, -123, -1234, -12345);
    compare_printfs("%255d", 1);
    compare_printfs("%-255d", 1);
    compare_printfs("%.255d", 2);
    compare_printfs("%ld %ld %ld %ld %ld %ld", 0L, 1L, -1L, 2147483647L, -2147483647L, 0x80000000L);
    compare_printfs("%hd %hd %hd", 0, 2, -2);
    compare_printfs("%hhd", 123);
    compare_printfs("%d", INT_MAX);
    compare_printfs("%d", INT_MIN);
    compare_printfs("%jd", INTMAX_MAX);
    compare_printfs("%jd", INTMAX_MIN);
    compare_printfs("%ju", UINTMAX_MAX);
    compare_printfs("%ju", UINTMAX_MAX);
    compare_printfs("%ld", LONG_MAX);
    compare_printfs("%ld", LONG_MIN);
    compare_printfs("%lld", LLONG_MAX);
    compare_printfs("%lld", LLONG_MIN);
    compare_printfs("%o", UINT_MAX);
    compare_printfs("%u", UINT_MAX);
    compare_printfs("%x", UINT_MAX);
    compare_printfs("%X", UINT_MAX);
    compare_printfs("%dx%d", 1, 2);
    compare_printfs("%d\xc2\xa2%d", 1, 2);
    compare_printfs("%d\xe2\x82\xac%d", 1, 2);
    compare_printfs("%d\xf0\xa4\xad\xa2%d", 1, 2);
}

Test(my_printf, format_integer, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%i %i", 1239, -1239);
}

Test(my_printf, format_unsigned, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%u", 1239);
    for (int i = -100; i < 100; ++i)
        compare_printfs("%u", i);
    for (int i = -100; i < 100; ++i)
        compare_printfs("%08u", i);
}

Test(my_printf, format_octal, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%o", 0);
    compare_printfs("%o", 01123);
    compare_printfs("%o", 0123456);
    compare_printfs("%o", 0x12345678);
    compare_printfs("%#.o", 0);
    compare_printfs("%o %o %o %o %o", 1, 0x7fff, 0x8000, 0x8001, 0xffff);
    compare_printfs("%0o %0o %0o", 0, 1, 0xffff);
    compare_printfs("% o % o % o", 0, 1, 0xffff);
    compare_printfs("%+o %+o %+o", 0, 1, 0xffff);
    compare_printfs("%-o %-o %-o", 0, 1, 0xffff);
    compare_printfs("%#o %#o %#o", 0, 1, 0xffff);
    compare_printfs("%.0o", 0);
    compare_printfs("%.0o %.0o", 1, 0xffff);
    compare_printfs("%.1o %.1o %.1o", 0, 1, 0xffff);
    compare_printfs("%.2o %.2o %.2o %.2o", 0, 1, 8, 0xffff);
    compare_printfs("%.4o %.4o %.4o %.4o %.4o %.4o", 0, 1, 012, 0123, 01234, 012345);
    compare_printfs("%1o.%1o.%1o", 0, 1, 0xffff);
    compare_printfs("%2o.%2o.%2o", 1, 012, 0123);
    compare_printfs("%4o.%4o.%4o.%4o.%4o", 1, 012, 0123, 01234, 012345);
    compare_printfs("%#4o.%#4o.%#4o", 012, 0123, 01234);
    compare_printfs("% 4o.% 4o", 014, 0xffff);
    compare_printfs("%+4o.%+4o", 016, 0xffff);
    compare_printfs("%-4o.%-4o", 017, 0xffff);
    compare_printfs("%04o.%04o.%04o.%04o.%04o.%04o.%04o", 0, 1, 012, 0123, 01234, 012345, 0177777);
    compare_printfs("%08.4o", 1);
    compare_printfs("%08.0o", 1);
    compare_printfs("%08.o", 1);
    compare_printfs("%8.4o.%8.4o.%8.4o.%8.4o", 1, 0123, 01234, 0xffff);
    compare_printfs("%08.4o.% 8.4o.%+8.4o", 012, 013, 014);
    compare_printfs("%-8.4o.%-8.4o.%-8.4o.%-8.4o", 1, 0123, 01234, 012345);
    compare_printfs("%#8.4o.%#8.4o.%#8.4o.%#8.4o.%#8.4o", 0, 1, 012, 0123, 01234);
    compare_printfs("%255o", 1);
    compare_printfs("%-255o", 1);
    compare_printfs("%.255o", 2);
    compare_printfs("%lo %lo %lo %lo %lo %lo %lo", 0L, 01234567L, 076543210L, 0x7fffffffL, 0x80000000L, 0x80000001L, 0xffffffffL);
    compare_printfs("%ho %ho %ho", 0, 2, 0xfffe);
    compare_printfs("%o", 1);
    compare_printfs("%#o", 1);
}

Test(my_printf, format_hex_lowercase, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%x %x", 0x1234, 0xabcd);
    compare_printfs("%x", -1);
    compare_printfs("%04x", 255);
    compare_printfs("%08x", 65537);
    for (int i = -100; i < 100; ++i) {
        compare_printfs("%x", i);
        compare_printfs("%04x", i);
        compare_printfs("%08x", i);
    }
    compare_printfs("%0x %0x %0x", 0, 1, 0xffff);
    compare_printfs("% x % x % x", 0, 1, 0xffff);
    compare_printfs("%+x %+x %+x", 0, 1, 0xffff);
    compare_printfs("%-x %-x %-x", 0, 1, 0xffff);
    compare_printfs("%#x %#x %#x", 0, 1, 0xffff);
    compare_printfs("%.0x", 0);
    compare_printfs("%.0x %.0x", 1, 0xffff);
    compare_printfs("%.1x %.1x %.1x", 0, 1, 0xffff);
    compare_printfs("%.2x %.2x %.2x %.2x", 0, 1, 255, 0xffff);
    compare_printfs("%.3x %.3x %.3x %.3x %.3x", 0, 1, 0x12, 0x123, 0x1234);
    compare_printfs("%1x.%1x.%1x", 0, 1, 0xffff);
    compare_printfs("%2x.%2x.%2x", 1, 0x12, 0x123);
    compare_printfs("%3x.%3x.%3x.%3x", 1, 0x12, 0x123, 0x1234);
    compare_printfs("%#4x.%#4x.%#4x.%#4x.%#4x", 0, 1, 0x12, 0x123, 0x1234);
    compare_printfs("% 4x.% 4x", 0x14, 0xffff);
    compare_printfs("%+4x.%+4x", 0x16, 0xffff);
    compare_printfs("%-4x.%-4x", 0x17, 0xffff);
    compare_printfs("%04x.%04x.%04x.%04x.%04x", 0, 1, 0x12, 0x123, 0x1234);
    compare_printfs("%08.4x", 1);
    compare_printfs("%08.0x", 1);
    compare_printfs("%08.x", 1);
    compare_printfs("%8.3x.%8.3x.%8.3x.%8.3x.%8.3x", 0, 1, 0x12, 0x123, 0x1234);
    compare_printfs("%08.4x.% 8.4x.%+8.4x", 0x12, 0x13, 0x14);
    compare_printfs("%-8.3x.%-8.3x.%-8.3x.%-8.3x.%-8.3x", 0, 1, 0x12, 0x123, 0x1234);
    compare_printfs("%#8.4x.%#8.4x.%#8.4x.%#8.4x.%#8.4x", 0, 1, 0x12, 0x123, 0x1234);
    compare_printfs("%255x", 1);
    compare_printfs("%-255x", 1);
    compare_printfs("%.255x", 2);
    compare_printfs("%lx %lx %lx %lx %lx %lx %lx %lx", 0L, 1L, 0x12345678L, 0x9abcdef0L, 0x7fffffffL, 0x80000000L, 0x80000001L, 0xffffffffL);
    compare_printfs("%hx %hx %hx", 0, 2, 0xfffe);
}

Test(my_printf, format_hex_uppercase, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%X %X", 0x1234, 0xABCD);
    compare_printfs("%X", -1);
    compare_printfs("%04X", 255);
    compare_printfs("%08X", 65537);
    for (int i = -100; i < 100; ++i)
        compare_printfs("%X", i);
    for (int i = -100; i < 100; ++i)
        compare_printfs("%04X", i);
    for (int i = -100; i < 100; ++i)
        compare_printfs("%08X", i);
    compare_printfs("%X %X %X %X %X", 0, 0x1234, 0x5678, 0x9abc, 0xdef0);
    compare_printfs("%#X %#X %#X %#X", 0xfedc, 0xba98, 0x7654, 0x3210);
}

Test(my_printf, format_precision_string, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    static const char array[5] = {'a', 'b', 'c', 'n', 'o'};
    compare_printfs("%.*s", 3, array);
}

Test(my_printf, too_many_args, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    compare_printfs("%d %d", 123, 456, 789);
}

Test(my_printf, some_format_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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

Test(my_printf, through_int_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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

Test(my_printf, through_long_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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

Test(my_printf, through_long_long_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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
        compare_printfs("%Ld", values[i]);
        compare_printfs("%Lx", values[i]);
        compare_printfs("%LX", values[i]);
        compare_printfs("%Lo", values[i]);
        compare_printfs("%#Lx", values[i]);
        compare_printfs("%#LX", values[i]);
        compare_printfs("%10Ld", values[i]);
        compare_printfs("%10Lx", values[i]);
        compare_printfs("%10LX", values[i]);
        compare_printfs("%10Lo", values[i]);
        compare_printfs("%#10Lx", values[i]);
        compare_printfs("%#10LX", values[i]);
        compare_printfs("%#10Lo", values[i]);
        compare_printfs("%-10Ld", values[i]);
        compare_printfs("%-10Lx", values[i]);
        compare_printfs("%-10LX", values[i]);
        compare_printfs("%-10Lo", values[i]);
        compare_printfs("%-#10Lx", values[i]);
        compare_printfs("%-#10LX", values[i]);
        compare_printfs("%-#10Lo", values[i]);
    }
}

Test(my_printf, through_size_t_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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

Test(my_printf, through_string_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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

Test(my_printf, format_n, .init = do_init)
{
    int count_int = -1;
    signed char count_char = -1;
    short count_short = -1;
    long count_long = -1;
    long long count_long_long = -1;
    intmax_t count_intmax_t = -1;
    ssize_t count_size_t = -1;
    ptrdiff_t count_ptrdiff_t = -1;
    my_printf("%d %n", 123, &count_int);
    my_printf("%d %hhn", 123, &count_char);
    my_printf("%d %hn", 123, &count_short);
    my_printf("%d %ln", 123, &count_long);
    my_printf("%d %lln", 123, &count_long_long);
    my_printf("%d %jn", 123, &count_intmax_t);
    my_printf("%d %zn", 123, &count_size_t);
    my_printf("%d %tn", 123, &count_ptrdiff_t);
    cr_assert_eq(count_int, 4);
    cr_assert_eq(count_char, 4);
    cr_assert_eq(count_short, 4);
    cr_assert_eq(count_long, 4);
    cr_assert_eq(count_long_long, 4);
    cr_assert_eq(count_intmax_t, 4);
    cr_assert_eq(count_size_t, 4);
    cr_assert_eq(count_ptrdiff_t, 4);

    char bytes[7];
    memset(bytes, '\xff', sizeof bytes);
    my_printf("foo %hhn", &bytes[3]);
    cr_assert_not(bytes[0] != '\xff' || bytes[1] != '\xff' || bytes[2] != '\xff' || bytes[4] != '\xff' || bytes[5] != '\xff' || bytes[6] != '\xff');
    cr_assert_eq(bytes[3], 4);
    cr_assert_stdout_eq_str("123 123 123 123 123 123 123 123 foo ");
}

Test(my_printf, through_format, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    char buffer[7];
    char *prefix = buffer;
    char format[20];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                for (int l = 0; l < 2; l++) {
                    strcpy(prefix, "%");
                    if (i == 0)
                        strcat(prefix, "-");
                    if (j == 0)
                        strcat(prefix, "+");
                    if (k == 0)
                        strcat(prefix, "#");
                    if (l == 0)
                        strcat(prefix, "0");
                    compare_printfs("%5s |", prefix);
                    strcpy(format, prefix);
                    strcat(format, "6d |");
                    compare_printfs(format, -123);
                    strcpy(format, prefix);
                    strcat(format, "6o |");
                    compare_printfs(format, 255);
                    strcpy(format, prefix);
                    strcat(format, "6x |");
                    compare_printfs(format, 255);
                    strcpy(format, prefix);
                    strcat(format, "6X |");
                    compare_printfs(format, 255);
                    strcpy(format, prefix);
                    strcat(format, "6u |");
                    compare_printfs(format, ~0);
                }
    compare_printfs("%-10s\n", (char *)NULL);
    compare_printfs("%-10s\n", (char *)NULL);
}

#ifdef LIBMY_FLOATING_POINT_CLUDGE

Test(my_printf, some_float_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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
    compare_printfs("%#.0f", 1.0);
    compare_printfs("%e", 1234567.8);
    compare_printfs("%f", 1234567.8);
    compare_printfs("%G", 1234567.8);
    compare_printfs("%Le", 1234567.8L);
    compare_printfs("%Lf", 1234567.8L);
    compare_printfs("%LG", 1234567.8L);
    compare_printfs("%Lf", 123456789.8642097531L);
    compare_printfs("%LG", -123456789.8642097531L);
    compare_printfs("%lle", 1234567.8L);
    compare_printfs("%llf", 1234567.8L);
    compare_printfs("%llG", 1234567.8L);
    compare_printfs("%llf", 123456789.8642097531L);
    compare_printfs("%llG", -123456789.8642097531L);
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
    compare_printfs("%#.0f", 1.0);

    /* Test the support of the 'a' and 'A' conversion specifier for hexadecimal
       output of floating-point numbers.  */

    /* Positive zero.  */
    compare_printfs("%a %d\n", 0.0, 33, 44, 55);

    /* Positive infinity.  */
    compare_printfs("%a %d\n", INFINITY, 33, 44, 55);

    /* Negative infinity.  */
    compare_printfs("%a %d\n", -INFINITY, 33, 44, 55);

    /* FLAG_ZERO with infinite number.  */
    compare_printfs("%010a %d\n", INFINITY, 33, 44, 55);

    /* Test the support of the %f format directive.  */

    /* A positive number.  */
    compare_printfs("%f %d\n", 12.75, 33, 44, 55);

    /* A larger positive number.  */
    compare_printfs("%f %d\n", 1234567.0, 33, 44, 55);

    /* A negative number.  */
    compare_printfs("%f %d\n", -0.03125, 33, 44, 55);

    /* Positive zero.  */
    compare_printfs("%f %d\n", 0.0, 33, 44, 55);

    /* FLAG_ZERO.  */
    compare_printfs("%015f %d\n", 1234.0, 33, 44, 55);

    /* Precision.  */
    compare_printfs("%.f %d\n", 1234.0, 33, 44, 55);

    /* Precision with no rounding.  */
    compare_printfs("%.2f %d\n", 999.95, 33, 44, 55);

    /* Precision with rounding.  */
    compare_printfs("%.2f %d\n", 999.996, 33, 44, 55);

    /* A positive number.  */
    compare_printfs("%Lf %d\n", 12.75L, 33, 44, 55);

    /* A larger positive number.  */
    compare_printfs("%Lf %d\n", 1234567.0L, 33, 44, 55);

    /* A negative number.  */
    compare_printfs("%Lf %d\n", -0.03125L, 33, 44, 55);

    /* Positive zero.  */
    compare_printfs("%Lf %d\n", 0.0L, 33, 44, 55);

    /* FLAG_ZERO.  */
    compare_printfs("%015Lf %d\n", 1234.0L, 33, 44, 55);

    /* Precision.  */
    compare_printfs("%.Lf %d\n", 1234.0L, 33, 44, 55);

    /* Precision with no rounding.  */
    compare_printfs("%.2Lf %d\n", 999.95L, 33, 44, 55);

    /* Precision with rounding.  */
    compare_printfs("%.2Lf %d\n", 999.996L, 33, 44, 55);

    /* Test the support of the %F format directive.  */

    /* A positive number.  */
    compare_printfs("%F %d\n", 12.75, 33, 44, 55);

    /* A larger positive number.  */
    compare_printfs("%F %d\n", 1234567.0, 33, 44, 55);

    /* A negative number.  */
    compare_printfs("%F %d\n", -0.03125, 33, 44, 55);

    /* Positive zero.  */
    compare_printfs("%F %d\n", 0.0, 33, 44, 55);

    /* FLAG_ZERO.  */
    compare_printfs("%015F %d\n", 1234.0, 33, 44, 55);

    /* Precision.  */
    compare_printfs("%.F %d\n", 1234.0, 33, 44, 55);

    /* Precision with no rounding.  */
    compare_printfs("%.2F %d\n", 999.95, 33, 44, 55);

    /* Precision with rounding.  */
    compare_printfs("%.2F %d\n", 999.996, 33, 44, 55);

    /* A positive number.  */
    compare_printfs("%LF %d\n", 12.75L, 33, 44, 55);

    /* A larger positive number.  */
    compare_printfs("%LF %d\n", 1234567.0L, 33, 44, 55);

    /* A negative number.  */
    compare_printfs("%LF %d\n", -0.03125L, 33, 44, 55);

    /* Positive zero.  */
    compare_printfs("%LF %d\n", 0.0L, 33, 44, 55);

    /* FLAG_ZERO.  */
    compare_printfs("%015LF %d\n", 1234.0L, 33, 44, 55);

    /* Precision.  */
    compare_printfs("%.LF %d\n", 1234.0L, 33, 44, 55);

    /* Precision with no rounding.  */
    compare_printfs("%.2LF %d\n", 999.95L, 33, 44, 55);

    /* Precision with rounding.  */
    compare_printfs("%.2LF %d\n", 999.996L, 33, 44, 55);

    compare_printfs("%Lg %d", (long double)1.5, 33, 44, 55);
    compare_printfs("%a %d", 3.1416015625, 33, 44, 55);
    compare_printfs("%A %d", -3.1416015625, 33, 44, 55);
    compare_printfs("%a %d", 0.0, 33, 44, 55);
    compare_printfs("%a %d", -0.0, 33, 44, 55);
    compare_printfs("%a %d", INFINITY, 33, 44, 55);
    compare_printfs("%a %d", -INFINITY, 33, 44, 55);
    compare_printfs("%a %d", NAN, 33, 44, 55);
    compare_printfs("%.0a %d", 1.5, 33, 44, 55);
    compare_printfs("%.0a %d", 1.51, 33, 44, 55);
    compare_printfs("%.1a %d", 1.51, 33, 44, 55);
    compare_printfs("%.2a %d", 1.51, 33, 44, 55);
    compare_printfs("%.3a %d", 1.51, 33, 44, 55);
    compare_printfs("%.3a %d", 1.49999, 33, 44, 55);
    compare_printfs("%.1a %d", 1.999, 33, 44, 55);
    compare_printfs("%10a %d", 1.75, 33, 44, 55);
    compare_printfs("%.10a %d", 1.75, 33, 44, 55);
    compare_printfs("%.50a %d", 1.75, 33, 44, 55);
    compare_printfs("%-10a %d", 1.75, 33, 44, 55);
    compare_printfs("%+a %d", 1.75, 33, 44, 55);
    compare_printfs("% a %d", 1.75, 33, 44, 55);
    compare_printfs("%#a %d", 1.75, 33, 44, 55);
    compare_printfs("%#a %d", 1.0, 33, 44, 55);
    compare_printfs("%010a %d", 1.75, 33, 44, 55);
    compare_printfs("%010a %d", INFINITY, 33, 44, 55);
    compare_printfs("%050a %d", NAN, 33, 44, 55);
    compare_printfs("%La %d", 3.1416015625L, 33, 44, 55);
    compare_printfs("%LA %d", -3.1416015625L, 33, 44, 55);
    compare_printfs("%La %d", 0.0L, 33, 44, 55);
    compare_printfs("%La %d", -0.0L, 33, 44, 55);
    compare_printfs("%La %d", (long double)INFINITY, 33, 44, 55);
    compare_printfs("%La %d", (long double)-INFINITY, 33, 44, 55);
    compare_printfs("%La %d", (long double)NAN, 33, 44, 55);
    compare_printfs("%.0La %d", 1.5L, 33, 44, 55);
    compare_printfs("%.0La %d", 1.51L, 33, 44, 55);
    compare_printfs("%.1La %d", 1.51L, 33, 44, 55);
    compare_printfs("%.2La %d", 1.51L, 33, 44, 55);
    compare_printfs("%.3La %d", 1.51L, 33, 44, 55);
    compare_printfs("%.3La %d", 1.49999L, 33, 44, 55);
    compare_printfs("%.1La %d", 1.999L, 33, 44, 55);
    compare_printfs("%10La %d", 1.75L, 33, 44, 55);
    compare_printfs("%.10La %d", 1.75L, 33, 44, 55);
    compare_printfs("%.50La %d", 1.75L, 33, 44, 55);
    compare_printfs("%-10La %d", 1.75L, 33, 44, 55);
    compare_printfs("%+La %d", 1.75L, 33, 44, 55);
    compare_printfs("% La %d", 1.75L, 33, 44, 55);
    compare_printfs("%#La %d", 1.75L, 33, 44, 55);
    compare_printfs("%#La %d", 1.0L, 33, 44, 55);
    compare_printfs("%010La %d", 1.75L, 33, 44, 55);
    compare_printfs("%010La %d", (long double)INFINITY, 33, 44, 55);
    compare_printfs("%050La %d", (long double)NAN, 33, 44, 55);
    compare_printfs("%f %d", 12.75, 33, 44, 55);
    compare_printfs("%f %d", 1234567.0, 33, 44, 55);
    compare_printfs("%f %d", -0.03125, 33, 44, 55);
    compare_printfs("%f %d", 0.0, 33, 44, 55);
    compare_printfs("%f %d", -0.0, 33, 44, 55);
    compare_printfs("%f %d", INFINITY, 33, 44, 55);
    compare_printfs("%f %d", -INFINITY, 33, 44, 55);
    compare_printfs("%f %d", NAN, 33, 44, 55);
    compare_printfs("%10f %d", 1.75, 33, 44, 55);
    compare_printfs("%-10f %d", 1.75, 33, 44, 55);
    compare_printfs("%+f %d", 1.75, 33, 44, 55);
    compare_printfs("% f %d", 1.75, 33, 44, 55);
    compare_printfs("%#f %d", 1.75, 33, 44, 55);
    compare_printfs("%#.f %d", 1.75, 33, 44, 55);
    compare_printfs("%015f %d", 1234.0, 33, 44, 55);
    compare_printfs("%015f %d", -INFINITY, 33, 44, 55);
    compare_printfs("%050f %d", NAN, 33, 44, 55);
    compare_printfs("%.f %d", 1234.0, 33, 44, 55);
    compare_printfs("%.2f %d", 999.951, 33, 44, 55);
    compare_printfs("%.2f %d", 999.996, 33, 44, 55);
    compare_printfs("%Lf %d", 12.75L, 33, 44, 55);
    compare_printfs("%Lf %d", 1234567.0L, 33, 44, 55);
    compare_printfs("%.4000f %d", 1.0, 99);
    compare_printfs("%.511f %d", 1.0, 99);
    compare_printfs("e1=%f %% e2=%f", 1.25, -6.5);
}

Test(my_printf, through_float_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    static const double values[] = {-(0.0 / 0.0), -INFINITY, -99999, -99, -17.4, -4.3, -3.0, -1.5, -1, 0, 0.1, 0.2342374852, 0.2340007, 3.1415926, 14.7845, 34.24758, 9999, 9999999, INFINITY, (0.0 / 0.0), 0.001, 1.0e-20, 1.0, 100.0, 9.9999, -0.00543, -99.99999, 12.75, 1234567.0, -0.03125};

    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%f", values[i]);
        compare_printfs("%10f", values[i]);
        compare_printfs("%010f", values[i]);
        compare_printfs("%015f", values[i]);
        compare_printfs("%.2f", values[i]);
        compare_printfs("%.0f", values[i]);
        compare_printfs("%7.0f", values[i]);
        compare_printfs("%5.2f", values[i]);
        compare_printfs("%0f", values[i]);
        compare_printfs("%#f", values[i]);
        compare_printfs("%F", values[i]);
        compare_printfs("%10F", values[i]);
        compare_printfs("%010F", values[i]);
        compare_printfs("%015F", values[i]);
        compare_printfs("%.2F", values[i]);
        compare_printfs("%.0F", values[i]);
        compare_printfs("%.F", values[i]);
        compare_printfs("%7.0F", values[i]);
        compare_printfs("%5.2F", values[i]);
        compare_printfs("%0F", values[i]);
        compare_printfs("%#F", values[i]);
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

Test(my_printf, through_long_double_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
{
    static const long double values[] = {  1.234321234321234e-37L, 1.234321234321234e-36L, 1.234321234321234e-35L, 1.234321234321234e-34L, 1.234321234321234e-33L, 1.234321234321234e-32L, 1.234321234321234e-31L, 1.234321234321234e-30L, 1.234321234321234e-29L, 1.234321234321234e-28L, 1.234321234321234e-27L, 1.234321234321234e-26L, 1.234321234321234e-25L, 1.234321234321234e-24L, 1.234321234321234e-23L, 1.234321234321234e-22L, 1.234321234321234e-21L, 1.234321234321234e-20L, 1.234321234321234e-19L, 1.234321234321234e-18L, 1.234321234321234e-17L, 1.234321234321234e-16L, 1.234321234321234e-15L, 1.234321234321234e-14L, 1.234321234321234e-13L, 1.234321234321234e-12L, 1.234321234321234e-11L, 1.234321234321234e-10L, 1.234321234321234e-9L, 1.234321234321234e-8L, 1.234321234321234e-7L, 1.234321234321234e-6L, 1.234321234321234e-5L, 1.234321234321234e-4L, 1.234321234321234e-3L, 1.234321234321234e-2L, 1.234321234321234e-1L, 1.234321234321234L, 1.234321234321234e1L, 1.234321234321234e2L, 1.234321234321234e3L, 1.234321234321234e4L, 1.234321234321234e5L, 1.234321234321234e6L, 1.234321234321234e7L, 1.234321234321234e8L, 1.234321234321234e9L, 1.234321234321234e10L, 1.234321234321234e11L, 1.234321234321234e12L, 1.234321234321234e13L, 1.234321234321234e14L, 1.234321234321234e15L, 1.234321234321234e16L, 1.234321234321234e17L, 1.234321234321234e18L, 1.234321234321234e19L, 1.234321234321234e20L, 1.234321234321234e21L, 1.234321234321234e22L, 1.234321234321234e23L, 1.234321234321234e24L, 1.234321234321234e25L, 1.234321234321234e26L, 1.234321234321234e27L, 1.234321234321234e28L, 1.234321234321234e29L, 1.234321234321234e30L, 1.234321234321234e31L, 1.234321234321234e32L, 1.234321234321234e33L, 1.234321234321234e34L, 1.234321234321234e35L, 1.234321234321234e36L, -0.03125L, 0.0L, -0.0L, INFINITY, -INFINITY, NAN, 1.75L, 1234.0L, 999.951L, 999.996L };
    for (size_t i = 0; i < MY_ARRAY_SIZE(values); ++i) {
        compare_printfs("%Lf", values[i]);
        compare_printfs("%10Lf", values[i]);
        compare_printfs("%-10Lf", values[i]);
        compare_printfs("%+Lf", values[i]);
        compare_printfs("% Lf", values[i]);
        compare_printfs("%#Lf", values[i]);
        compare_printfs("%#.Lf", values[i]);
        compare_printfs("%015Lf", values[i]);
        compare_printfs("%.Lf", values[i]);
        compare_printfs("%.2Lf", values[i]);
    }
}

Test(my_printf, through_float_widths_checks, .init = do_init, .fini = compare_all_libc_to_stdout)
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
    my_printf("%S", "a\002\377\012\370b");
    cr_assert_stdout_eq_str("a\\002\\377\\012\\370b");
}

Test(my_printf, format_epitech_extension_b)
{
    cr_redirect_stdout();
    my_printf("%b", 022645);
    cr_assert_stdout_eq_str("10010110100101");
}
