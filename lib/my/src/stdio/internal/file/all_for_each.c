/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines all_for_each
*/

#include "my/internal/stdio.h"
#include "my/internal/stdio/bucket.h"

#if !LIBMY_USE_LIBC_FILE

int my_internal_file_all_for_each(int (*func)(MY_FILE *fp))
{
    int result = 0;

    for (struct my_internal_file_bucket *bucket_it =
        &g_my_file_internal_first_bucket; bucket_it != NULL;
        bucket_it = bucket_it->next)
        for (size_t i = 0; i < bucket_it->num_files; ++i)
            if (bucket_it->files[i].flags != 0)
                result |= func(&bucket_it->files[i]);
    return (result);
}

#endif
