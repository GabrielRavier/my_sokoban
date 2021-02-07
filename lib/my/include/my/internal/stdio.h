/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares stdio-related internal entities
*/

#pragma once

#include "../stdio.h"

int my_internal_file_flush(int c, MY_FILE *file);
MY_FILE *my_internal_find_file_ptr(void);
