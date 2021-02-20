/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares my_internal_file_bucket
*/

#pragma once

#include "my/stdio.h"
#include <stddef.h>

extern struct my_internal_file_bucket {
    struct my_internal_file_bucket *next;
    size_t num_files;
    my_file_t *files;
} g_my_file_internal_first_bucket;
