/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares getopt stuff
*/

#pragma once

#include "features.h"
#include <getopt.h>

int my_getopt(int argc, char **argv, const char *optstring)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((2, 3));
