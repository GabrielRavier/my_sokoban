/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines free
*/

#include "my/stdlib.h"
#include <stdlib.h>
#include "my/assert.h"

#if LIBMY_HAS_LIBC_ALLOC

void my_free(void *ptr)
{
    free(ptr);
}
#else
void my_free(void *ptr)
{
    if (ptr != NULL)
        MY_ASSERT(false && "my_free not implemented");
}
#endif
