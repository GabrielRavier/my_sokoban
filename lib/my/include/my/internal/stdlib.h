/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares internal stuff for stdlib.h
*/

#pragma once

#include <stddef.h>

// Similar to getenv, but puts the offset of the found variable in offset
char *my_getenv_offset(const char *name, size_t *offset);
