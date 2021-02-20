/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines qsort_r
*/

#include "my/stdlib.h"
#include "qsort_r_do_quick.h"

static char *med3(char *a, char *b, char *c,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    return (cmp->func(a, b, cmp->argument) < 0 ?
        (cmp->func(b, c, cmp->argument) < 0 ? b :
        cmp->func(a, c, cmp->argument) < 0 ? c : a) :
        cmp->func(b, c, cmp->argument) > 0 ? b :
        cmp->func(a, c, cmp->argument) < 0 ? c : a);
}

// Get pseudo-median from 3 elements, or from 9 if the array is big enough
static char *get_median(char *base, size_t num_elements, size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    char *result = base + (num_elements >> 1) * element_size;
    char *result2 = base;
    char *result3 = base + (num_elements - 1) * element_size;
    size_t distance;

    if (num_elements > 40) {
        distance = (num_elements >> 3) * element_size;
        result = med3(result - distance, result, result + distance, cmp);
        result2 = med3(result2, result2 + distance, result2 + distance * 2,
            cmp);
        result3 = med3(result3 - distance * 2, result3 - distance, result3,
            cmp);
    }
    return (med3(result, result2, result3, cmp));
}

// Insertion sort is used on arrays with <7 elements. Otherwise, just a straight
// quick sort
void my_internal_qsort_r(void *base_param, size_t num_elements,
    size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    char *base = (char *)base_param;
    struct qsort_state state;

    if (num_elements < 7) {
        for (char *i = base + element_size; i < base + num_elements *
            element_size; i += element_size)
            for (char *j = i; j > base && cmp->func(j - element_size, j,
                cmp->argument) > 0; j -= element_size)
                swap_elements(j, j - element_size, element_size);
        return;
    }
    state.base = base;
    state.p_median = get_median(base, num_elements, element_size, cmp);
    state.pa = base;
    state.pb = base;
    state.pc = base + (num_elements - 1) * element_size;
    state.pd = state.pc;
    do_quick(&state, num_elements, element_size, cmp);
}
