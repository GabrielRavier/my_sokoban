/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests qsort
*/

#include "../tests_header.h"
#include "my/stdlib.h"

#define MY_QSORT_NAME my_qsort

#define QSORT(base, nmemb, size, compar, arg) (qsort(base, nmemb, size, compar), (void)(data))
#define MY_QSORT(base, nmemb, size, compar, arg) (my_qsort(base, nmemb, size, compar), (void)(data))

#include "qsort_generic.h"
