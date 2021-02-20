/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines qsort_r_do_quick
*/

#pragma once

#include "my/stdlib.h"
#include "my/cpp-like/algorithm.h"
#include "my/string.h"
#include "my/features.h"
#include <stddef.h>
#include <stdbool.h>

struct qsort_state {
    char *base;
    char *p_median;
    char *pa;
    char *pb;
    char *pc;
    char *pd;
};

MY_ATTR_ACCESS((read_write, 1, 3)) MY_ATTR_ACCESS((read_write, 2, 3))
MY_ATTR_NONNULL((1, 2)) static void swap_elements(char *elem1, char *elem2,
    size_t element_size)
{
    char buffer[10000];
    size_t copy_size;

    while (element_size) {
        copy_size = MY_MIN(sizeof(buffer), element_size);
        my_memcpy(buffer, elem1, copy_size);
        my_memcpy(elem1, elem2, copy_size);
        my_memcpy(elem2, buffer, copy_size);
        elem1 += copy_size;
        elem2 += copy_size;
        element_size -= copy_size;
    }
}

static void finish_quick(struct qsort_state *state, size_t num_elements,
    size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    char *p_end = state->base + num_elements * element_size;
    size_t distance = MY_MIN(state->pa - state->base, state->pb - state->pa);

    if (distance)
        swap_elements(state->base, state->pb - distance, distance);
    distance = MY_MIN(state->pd - state->pc, p_end - state->pd - element_size);
    if (distance)
        swap_elements(state->pb, p_end - distance, distance);
    distance = state->pb - state->pa;
    if (distance > element_size)
        my_internal_qsort_r(state->base, distance / element_size, element_size,
            cmp);
    distance = state->pd - state->pc;
    if (distance > element_size)
        my_internal_qsort_r(p_end - distance, distance / element_size,
            element_size, cmp);
}

static bool do_below_iter(struct qsort_state *state, size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    int r = cmp->func(state->pb, state->base, cmp->argument);

    if (r > 0)
        return (false);
    if (r == 0) {
        swap_elements(state->pa, state->pb, element_size);
        state->pa += element_size;
    }
    state->pb += element_size;
    return (true);
}

static bool do_above_iter(struct qsort_state *state, size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    int r = cmp->func(state->pc, state->base, cmp->argument);

    if (r < 0)
        return (false);
    if (r == 0) {
        swap_elements(state->pc, state->pd, element_size);
        state->pd -= element_size;
    }
    state->pc -= element_size;
    return (true);
}

static void do_quick(struct qsort_state *state, size_t num_elements,
    size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
{
    swap_elements(state->base, state->p_median, element_size);
    while (true) {
        while (state->pb <= state->pc)
            if (!do_below_iter(state, element_size, cmp))
                break;
        while (state->pb <= state->pc)
            if (!do_above_iter(state, element_size, cmp))
                break;
        if (state->pb > state->pc)
            break;
        swap_elements(state->pb, state->pc, element_size);
        state->pb += element_size;
        state->pc -= element_size;
    }
    finish_quick(state, num_elements, element_size, cmp);
}
