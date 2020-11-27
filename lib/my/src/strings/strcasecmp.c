/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements strcasecmp
*/

#include "my/strings.h"
#include "my/ctype.h"
#include <stddef.h>

int my_strcasecmp(const char *s1, const char *s2)
{
    for (size_t i = 0;; ++i) {
        if (my_tolower(s1[i]) != my_tolower(s2[i]))
            return my_tolower(s1[i]) - my_tolower(s2[i]);
        if (s1[i] == '\0')
            return (0);
    }
}
