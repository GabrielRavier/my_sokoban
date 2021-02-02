/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests qsort_r
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"
#include "my/macros.h"

#define QSORT_NAME qsort_r
#define MY_QSORT_NAME my_qsort_r
#define IS_QSORT_R

#define QSORT(base, nmemb, size, compar, arg) qsort_r(base, nmemb, size, compar, arg)
#define MY_QSORT(base, nmemb, size, compar, arg) my_qsort_r(base, nmemb, size, compar, arg)

#include "qsort_generic.h"

static int qsort_r_helper_int(const void *a, const void *b, void *arg)
{
    const char *char_a = a;
    const char *char_b = b;
    const int *int_arg = arg;
    return MY_THREE_WAY_CMP(*char_a, *char_b) * *int_arg;
}

Test(my_qsort_r, gnulib)
{
    char buffer[] = "thequickbrownfoxjumpedoverthelazydogs";
    int forward = 1;
    int reverse = -1;
    my_qsort_r(buffer, sizeof(buffer) - 1, 1, &qsort_r_helper_int, &forward);
    cr_assert_eq(my_strcmp(buffer, "abcddeeeefghhijklmnoooopqrrsttuuvwxyz"), 0);
    my_qsort_r(buffer, sizeof(buffer) - 1, 1, &qsort_r_helper_int, &reverse);
    cr_assert_eq(my_strcmp(buffer, "zyxwvuuttsrrqpoooonmlkjihhgfeeeeddcba"), 0);
}
