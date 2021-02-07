/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declare sys/stat-related entities
*/

#pragma once

#include "../features.h"
#include <sys/stat.h>

int my_fstat(int fd, struct stat *buf) MY_ATTR_NOTHROW MY_ATTR_NONNULL((2));
