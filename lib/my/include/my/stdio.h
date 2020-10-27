/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares stdio-related functions from libmy
*/

#pragma once

#include "my/config.h"

int my_putchar(int character);
int my_dputc(int character, int fd);
int my_dputs(const char *string, int fd);
int my_puts(const char *string);
