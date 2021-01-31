/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares entities related to unistd.h
*/

#pragma once

#include "features.h"

// Duplicates the actions of the shell in searching for an executable file
// (using PATH) if the given filename doesn't contain a /
int my_execvp(const char *file, char *const argv[]) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1, 2));

// Executes execve with the given arguments, and envp being environ
int my_execv(const char *pathname, char *const argv[]) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1, 2));
