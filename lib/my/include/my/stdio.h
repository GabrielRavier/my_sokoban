/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares stdio-related functions from libmy
*/

#pragma once

#include "my/config.h"

int my_putchar(int character) MY_ATTR_WARN_UNUSED_RESULT;
int my_dputc(int character, int fd) MY_ATTR_WARN_UNUSED_RESULT;
int my_dputs(const char *string, int fd) MY_ATTR_WARN_UNUSED_RESULT;
int my_puts(const char *string) MY_ATTR_WARN_UNUSED_RESULT;
