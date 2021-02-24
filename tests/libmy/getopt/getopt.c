/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests getopt
*/

#include "../tests_header.h"
#include "my/getopt.h"
#include "my/cpp-like/iterator.h"
#include <criterion/redirect.h>

#pragma GCC diagnostic ignored "-Wcast-qual"

static void do_one_test(int argc, char **argv, const char *optstring, int expected_result, int expected_optind, const char *expected_optarg)
{
    int result = my_getopt(argc, argv, optstring);
    cr_assert_eq(result, expected_result);
    cr_assert_eq(optind, expected_optind);
    if (optarg != NULL || expected_optarg != NULL)
        cr_assert_str_eq(optarg, expected_optarg);
}

Test(my_getopt, escape_options_without_arguments, .init = cr_redirect_stderr)
{
    const char *optstring = "abc";
    const char *argv[] = {"my_getopt_test", "-a", "-b", "-ccc", "-c", "-bc", "-de", "--"};
    int argc = MY_ARRAY_SIZE(argv);
    FILE *expected_stderr = tmpfile();
    if (expected_stderr == NULL)
        perror("tmpfile");

    do_one_test(argc, (char **)argv, optstring, 'a', 2, NULL);
    do_one_test(argc, (char **)argv, optstring, 'b', 3, NULL);
    do_one_test(argc, (char **)argv, optstring, 'c', 3, NULL);
    do_one_test(argc, (char **)argv, optstring, 'c', 3, NULL);
    do_one_test(argc, (char **)argv, optstring, 'c', 4, NULL);
    do_one_test(argc, (char **)argv, optstring, 'c', 5, NULL);
    do_one_test(argc, (char **)argv, optstring, 'b', 5, NULL);
    do_one_test(argc, (char **)argv, optstring, 'c', 6, NULL);
    do_one_test(argc, (char **)argv, optstring, '?', 6, NULL);
    if (expected_stderr)
        fprintf(expected_stderr, "my_getopt_test: invalid option -- 'd'\n");
    do_one_test(argc, (char **)argv, optstring, '?', 7, NULL);
    if (expected_stderr)
        fprintf(expected_stderr, "my_getopt_test: invalid option -- 'e'\n");
    do_one_test(argc, (char **)argv, optstring, -1, 8, NULL);

    if (expected_stderr) {
        cr_assert_stderr_eq(expected_stderr);
        fclose(expected_stderr);
    }
}

Test(my_getopt, escape_options_with_arguments)
{
    const char *optstring = "a:b:c";
    const char *argv[] = {"my_getopt_test", "-a", "foo", "-b", "bar", "-c", "-bzoo", "-"};
    int argc = MY_ARRAY_SIZE(argv);

    do_one_test(argc, (char **)argv, optstring, 'a', 3, "foo");
    do_one_test(argc, (char **)argv, optstring, 'b', 5, "bar");
    do_one_test(argc, (char **)argv, optstring, 'c', 6, NULL);
    do_one_test(argc, (char **)argv, optstring, 'b', 7, "zoo");
    do_one_test(argc, (char **)argv, optstring, -1, 7, NULL);
}

Test(my_getopt, midnight_bsd, .init = cr_redirect_stderr)
{
    const char *optstring = "c:d";
    const char *argv1[] = {"my_getopt_test", "-c", "1", "-d", "foo"};
    int argc = MY_ARRAY_SIZE(argv1);
    FILE *expected_stderr = tmpfile();
    if (expected_stderr == NULL)
        perror("tmpfile");

    optind = 0;
    do_one_test(argc, (char **)argv1, optstring, 'c', 3, "1");
    do_one_test(argc, (char **)argv1, optstring, 'd', 4, NULL);
    do_one_test(argc, (char **)argv1, optstring, -1, 4, NULL);

    const char *argv2[] = {"my_getopt_test", "-d", "foo", "bar"};
    argc = MY_ARRAY_SIZE(argv2);

    optind = 0;
    do_one_test(argc, (char **)argv2, optstring, 'd', 2, NULL);
    do_one_test(argc, (char **)argv2, optstring, -1, 2, NULL);

    const char *argv3[] = {"my_getopt_test", "-c", "2", "foo", "bar"};
    argc = MY_ARRAY_SIZE(argv3);

    optind = 0;
    do_one_test(argc, (char **)argv3, optstring, 'c', 3, "2");
    do_one_test(argc, (char **)argv3, optstring, -1, 3, NULL);

    const char *argv4[] = {"my_getopt_test", "-e", "1", "foo", "bar"};
    argc = MY_ARRAY_SIZE(argv4);

    optind = 0;
    do_one_test(argc, (char **)argv4, optstring, '?', 2, NULL);
    if (expected_stderr)
        fprintf(expected_stderr, "my_getopt_test: invalid option -- 'e'\n");
    do_one_test(argc, (char **)argv4, optstring, -1, 2, NULL);

    const char *argv5[] = {"my_getopt_test", "-d", "--", "-c", "1"};
    argc = MY_ARRAY_SIZE(argv5);

    optind = 0;
    do_one_test(argc, (char **)argv5, optstring, 'd', 2, NULL);
    do_one_test(argc, (char **)argv5, optstring, -1, 3, NULL);

    const char *argv6[] = {"my_getopt_test", "-c-", "1"};
    argc = MY_ARRAY_SIZE(argv6);

    optind = 0;
    do_one_test(argc, (char **)argv6, optstring, 'c', 2, "-");
    do_one_test(argc, (char **)argv6, optstring, -1, 2, NULL);

    const char *argv7[] = {"my_getopt_test", "-d", "-", "1"};
    argc = MY_ARRAY_SIZE(argv7);

    optind = 0;
    do_one_test(argc, (char **)argv7, optstring, 'd', 2, NULL);
    do_one_test(argc, (char **)argv7, optstring, -1, 2, NULL);

    if (expected_stderr) {
        cr_assert_stderr_eq(expected_stderr);
        fclose(expected_stderr);
    }
}
