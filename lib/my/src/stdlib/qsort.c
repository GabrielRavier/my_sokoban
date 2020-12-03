/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Sorts an array with num_elements of element_size size, according to
** comparison_function
*/

#include "my/stdlib.h"

static int qsort_r_helper_for_qsort(const void *elem1, const void *elem2,
    void *comparison_function_ptr)
{
    return ((*((int (**)(const void *, const void *))comparison_function_ptr))(
        elem1, elem2));
}

void my_qsort(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *))
{
    my_qsort_r(base, num_elements, element_size, &qsort_r_helper_for_qsort,
        (void *)&comparison_function);
}
