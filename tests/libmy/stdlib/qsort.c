/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests qsort
*/

#include "../tests_header.h"
#include "my/stdlib.h"

#define QSORT_NAME qsort
#define MY_QSORT_NAME my_qsort

#define QSORT(base, nmemb, size, compar, arg) qsort(base, nmemb, size, compar)
#define MY_QSORT(base, nmemb, size, compar, arg) my_qsort(base, nmemb, size, compar)

#include "qsort_generic.h"
