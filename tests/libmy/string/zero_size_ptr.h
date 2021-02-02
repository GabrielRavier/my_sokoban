/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares zero_size_ptr
*/

#pragma once

#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>

static inline void *zero_size_ptr(void)
{
    size_t page_size = (size_t)getpagesize();
    char *two_pages = (char *)mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (two_pages != (char *)(-1) && mprotect(two_pages + page_size, page_size, PROT_NONE) == 0)
        return two_pages + page_size;
    return NULL;
}
