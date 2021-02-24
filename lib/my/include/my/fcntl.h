/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares fcntl-related entities
*/

#pragma once

#include "features.h"
#include <sys/types.h>

// Open pathname and return a new fd for it, or -1 on error. If open_flag has
// O_CREAT or O_TMPFILE, the third argument is taken as a `mode_t`
int my_open(const char *pathname, int flags, ...) MY_ATTR_NONNULL((1));

// Create and open pathname with the given mode.
int my_creat(const char *pathname, mode_t mode) MY_ATTR_NONNULL((1));
