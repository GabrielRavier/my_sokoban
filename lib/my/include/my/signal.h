/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares signal-related entities
*/

#pragma once

#include <signal.h>

// Add signal signum to set
int my_sigaddset(sigset_t *set, int signum);
