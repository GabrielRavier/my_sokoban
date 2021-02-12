/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines find_ptr
*/

#include "my/internal/stdio.h"
#include "my/internal/stdio/bucket.h"
#include "my/stdlib.h"

#if !LIBMY_USE_LIBC_FILE

// This is a static bucket of files for usage when we don't have malloc (the
// size is FOPEN_MAX - 3 to account for the first bucket with the standard stdio
// files)
static MY_FILE second_bucket_files[FOPEN_MAX - 3];
static struct my_internal_file_bucket second_bucket = {
    .next = NULL,
    .num_files = FOPEN_MAX - 3,
    .files = second_bucket_files
};

// This points to the standard files, and the second bucket
struct my_internal_file_bucket g_my_file_internal_first_bucket = {
    .next = &second_bucket,
    .num_files = 3,
    .files = g_my_standard_files
};

// This makes a new bucket to put more files in.
static struct my_internal_file_bucket *make_more_files(void)
{
    static size_t FILES_PER_ALLOC = 50;
    struct my_internal_file_bucket *result = my_calloc(1, sizeof(*result));
    
    if (result == NULL)
        return (NULL);
    result->files = my_calloc(1, sizeof(*result->files) * FILES_PER_ALLOC);
    if (result->files == NULL) {
        my_free(result);
        return (NULL);
    }
    result->num_files = FILES_PER_ALLOC;
    return (result);
}

// This marks a file as used and initializes it to default values, i.e. we have
// nothing to write, we don't have a pointer nor a buffer, we're not (yet) line
// buffered and we have no file
static MY_FILE *make_found_file(MY_FILE *fp)
{
    fp->flags = !0;
    fp->write_space_left = 0;
    fp->buffer_ptr = NULL;
    fp->buffer.base = NULL;
    fp->buffer.size = 0;
    fp->line_buffer_size = 0;
    fp->fd = -1;
    return (fp);
}

MY_FILE *my_internal_file_find_ptr(void)
{
    for (struct my_internal_file_bucket *bucket_it =
         &g_my_file_internal_first_bucket;; bucket_it = bucket_it->next) {
        for (size_t files_it = 0; files_it < bucket_it->num_files; ++files_it)
            if (bucket_it->files[files_it].flags == 0)
                return (make_found_file(&bucket_it->files[files_it]));
        if (bucket_it->next == NULL) {
            bucket_it->next = make_more_files();
            if (bucket_it->next == NULL)
                return (NULL);
        }
    }
}

#endif
