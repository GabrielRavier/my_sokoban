/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares glibc-specific test stuff
*/

#pragma once

#include "../tests_header.h"
#include "my/cpp-like/algorithm.h"
#include "my/string.h"
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>

static char *glibc_buf1, *glibc_buf2;
static size_t glibc_page_size;

static void glibc_test_string_init(void)
{
    glibc_page_size = 2 * getpagesize();
#ifdef GLIBC_MIN_PAGE_SIZE
    glibc_page_size = MY_MAX(glibc_page_size, (GLIBC_MIN_PAGE_SIZE));
#endif
    glibc_buf1 = mmap(0, 2 * glibc_page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    cr_assert_neq(glibc_buf1, MAP_FAILED);
    cr_assert_eq(mprotect(glibc_buf1 + glibc_page_size, glibc_page_size, PROT_NONE), 0);
    glibc_buf2 = mmap(0, 2 * glibc_page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    cr_assert_neq(glibc_buf2, MAP_FAILED);
    cr_assert_eq(mprotect(glibc_buf2 + glibc_page_size, glibc_page_size, PROT_NONE), 0);

    my_memset(glibc_buf1, 0xA5, glibc_page_size);
    my_memset(glibc_buf2, 0x5A, glibc_page_size);
}
